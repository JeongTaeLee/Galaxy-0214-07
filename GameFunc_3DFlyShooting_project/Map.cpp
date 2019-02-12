#include "DXUT.h"
#include "Map.h"

//Manager
#include "ImageManager.h"
#include "CameraManager.h"

//Component
#include "Renderer.h"
#include "ShaderRenderer.h"
#include "Transform.h"
#include "SphereCollider.h"

Map::Map()
	:lpRenderer(nullptr)
{
}


Map::~Map()
{
}

void Map::Init()
{
	transform->pos = Vector3(0.f, 0.f, 150.f);
	transform->scale = Vector3(1.f, 1.f, 1.f);

	lpRenderer = AC(ShaderRenderer);
	lpRenderer->LoadMesh(IMAGE.LoadObjFile("TestObject", "./rs/obj/TestObject/TestObject.obj"));
	lpRenderer->SetEffect(IMAGE.LoadEffect("NoMapLighting", "NoMapLighting.fx"));

	lpRenderer->SetRenderBegin(
		[&]() {

			lpRenderer->SetShaderVector("gWorldCamera", &Vector4(CAMERA.GetPos(), 1.f));
		});

	AC(SphereCollider)->InitSphere(Vector3(0.f, 0.f, 0.f), 50.f);
}
