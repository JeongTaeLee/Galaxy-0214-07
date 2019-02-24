#pragma once
#include "singleton.h"

class Scene;

class SceneManager :
	public singleton<SceneManager>
{
private:
	Scene * lpNowScene;
	Scene * lpNextScene;

	std::map<std::string, Scene*> mScene;

	std::thread thThread;

	bool bLoading;

	texture* lpTex;
	std::vector<texture*> veTex;
	int iCount;
	float fAccrue;
	float fDelay;

public:
	std::string sNowScene;

public:
	SceneManager();
	virtual ~SceneManager();

	Scene * AddScene(const std::string & key, Scene * lpScene);
	Scene * ChangeScene(const std::string &key);

	void Update();
	void Render();
};

#define SCENE SceneManager::GetInst()