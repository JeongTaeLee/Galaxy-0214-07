#include "DXUT.h"
#include "Animater.h"

//Manager
#include "ImageManager.h"

//Component
#include "Renderer.h"

Animater::Animater()
	:fFrameDelay(0.f), fFrameAccrue(0.f),
	fFrameCount(0)
{
}


Animater::~Animater()
{
}

void Animater::Update()
{

}

void Animater::Add(const std::string& name, std::string& keys, const std::string& paths, int mn, int mx)
{
	if (auto find = mAnimation.find(name); find != mAnimation.end())
		return;

	std::vector<Mesh*>* meshs = new std::vector<Mesh*>;
	
	for (int i = mn; i <= mx; ++i)
	{
		char key[256];
		sprintf(key, keys.c_str(), i);

		char path[256];
		sprintf(path, paths.c_str(), i);
	
		(*meshs).push_back(IMAGE.LoadObjFile(key, path));
	}

	mAnimation.insert(make_pair(name, meshs));
}

void Animater::Chanage(const std::string& name)
{
	if (auto find = mAnimation.find(name); find != mAnimation.end())
	{
		sNowAni = find->first;
		vNowAni = find->second;

		fFrameAccrue = 0.f;
		fFrameCount = 0;
	}
}
