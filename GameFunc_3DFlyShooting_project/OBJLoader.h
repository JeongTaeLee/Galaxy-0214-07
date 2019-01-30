#pragma once


struct CacheEntry
{
	UINT index;
	CacheEntry* pNext;
};

class OBJLoader
{
private:
	std::string OBJPath;

	std::vector<Vector3> Position;
	std::vector<Vector2> TexCoord;
	std::vector<Vector3> Normal;

	std::vector<VERTEX>  Vertex;
	std::vector<DWORD> Index;
	std::vector<DWORD> Attribute;

	std::vector <CacheEntry*> VertexCache;

	std::string mtlPath;

	void CreateMesh(LPD3DXMESH * mesh);
	void MtlLoad(const std::string & mtlName, Mesh * mesh, const std::string & mapPath = "None");
	DWORD AddVertex(UINT hash, VERTEX* pVertex);
public:
	OBJLoader();
	~OBJLoader();

	void OBJLoad(Mesh * mesh, const std::string & objPath, const std::string & mapPath = "None");
};

