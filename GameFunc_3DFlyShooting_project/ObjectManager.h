#pragma once
#include "singleton.h"
#include "Transform.h"

class GameObject;
class Renderer;
class ShaderRenderer;
class ObjectManager :
	public singleton<ObjectManager>
{
private:
	std::list<GameObject*> liGameObjects;

	std::list<Renderer*> liRenderer;
public:
	ObjectManager();
	virtual ~ObjectManager();

	void Reset();
	void Update();
	void Render();

public:
	void DestroyProcess();

public:
	Renderer* RegisterRenderer(Renderer* renderer);
	void UnRegisterRenderer(Renderer* renderer);
public:
	template<class T>
	T * AddObject(T * lpObject = nullptr, GameObject * lpParentObject = nullptr);

};

template<class T>
inline T * ObjectManager::AddObject(T * lpObject, GameObject * lpParentObject)
{
	T* obj = (T*)lpObject;

	if (!obj)
		obj = new T;

	obj->Init();
	liGameObjects.push_back(obj);
	obj->transform->UpdateTransform();

	return obj;
}

#define OBJECT ObjectManager::GetInst()