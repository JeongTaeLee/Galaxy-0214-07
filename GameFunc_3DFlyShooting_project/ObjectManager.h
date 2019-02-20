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

	/*너가 안봐도되는거*/
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
	/*너가 안봐도되는거*/
	Renderer* RegisterRenderer(Renderer* renderer);
	void UnRegisterRenderer(Renderer* renderer);

	UIRenderer* RegisterUIRenderer(UIRenderer * lpUIRenderer);
	void UnRegisterUIRenderer(UIRenderer* lpUIRenderer);

public:
	/*너가 안봐도되는거*/
	Collider* RegisterCollider(Collider* collider);
	void UnRegisterCollider(Collider * collider);
public:
	/*봐야되는거*/
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
	
	liGameObjects.push_back(obj);
	obj->Init();
	obj->transform->UpdateTransform();

	return obj;
}

#define OBJECT ObjectManager::GetInst()