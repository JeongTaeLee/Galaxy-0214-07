#pragma once
#include "singleton.h"

class Scene;

class SceneManager :
	public singleton<SceneManager>
{
private:
	Scene * lpNowScene;
	Scene * lpNextScene;
	std::string sNowScene;

	std::map<std::string, Scene*> mScene;
public:
	SceneManager();
	virtual ~SceneManager();

	Scene * AddScene(const std::string & key, Scene * lpScene);
	Scene * ChangeScene(const std::string key);

	void Update();
};

#define SCENE SceneManager::GetInst()