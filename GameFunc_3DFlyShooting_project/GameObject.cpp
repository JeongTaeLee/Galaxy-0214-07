#include "DXUT.h"
#include "GameObject.h"

//Component
#include "Component.h"
#include "Transform.h"

GameObject::GameObject()
	:transform(nullptr), lpParent(nullptr),
	bActive(false), bDestroy(false)
{
	transform = AC(Transform);
}


GameObject::~GameObject()
{
	for (auto Iter : liComponents)
	{
		Iter->Release();
		SAFE_DELETE(Iter);
	}
	liComponents.clear();

	if (lpParent)
		lpParent->DeleteChild(this);

	for (auto Iter : liChild)
	{
		Iter->SetParent(nullptr);
		Iter->SetDestroy(true);
	}
	liChild.clear();
}

void GameObject::ComUpdate()
{
	for (auto Iter : liComponents)
		Iter->Update();
}

void GameObject::DeleteChild(GameObject * lpChild)
{
	for (auto Iter = liChild.begin(); Iter != liChild.end();)
	{
		if (*Iter == lpChild)
		{
			(*Iter)->SetDestroy(true);
			Iter = liChild.erase(Iter);
			break;
		}
		else
			++Iter;
	}
}
