#include "DXUT.h"
#include "Water.h"

//Manager
#include "ImageManager.h"
#include "CameraManager.h"

//Component
#include "ShaderRenderer.h"

Water::Water()
	:lpRenderer(nullptr), fWaterWave(0.f)
{
}


Water::~Water()
{
}

void Water::Init()
{
	lpRenderer = AC(ShaderRenderer);
	lpRenderer->LoadMesh(IMAGE.LoadObjFile("Water", "./rs/obj/Water/Water.obj"));
	lpRenderer->SetEffect(IMAGE.LoadEffect("Water", "Water.fx"));

	lpRenderer->SetRenderBegin(
		[&]() {

			lpRenderer->SetShaderVector("gWorldCamera", &CAMERA.GetV4Pos());
			lpRenderer->SetShaderTexture("gMap", lpRenderer->GetMesh()->GetTexture(0));
			lpRenderer->SetShaderTexture("gBumpMap", LOADTEX("WaterBumpMap", "./rs/obj/Water/NormalMap.png"));
			lpRenderer->SetShaderFloat("gWaterWave", fWaterWave);
			
		});
}

void Water::Update()
{
}
