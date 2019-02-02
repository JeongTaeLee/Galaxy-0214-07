#include "DXUT.h"
#include "Map.h"

//Manager
#include "ImageManager.h"
#include "CameraManager.h"

//Component
#include "Renderer.h"
#include "ShaderRenderer.h"

Map::Map()
	:lpRenderer(nullptr)
{
}


Map::~Map()
{
}

void Map::Init()
{
	lpRenderer = AC(ShaderRenderer);
	lpRenderer->LoadMesh(IMAGE.LoadObjFile("TestObject", "./rs/obj/TestObject/TestObject.obj"));
	lpRenderer->SetEffect(IMAGE.LoadEffect("NoMapLighting", "NoMapLighting.fx"));

	lpRenderer->SetRenderBegin(
		[&]() {

			lpRenderer->SetShaderVector("gWorldCamera", &CAMERA.GetV4Pos());
		});
}
