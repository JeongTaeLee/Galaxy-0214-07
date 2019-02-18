#include "DXUT.h"
#include "ImageManager.h"

#include "OBJLoader.h"

ImageManager::ImageManager()
	:lpD3DSprite(nullptr), lpObjLoader(nullptr)
{
	D3DXCreateSprite(g_device , &lpD3DSprite);
	lpObjLoader = new OBJLoader;

	D3DXCreateMeshFVF(
		2,
		4,
		D3DXMESH_MANAGED | D3DXMESH_32BIT,
		VERTEXFVF,
		g_device,
		&lpBillBoardMesh);  

	void* Vertices = nullptr;
	VERTEX* vt;
	lpBillBoardMesh->LockVertexBuffer(0, &Vertices);
	vt = (VERTEX*)Vertices;

	vt[0].pos = Vector3(-1.f, 1.f, 0.f);
	vt[0].normal = Vector3(0.f, 0.f, 0.f);
	vt[0].tex = Vector2(0.f, 0.f);

	vt[1].pos = Vector3(1.f, 1.f, 0.f);
	vt[1].normal = Vector3(0.f, 0.f, 0.f);
	vt[1].tex = Vector2(1.f, 0.f);

	vt[2].pos = Vector3(1.f, -1.f, 0.f);
	vt[2].normal = Vector3(0.f, 0.f, 0.f);
	vt[2].tex = Vector2(1.f, 1.f);

	vt[3].pos = Vector3(-1.f, -1.f, 0.f);
	vt[3].normal = Vector3(0.f, 0.f, 0.f);
	vt[3].tex = Vector2(0.f, 1.f);

	lpBillBoardMesh->UnlockVertexBuffer();

	void* Indices = nullptr;
	lpBillBoardMesh->LockIndexBuffer(0, &Indices);
	DWORD* id = (DWORD*)Indices;

	id[0] = 0; id[1] = 1; id[2] = 3;
	id[3] = 1; id[4] = 2; id[5] = 3;

	lpBillBoardMesh->UnlockIndexBuffer();


	DWORD* Attribute = nullptr;
	lpBillBoardMesh->LockAttributeBuffer(0, &Attribute);


	lpBillBoardMesh->UnlockAttributeBuffer();
}


ImageManager::~ImageManager()
{
	SAFE_RELEASE(lpBillBoardMesh);
	SAFE_RELEASE(lpD3DSprite);
	SAFE_DELETE(lpObjLoader);

	for (auto Iter : mTextures)
	{
		SAFE_RELEASE(Iter.second->lpD3DTexture);
		SAFE_DELETE(Iter.second);
	}
	mTextures.clear();

	for (auto Iter : mMeshs)
	{
		SAFE_DELETE(Iter.second);
	}
	
	for (auto Iter : mEffects)
	{
		SAFE_RELEASE(Iter.second);

	}
	
	mEffects.clear();
}

void ImageManager::Reset()
{
	for (auto Iter : mTextures)
	{
		if(!Iter.second->bNoneDelete)
		{ 
			SAFE_RELEASE(Iter.second->lpD3DTexture);
			SAFE_DELETE(Iter.second);
		}
	}
	mTextures.clear();

	for (auto Iter : mMeshs)
	{
		if (!Iter.second->bNoneDelete)
			SAFE_DELETE(Iter.second);
	}
	mMeshs.clear();


}

texture * ImageManager::LoadTexture(const std::string & key, const std::string & path, bool bNoneDelete)
{
	if (auto find = mTextures.find(key); find != mTextures.end())
		return find->second;

	LPDIRECT3DTEXTURE9 lpD3DTex;
	D3DXIMAGE_INFO		info;

	if ((FAILED(D3DXCreateTextureFromFileExA(g_device, path.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, &info, nullptr, &lpD3DTex))))
	{
		DEBUG_LOG("Failed LoadTex : " << key << " path : " << path);
		return nullptr;
	}

	texture* tex = new texture(lpD3DTex, info);
	tex->bNoneDelete = bNoneDelete;
	return mTextures.insert(std::make_pair(key, tex)).first->second;
}

void ImageManager::LoadTextures(const std::string & keys, const std::string & paths, int mn, int mx, bool bNoneDelete)
{
	for (int i = mn; i <= mx; ++i)
	{
		char key[256];
		sprintf(key, keys.c_str(), i);
		
		char path[256];
		sprintf(path, paths.c_str(), i);

		LoadTexture(key, path, bNoneDelete);
	}
}

Mesh* ImageManager::LoadObjFile(const std::string & keys, const std::string & path, bool bNoneDelete)
{
	if (auto find = mMeshs.find(keys); find != mMeshs.end())
		return find->second;

	Mesh * mesh = new Mesh;
	lpObjLoader->OBJLoad(mesh, path);

	mesh->bNoneDelete = bNoneDelete;
	return mMeshs.insert(make_pair(keys, mesh)).first->second;
}

void ImageManager::LoadObjFiles(const std::string & keys, const std::string & paths, int mn, int mx)
{
	for (int i = mn; i <= mx; ++i)
	{
		char key[256];
		sprintf(key, keys.c_str(), i);
		char path[256];
		sprintf(path, paths.c_str(), i);

		LoadObjFile(key, path);
	}
}

LPD3DXEFFECT ImageManager::LoadEffect(const std::string& key, const std::string& path)
{
	if (auto find = mEffects.find(key); find != mEffects.end())
		return find->second;

	LPD3DXEFFECT lpEffect = nullptr;
	LPD3DXBUFFER lpBuffer = nullptr;
	DWORD dwShaderFlag = 0;
#ifdef DEBUG	
	dwShaderFlag = D3DXSHADER_DEBUG;
#endif

	D3DXCreateEffectFromFileA(g_device,
		path.c_str(), nullptr, nullptr,
		dwShaderFlag, nullptr, &lpEffect,
		&lpBuffer);
	

	if (!lpEffect && lpBuffer)
	{
		int size = lpBuffer->GetBufferSize();
		void* buffer = lpBuffer->GetBufferPointer();

		if (buffer)
		{
			char* str = new char[size];
			sprintf(str, (char *)buffer);
			OutputDebugStringA(str);
			SAFE_DELETE_ARRAY(str);
		}
		return nullptr;
	}

	mEffects.insert(make_pair(key, lpEffect));
	return lpEffect;
}
