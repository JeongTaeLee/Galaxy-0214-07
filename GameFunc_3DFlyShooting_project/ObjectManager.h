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

	std::list<Renderer*> liRenderers;

	std::list<Collider*> liColliders;
public:
	ObjectManager();
	virtual ~ObjectManager();

	void Reset();
	void Update();
	void Render();
	void CollisionProcess();
public:
	Renderer* RegisterRenderer(Renderer* renderer);
	void UnRegisterRenderer(Renderer* renderer);

public:
	Collider* RegisterCollider(Collider* collider);
	void UnRegisterCollider(Collider * collider);
public:
	template<class T>
	T * AddObject(T * lpObject = nullptr, GameObject * lpParentObject = nullptr);

	GameObject* FindWithTag(const std::string& key);
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