#include "DXUT.h"
#include "SceneManager.h"

//Scene
#include "Scene.h"

SceneManager::SceneManager()
	:lpNowScene(nullptr), lpNextScene(nullptr),
	sNowScene("None"), bLoading(false)
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

Scene * SceneManager::ChangeScene(const std::string &key)
{
	if (auto find = mScene.find(key); find != mScene.end())
	{
		lpNextScene = find->second;
		sNowScene = find->first;
		sNowScene = key;
		return lpNextScene;
	}
	return nullptr;
}

void SceneManager::Update()
{
	Sleep(1);

	if (lpNextScene && !bLoading)
	{
		thThread = std::thread([&]() { lpNextScene->LoadingResource(); });
		bLoading = true;

		if (lpNowScene)
		{
			lpNowScene->Release();
			lpNowScene = nullptr;
		}
	}

	if (bLoading)
	{
		if (lpNextScene->GetLoadingComplete())
		{
			if (thThread.joinable())
				thThread.join();

			bLoading = false;

			(lpNowScene = lpNextScene)->Init();
			lpNextScene = nullptr;
		}
	}

}
