#include "DXUT.h"
#include "ImageManager.h"

#include "OBJLoader.h"

ImageManager::ImageManager()
	:lpD3DSprite(nullptr), lpObjLoader(nullptr)
{
	D3DXCreateSprite(g_device , &lpD3DSprite);
	lpObjLoader = new OBJLoader;
}


ImageManager::~ImageManager()
{
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

texture * ImageManager::LoadTexture(const std::string & key, const std::string & path)
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

	return mTextures.insert(std::make_pair(key, new texture(lpD3DTex, info))).first->second;
}

void ImageManager::LoadTextures(const std::string & keys, const std::string & paths, int mn, int mx)
{
	for (int i = mn; i <= mx; ++i)
	{
		char key[256];
		sprintf(key, keys.c_str(), i);
		
		char path[256];
		sprintf(path, paths.c_str(), i);

		LoadTexture(key, path);
	}
}

Mesh* ImageManager::LoadObjFile(const std::string & keys, const std::string & path)
{
	if (auto find = mMeshs.find(keys); find != mMeshs.end())
		return find->second;

	Mesh * mesh = new Mesh;
	lpObjLoader->OBJLoad(mesh, path);

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
