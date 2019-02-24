#include "DXUT.h"
#include "SceneManager.h"

#include "TimeManager.h"
#include "ImageManager.h"
//Scene
#include "Scene.h"

SceneManager::SceneManager()
	:lpNowScene(nullptr), lpNextScene(nullptr),
	sNowScene("None"), bLoading(false),
	iCount(0), fAccrue(0.f), fDelay(0.05f),
	lpTex(nullptr)
{
	LoadImages(veTex, "LoadingScreen%d", " ", 1, 32);
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
		iCount = 0;
		fAccrue = 0.f;

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
		fAccrue += Et;
		
		if (fAccrue >= fDelay)
		{
			fAccrue = 0.f;
		
			lpTex = veTex[iCount];
		
			if (iCount < veTex.size() - 1)
				++iCount;
			else
				iCount = 0;
		}

		if (lpNextScene->GetLoadingComplete())
		{
			lpNextScene->ResetLoadingComplete();

			if (thThread.joinable())
				thThread.join();

			bLoading = false;

			(lpNowScene = lpNextScene)->Init();
	
			lpNextScene = nullptr;
		}
	}

}

void SceneManager::Render()
{
	if (lpTex && bLoading)
	{
		Matrix matPos;
		D3DXMatrixTranslation(&matPos, 0.f, 0.f, 0.f);

		IMAGE.GetSprite()->SetTransform(&matPos);
		IMAGE.GetSprite()->Draw(lpTex->lpD3DTexture, nullptr, nullptr, nullptr, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
	}
}
