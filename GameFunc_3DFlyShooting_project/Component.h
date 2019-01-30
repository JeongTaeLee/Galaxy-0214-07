#pragma once

class GameObject;
class Transform;

class Component
{
public:
	GameObject * gameObject;
	Transform * transform;
private:
public:
	Component();
	virtual ~Component();

	virtual void Init() {}
	virtual void Release() {}
	virtual void Update() {}
	virtual void Render() {}

public:
	void SetInfo(GameObject * _gameObject, Transform * _transform);
};

