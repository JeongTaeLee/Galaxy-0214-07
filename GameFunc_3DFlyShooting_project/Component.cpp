#include "DXUT.h"
#include "Component.h"

#include "GameObject.h"
#include "Transform.h"

Component::Component()
	:transform(nullptr), gameObject(nullptr)
{
}


Component::~Component()
{
}

void Component::SetInfo(GameObject * _gameObject, Transform * _transform)
{
	gameObject = _gameObject;
	transform = _transform;
}
