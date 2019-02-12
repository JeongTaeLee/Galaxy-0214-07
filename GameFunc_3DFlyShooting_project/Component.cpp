#include "DXUT.h"
#include "Component.h"

#include "GameObject.h"
#include "Transform.h"

Component::Component()
	:transform(nullptr), gameObject(nullptr), bEnable(true)
{
}


Component::~Component()
{
}

void Component::ReceiveCollider(Collider* collider)
{

}

void Component::SetInfo(GameObject * _gameObject, Transform * _transform)
{
	gameObject = _gameObject;
	transform = _transform;
}
