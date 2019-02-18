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

public:
	std::string sNowScene;

public:
	SceneManager();
	virtual ~SceneManager();

	Scene * AddScene(const std::string & key, Scene * lpScene);
	Scene * ChangeScene(const std::string &key);

	void Update();
};

#define SCENE SceneManager::GetInst()