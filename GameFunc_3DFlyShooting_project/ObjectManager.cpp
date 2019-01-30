#include "DXUT.h"
#include "ObjectManager.h"

//GameObject
#include "GameObject.h"

//Component
#include "Transform.h"
#include "Renderer.h"
#include "ShaderRenderer.h"

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

	liRenderer.clear();
}

void ObjectManager::Update()
{
	for (auto Iter : liGameObjects)
	{
		Iter->Update();
		Iter->ComUpdate();
		Iter->transform->UpdateTransform();
	}

	DestroyProcess();
}

void ObjectManager::Render()
{
	for (auto Iter : liRenderer)
		Iter->Render();
}

void ObjectManager::DestroyProcess()
{
	for (auto Iter = liGameObjects.begin(); Iter != liGameObjects.end();)
	{
		if ((*Iter)->GetDestroy())
		{
			(*Iter)->Release();
			SAFE_DELETE((*Iter));
			Iter = liGameObjects.erase(Iter);
		}
		else
			++Iter;
	}
}

Renderer* ObjectManager::RegisterRenderer(Renderer* renderer)
{
	liRenderer.push_back(renderer);
	return renderer;
}

void ObjectManager::UnRegisterRenderer(Renderer* renderer)
{
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
}
