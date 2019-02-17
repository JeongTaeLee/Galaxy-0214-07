#pragma once
class Transform;
class Component;
class Collider;

class GameObject
{
public:
	Transform * transform;
	std::string sTag;
private:
	std::list<Component*> liComponents;
	std::list<GameObject*> liChild;
protected:
	GameObject * lpParent;	

private:
	bool bActive;
	bool bDestroy;

public:
	GameObject();
	virtual ~GameObject();

	virtual void Init()		{}
	virtual void Release()  {}
	virtual void Update()	{}

public:
	virtual void ComUpdate();

public:
	bool GetActive()				{ return bActive; }
	void SetActive(bool _bActive)	{ bActive = _bActive; }

	bool GetDestroy()				{ return bDestroy; }
	void SetDestroy(bool _bDestroy) { bDestroy = _bDestroy; }
public:
	GameObject * GetParent()				{ return lpParent; }
	void SetParent(GameObject * _lpParent)	{ lpParent = _lpParent; }

	void AddChild(GameObject * lpChild) { liChild.push_back(lpChild); }
	void DeleteChild(GameObject * lpChild);

public:
	void SendCollider(Collider * collider);
	virtual void ReceiveCollider(Collider* collider) {};
public:
	template<class T>
	T * AddComponent();
	template<class T>
	T * GetComponent();
	template<class T>
	void DeleteComponent();
};

template<class T>
inline T * GameObject::AddComponent()
{
	T * inst = new T;

	inst->SetInfo(this, transform);
	inst->Init();
	liComponents.push_back(inst);
	
	return inst;
}

template<class T>
inline T * GameObject::GetComponent()
{
	for (auto Iter : liComponents)
	{
		T * inst = dynamic_cast <T*>(Iter);

		if (inst)
			return inst;
	}

	return nullptr;
}

template<class T>
inline void GameObject::DeleteComponent()
{
	for (auto Iter = liComponents.begin(); Iter != liComponents.end();)
	{
		T * inst = dynamic_cast<T*>((*Iter));

		if (inst)
		{
			Iter->Release();
			SAFE_DELETE(Iter);
			Iter = liComponents.erase(Iter);
		}
		else
			++Iter;
	}
}

#define AC(com) AddComponent<com>()
#define GC(com) GetComponent<com>()
#define DC(com) DeleteComponent<com>()