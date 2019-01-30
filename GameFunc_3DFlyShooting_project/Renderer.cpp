#include "DXUT.h"
#include "Renderer.h"
#include "OBJLoader.h"

//Manager
#include "ObjectManager.h"
#include "ImageManager.h"
#include "CameraManager.h"
Renderer::Renderer()
	:lpMesh(nullptr), RenderBegin(nullptr), RenderEnd(nullptr)
{
}


Renderer::~Renderer()
{
}

void Renderer::Init()
{
	OBJECT.RegisterRenderer(this);
}

void Renderer::Release()
{
	OBJECT.UnRegisterRenderer(this);
}

void Renderer::Render()
{
	transform->SetTransform();
	
	if(RenderBegin)
		RenderBegin();

	for (size_t i = 0; i < lpMesh->vMaterial.size(); ++i)
	{
		g_device->SetMaterial(&(lpMesh->vMaterial[i]->material));

		if (lpMesh->vMaterial[i]->map)
			g_device->SetTexture(0, lpMesh->vMaterial[i]->map->lpD3DTexture);
		
		lpMesh->lpD3DXMesh->DrawSubset(i);
	}

	if (RenderEnd)
		RenderEnd();
}

void Renderer::LoadMesh(Mesh* _lpMesh)
{
	lpMesh = _lpMesh;
}

void Renderer::SetRenderBegin(std::function<void()> _RenderBegin)
{
	RenderBegin = _RenderBegin;
}

void Renderer::SetRenderEnd(std::function<void()> _RenderEnd)
{
	RenderEnd = _RenderEnd;
}
