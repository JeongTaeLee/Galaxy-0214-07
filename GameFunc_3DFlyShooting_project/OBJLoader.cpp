#include "DXUT.h"
#include "OBJLoader.h"
#include "ImageManager.h"

OBJLoader::OBJLoader()
{
}


OBJLoader::~OBJLoader()
{
}


void OBJLoader::CreateMesh(LPD3DXMESH * mesh)
{
	if (FAILED(D3DXCreateMeshFVF(Index.size() / 3, Vertex.size(), D3DXMESH_MANAGED | D3DXMESH_32BIT, VERTEXFVF, g_device, mesh)))
	{
		DEBUG_LOG("Failed D3DXCreateMeshFVF");
		return ;
	}

	VERTEX * vertices = nullptr;
	if (FAILED((*mesh)->LockVertexBuffer(0, (void**)&vertices)))
	{
		DEBUG_LOG("Failed LockVertexBuffer");
		return ;
	}

	memcpy(vertices, &Vertex[0], sizeof(VERTEX) * Vertex.size());
	(*mesh)->UnlockVertexBuffer();
	Vertex.clear();

	DWORD * indices = nullptr;
	if (FAILED((*mesh)->LockIndexBuffer(0, (void**)&indices)))
	{
		DEBUG_LOG("Failed LockIndexBuffer");
		return ;
	}

	memcpy(indices, &Index[0], sizeof(DWORD) * Index.size());
	(*mesh)->UnlockIndexBuffer();
	Index.clear();
	
	DWORD * attribute = nullptr;
	if (FAILED((*mesh)->LockAttributeBuffer(0, &attribute)))
	{
		DEBUG_LOG("Failed LockAttributeBuffer");
		return ;
	}

	memcpy(attribute, &Attribute[0], sizeof(DWORD) * Attribute.size());
	(*mesh)->UnlockAttributeBuffer();
	Attribute.clear();

	for (size_t i = 0; i < VertexCache.size(); ++i)
	{
		CacheEntry* pEntry = VertexCache[i];
		while (pEntry != NULL)
		{
			CacheEntry* pNext = pEntry->pNext;
			SAFE_DELETE(pEntry);
			pEntry = pNext;
		}
	}
	VertexCache.clear();

	Position.clear();
	TexCoord.clear();
	Normal.clear();
}

void OBJLoader::MtlLoad(const std::string & mtlName, Mesh * mesh, const std::string & mapPath)
{
	std::ifstream mtlLoader;

	mtlLoader.open(mtlPath);

	if (mtlLoader.fail())
	{
		DEBUG_LOG("Mtl 파일 로드 실패!" << mtlName << " " << mtlPath);
		return;
	}
	
	Material * lpMtl = nullptr;
	D3DMATERIAL9 * d3dMtl = nullptr;

	bool findMtl = false;

	while (!mtlLoader.eof())
	{
		std::string tag;
		mtlLoader >> tag;

		if (!findMtl)
		{
			if (tag == "newmtl")
			{
				mtlLoader >> tag;
				if (tag == mtlName)
				{
					lpMtl = new Material;
					
					lpMtl->mtlName = mtlName;
					mesh->vMaterial.push_back(lpMtl);
					
					d3dMtl = &lpMtl->material;

					findMtl = true;
				}
			}
		}
		else
		{
			if (tag == "Ka")
			{
				float r, g, b;
				r = g = b = 0.f;
				 
				mtlLoader >> tag;
				r = (float)atof(tag.c_str());

				mtlLoader >> tag;
				g = (float)atof(tag.c_str());

				mtlLoader >> tag;
				b = (float)atof(tag.c_str());

				d3dMtl->Ambient = { r, g, b, 1.f };
			}
			if (tag == "Kd")
			{
				float r, g, b;
				r = g = b = 0.f;

				mtlLoader >> tag;
				r = (float)atof(tag.c_str());

				mtlLoader >> tag;
				g = (float)atof(tag.c_str());

				mtlLoader >> tag;
				b = (float)atof(tag.c_str());

				d3dMtl->Diffuse = { r, g, b, 1.f };
			}

			if (tag == "Ks")
			{
				float r, g, b;
				r = g = b = 0.f;

				mtlLoader >> tag;
				r = (float)atof(tag.c_str());

				mtlLoader >> tag;
				g = (float)atof(tag.c_str());

				mtlLoader >> tag;
				b = (float)atof(tag.c_str());

				d3dMtl->Specular = { r, g, b, 1.f };
			}
			
			if (tag == "Ke")
			{
				float r, g, b;
				r = g = b = 0.f;

				mtlLoader >> tag;
				r = (float)atof(tag.c_str());
				mtlLoader >> tag;
				g = (float)atof(tag.c_str());
				mtlLoader >> tag;
				b = (float)atof(tag.c_str());

				d3dMtl->Emissive = { r,g,b, 1.f };
			}

			if (tag == "illum")
			{
				float l;

				mtlLoader >> tag;
				l = (float)atof(tag.c_str());

				lpMtl->fIllum = l;
			}

			if (tag == "Ns")
			{
				float n;

				mtlLoader >> tag;
				n = (float)atof(tag.c_str());
			
				lpMtl->fNs = n;
			}

			if (tag == "Tr" || tag == "d")
			{
				float a;

				mtlLoader >> tag;
				
				if (tag == "Tr")
					a = 1.f - (float)atof(tag.c_str());
				else
					a = (float)atof(tag.c_str());
				
				lpMtl->fAlpha = a;
			}

			if (tag == "map_Kd")
			{
				mtlLoader >> tag;

				std::string ImagePath;
				
				if (mapPath == "None")
				{
					int pathIndex = OBJPath.rfind("/"); // 마지막으로 사용된 해당 문자의 인덱스를 가져옴
					ImagePath = OBJPath.substr(0, pathIndex + 1) + tag; // 첫번쨰 인자부터 두번째 인자의 수만큼 글자를 가져옴
				}
				else
					ImagePath = mapPath + tag;

				lpMtl->map = LOADTEX(ImagePath, ImagePath);
			}

			if (tag == "newmtl")
				break;
		}
	}

	mtlLoader.close();
}

