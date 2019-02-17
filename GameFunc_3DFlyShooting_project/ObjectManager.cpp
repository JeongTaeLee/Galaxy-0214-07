#include "DXUT.h"
#include "ObjectManager.h"

//GameObject
#include "GameObject.h"

//Manager
#include "ImageManager.h"
#include "CameraManager.h"

//Component
#include "Transform.h"
#include "Renderer.h"
#include "ShaderRenderer.h"
#include "Collider.h"
#include "UIRenderer.h"
#include "BBRenderer.h"

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
			(*Iter)->Release();
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
	CAMERA.SetCameraTransform();

	CAMERA.SetProjectionTransform();
	for (auto Iter : liRenderers)
	{
		if (!(Iter->gameObject->GetActive()))
			continue;

		if(Iter->bEnable)
			Iter->Render();
	}

	IMAGE.GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	for (auto Iter : liUiRenderers)
	{
		if (!(Iter->gameObject->GetActive()))
			continue;

		if (Iter->bEnable)
			Iter->Render();
	}

	IMAGE.GetSprite()->End();
}

void ObjectManager::CollisionProcess()
{
	for (auto Iter : liColliders)
		Iter->ColliderUpdate();

	for (auto Iter : liColliders)
	{
		if (!Iter->bEnable)
			continue;

		if (Iter->gameObject->GetDestroy())
			continue;

		if (!(Iter->gameObject->GetActive()))
			continue;


		for (auto Iter02 : liColliders)
		{
			if (!Iter02->bEnable)
				continue;

			if (Iter->gameObject == Iter02->gameObject)
				continue;

			if (Iter == Iter02)
				continue;

			if (Iter02->gameObject->GetDestroy())
				continue;

			if (!(Iter02->gameObject->GetActive()))
				continue;

			if (Iter->CheckCollision(Iter02))
			{
				Iter->SendCollision(Iter02);
				Iter02->SendCollision(Iter);
			}
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

}

UIRenderer* ObjectManager::RegisterUIRenderer(UIRenderer* lpUIRenderer)
{
	liUiRenderers.push_back(lpUIRenderer);
	return lpUIRenderer;
}

void ObjectManager::UnRegisterUIRenderer(UIRenderer* lpUIRenderer)
{
	liUiRenderers.remove(lpUIRenderer);
}
Collider* ObjectManager::RegisterCollider(Collider* collider)
{
	liColliders.push_back(collider);
	return collider;
}

void ObjectManager::UnRegisterCollider(Collider* collider)
{
	liColliders.remove(collider);
}

GameObject* ObjectManager::FindWithTag(const std::string& key)
{
	for (auto find : liGameObjects)
	{
		if (find->sTag == key)
			return find;
	}
	return nullptr;
}
