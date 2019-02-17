#pragma once
#include "singleton.h"
#include "Transform.h"

class GameObject;
class Renderer;
class ShaderRenderer;
class UIRenderer;
class BBRenderer;

class ObjectManager :
	public singleton<ObjectManager>
{
private:
	std::list<GameObject*> liGameObjects;

	std::list<Renderer*> liRenderers;
	std::list<UIRenderer*> liUiRenderers;
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

	UIRenderer* RegisterUIRenderer(UIRenderer * lpUIRenderer);
	void UnRegisterUIRenderer(UIRenderer* lpUIRenderer);

public:
	Collider* RegisterCollider(Collider* collider);
	void UnRegisterCollider(Collider * collider);
public:
	template<class T>
	T * AddObject(GameObject * lpParentObject = nullptr,T * lpObject = nullptr);

	GameObject* FindWithTag(const std::string& key);
};

template<class T>
inline T * ObjectManager::AddObject(GameObject * lpParentObject, T* lpObject)
{
	T* obj = (T*)lpObject;

	if (!obj)
		obj = new T;

	if (lpParentObject)
	{
		obj->SetParent(lpParentObject);
		lpParentObject->AddChild(obj);
	}
	
	obj->Init();
	liGameObjects.push_back(obj);
	obj->transform->UpdateTransform();

	return obj;
}

#define OBJECT ObjectManager::GetInst()