#include "DXUT.h"
#include "ObjectManager.h"

//GameObject
#include "GameObject.h"

//Component
#include "Transform.h"
#include "Renderer.h"
#include "ShaderRenderer.h"
#include "Collider.h"

ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
}

void ObjectManager::Reset()
{
	for (auto Iter : liGameObjects)
		SAFE_DELETE(Iter);
	liGameObjects.clear();

	liRenderers.clear();
}

void ObjectManager::Update()
{
	for (auto Iter = liGameObjects.begin(); Iter != liGameObjects.end();)
	{
		if ((*Iter)->GetDestroy())
		{
			SAFE_DELETE(*Iter);
			Iter = liGameObjects.erase(Iter);
		}
		else
		{
			if (!((*Iter)->GetActive()))
				continue;

			(*Iter)->Update();
			(*Iter)->ComUpdate();

			(*Iter)->transform->UpdateTransform();
			++Iter;
		}
	}

	CollisionProcess();
}

void ObjectManager::Render()
{
	for (auto Iter : liRenderers)
	{
		if (!(Iter->gameObject->GetActive()))
			continue;

		if(Iter->bEnable)
			Iter->Render();
	}
}

void ObjectManager::CollisionProcess()
{
	for (auto Iter : liColliders)
	{
		if (Iter->gameObject->GetDestroy())
			continue;

		if (!(Iter->gameObject->GetActive()))
			continue;

		if (!(Iter->bEnable))
			continue;

		for (auto Iter02 : liColliders)
		{
			if (Iter->gameObject == Iter02->gameObject)
				continue;

			if (Iter == Iter02)
				continue;

			if (Iter02->gameObject->GetDestroy())
				continue;

			if (!(Iter02->gameObject->GetActive()))
				continue;

			if (!(Iter02->bEnable))
				continue;

			Iter->ColliderUpdate();
			Iter02->ColliderUpdate();

			if (Iter->CheckCollision(Iter02))
				Iter02->SendCollision(Iter);
		}
	}
}

Renderer* ObjectManager::RegisterRenderer(Renderer* renderer)
{
	liRenderers.push_back(renderer);
	return renderer;
}

void ObjectManager::UnRegisterRenderer(Renderer* renderer)
{
	liRenderers.remove(renderer);
	/*
	for (auto Iter = liRenderer.begin(); Iter != liRenderer.end();)
	{
		if ((*Iter) == renderer)
		{
			Iter = liRenderer.erase(Iter);
			break;
		}
		else
			++Iter;
	}
	*/
}

Collider* ObjectManager::RegisterCollider(Collider* collider)
{
	if (!collider)
		return nullptr;

	liColliders.push_back(collider);
	return collider;
}

void ObjectManager::UnRegisterCollider(Collider* collider)
{
	if (!collider)
		return;

	liColliders.remove(collider);
}
