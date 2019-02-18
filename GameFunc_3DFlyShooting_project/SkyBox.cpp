#include "DXUT.h"
#include "SkyBox.h"

//Manager
#include "ImageManager.h"
#include "CameraManager.h"

//Component
#include "Renderer.h"
#include "ShaderRenderer.h"
#include "Transform.h"

SkyBox::SkyBox()
	:lpRenderer(nullptr)
{
}


SkyBox::~SkyBox()
{
}

void SkyBox::Init()
{
	transform->scale = Vector3(100, 100, 100);

	lpRenderer = AC(ShaderRenderer);
	lpRenderer->LoadMesh(IMAGE.LoadObjFile("SkyBox_Sphere", "./rs/obj/SkyBox_Sphere/Stage.obj"));
	lpRenderer->SetEffect(IMAGE.LoadEffect("SkyBox", "SkyBox.fx"));

	lpRenderer->SetRenderBegin([&]() { 
		lpRenderer->SetShaderTexture("gMap", lpRenderer->GetMesh()->GetDiffuseMap(0));

		g_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
		g_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
		g_device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);
	});
}

void SkyBox::Update()
{
	transform->pos = CAMERA.GetPos();

}
