#include "DXUT.h"
#include "SceneManager.h"

//Scene
#include "Scene.h"

SceneManager::SceneManager()
	:lpNowScene(nullptr), lpNextScene(nullptr), sNowScene("None")
{
}

SceneManager::~SceneManager()
{
	if(lpNowScene)
	{
		lpNowScene->Release();
		lpNowScene = nullptr;
	}

	if (lpNextScene)
		lpNextScene = nullptr;

	for (auto Iter : mScene)
		SAFE_DELETE(Iter.second);

	mScene.clear();
}

Scene * SceneManager::AddScene(const std::string & key, Scene * lpScene)
{
	if (auto find = mScene.find(key); find != mScene.end())
		return find->second;

	return mScene.insert(std::make_pair(key, lpScene)).first->second;
}

Scene * SceneManager::ChangeScene(const std::string key)
{
	if (auto find = mScene.find(key); find != mScene.end())
	{
		lpNextScene = find->second;
		sNowScene = find->first;
		return lpNextScene;
	}
	return nullptr;
}

void SceneManager::Update()
{
	if (lpNextScene)
	{
		if (lpNowScene)
			lpNowScene->Release();

		lpNowScene	= nullptr;
		lpNextScene->Init();
		lpNowScene	= lpNextScene;
		lpNextScene = nullptr;
	}
}
