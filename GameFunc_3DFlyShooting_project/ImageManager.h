#pragma once
#include "singleton.h"

struct texture;
struct Mesh;

class OBJLoader;

class ImageManager :
	public singleton<ImageManager>
{
private:
	std::map<std::string, texture*> mTextures;

	std::map<std::string, Mesh*>	mMeshs;
	std::map<std::string, LPD3DXEFFECT> mEffects;

	LPD3DXSPRITE lpD3DSprite;


	OBJLoader * lpObjLoader;
public:
	LPD3DXMESH lpBillBoardMesh;
	
	ImageManager();
	virtual ~ImageManager();

	void Reset();

	texture * LoadTexture(const std::string & key, const std::string & path, bool bNoneDelete = false);
	void LoadTextures(const std::string & keys, const std::string & paths, int mn, int mx, bool bNoneDelete = false);

	Mesh* LoadObjFile(const std::string & keys, const std::string & path, bool bNoneDelete = false);
	void LoadObjFiles(const std::string & keys, const std::string & paths, int mn, int mx);

	LPD3DXEFFECT LoadEffect(const std::string& key, const std::string& path);

public:
	LPD3DXSPRITE GetSprite() { return lpD3DSprite; }
};
 
#define IMAGE ImageManager::GetInst()
#define LOADTEX(k, p) IMAGE.LoadTexture(k, p)