DWORD OBJLoader::AddVertex(UINT hash, VERTEX * pVertex)
{
	//DirectX Sample - MeshFromObj 사용함.

	// If this vertex doesn't already exist in the Vertices list, create a new entry.
		// Add the index of the vertex to the Indices list.
	bool bFoundInList = false;
	DWORD index = 0;

	// Since it's very slow to check every element in the vertex list, a hashtable stores
	// vertex indices according to the vertex position's index as reported by the OBJ file
	if ((UINT)VertexCache.size() > hash)
	{
		CacheEntry* pEntry = VertexCache[hash];
		while (pEntry != NULL)
		{
			VERTEX* pCacheVertex = &Vertex[pEntry->index];

			// If this vertex is identical to the vertex already in the list, simply
			// point the index buffer to the existing vertex
			if (0 == memcmp(pVertex, pCacheVertex, sizeof(VERTEX)))
			{
				bFoundInList = true;
				index = pEntry->index;
				break;
			}

			pEntry = pEntry->pNext;
		}
	}

	// Vertex was not found in the list. Create a new entry, both within the Vertices list
	// and also within the hashtable cache
	if (!bFoundInList)
	{
		// Add to the Vertices list
		index = Vertex.size();
		Vertex.push_back(*pVertex);

		// Add this to the hashtable
		CacheEntry* pNewEntry = new CacheEntry;
		if (pNewEntry == NULL)
			return (DWORD)-1;

		pNewEntry->index = index;
		pNewEntry->pNext = NULL;

		// Grow the cache if needed
		while ((UINT)VertexCache.size() <= hash)
		{
			VertexCache.push_back(NULL);
		}

		// Add to the end of the linked list
		CacheEntry* pCurEntry = VertexCache[hash];
		if (pCurEntry == NULL)
		{
			// This is the head element
			//m_VertexCache.SetAt(hash, pNewEntry);
			VertexCache[hash] = pNewEntry;
		}
		else
		{
			// Find the tail
			while (pCurEntry->pNext != NULL)
			{
				pCurEntry = pCurEntry->pNext;
			}

			pCurEntry->pNext = pNewEntry;
		}
	}

	return index;
}

void OBJLoader::OBJLoad(Mesh * mesh, const std::string & objPath, const std::string & mapPath)
{
	OBJPath = objPath;

	DWORD dwAttribute = 0;

	std::ifstream loader;

	loader.open(objPath.c_str());

	if (loader.fail())
	{
		DEBUG_LOG("파일을 여는데 실패 했습니다 : " << objPath.c_str());
		return;
	}

	while (!loader.eof())
	{
		std::string tag;
		loader >> tag;

		if (tag == "v")
		{
			Vector3 position;
			loader >> position.x >> position.y >> position.z;
			Position.push_back(position);
			continue;
		}
		else if (tag == "vt")
		{
			Vector2 texCoord;
			loader >> texCoord.x >> texCoord.y;
			TexCoord.push_back(Vector2(texCoord.x, 1.f - texCoord.y));
			continue;
		}
		else if (tag == "vn")
		{
			Vector3 normal;
			loader >> normal.x >> normal.y >> normal.z;
			Normal.push_back(normal);
			continue;
		}
		else if (tag == "f")
		{
			for (int i = 0; i < 3; ++i)
			{
				std::string str;
				loader >> str;

				UINT iPosition;
				UINT iTexCoord;
				UINT iNormal;

				sscanf(str.c_str(), "%u/%u/%u", &iPosition, &iTexCoord, &iNormal);

				VERTEX vertex;
				vertex.pos = Position[iPosition - 1];
				vertex.tex = TexCoord[iTexCoord - 1];
				vertex.normal = Normal[iNormal - 1];

				DWORD index = AddVertex(iPosition, &vertex);
				Index.push_back(index);
			}

			Attribute.push_back(dwAttribute);
			continue;
		}
		else if (tag == "mtllib")
		{
			loader >> mtlPath;

			int pathIndex = objPath.rfind("/"); // 마지막으로 사용된 해당 문자의 인덱스를 가져옴

			mtlPath = objPath.substr(0, pathIndex + 1) + mtlPath; // 첫번쨰 인자부터 두번째 인자의 수만큼 글자를 가져옴
		}
		else if (tag == "usemtl")
		{
			loader >> tag;

			bool bFind = false;

			for (size_t iMtl = 0; iMtl < mesh->vMaterial.size(); ++iMtl)
			{
				if (mesh->vMaterial[iMtl]->mtlName == tag)
				{
					dwAttribute = iMtl;
					bFind = true;
				}
			}
	
			if (!bFind)
			{
				dwAttribute = mesh->vMaterial.size();
				MtlLoad(tag, mesh, mapPath);
			}
			
			continue;
		}
	}

	return CreateMesh(&mesh->lpD3DXMesh);
}