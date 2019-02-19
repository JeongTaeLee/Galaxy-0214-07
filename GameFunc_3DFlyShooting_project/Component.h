#pragma once

class GameObject;
class Transform;
class Collider;

class Component
{
public:
	GameObject* gameObject;
	Transform* transform;

protected:
	bool bEnable;
public:
	Component();
	virtual ~Component();

	virtual void Init() {}
	virtual void Release() {}
	virtual void Update() {}
	virtual void Render() {}

public:
	virtual void ReceiveCollider(Collider* collider);
	virtual void SetEnable(bool _bEnable) { bEnable = _bEnable; }
	bool GetEnable() { return bEnable; }

public:
	void SetInfo(GameObject * _gameObject, Transform * _transform);
};

