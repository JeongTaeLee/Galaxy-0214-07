#include "DXUT.h"
#include "SkyBox.h"

//Manager
#include "ImageManager.h"
#include "CameraManager.h"

//Component
#include "Renderer.h"
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
	transform->scale = Vector3(20.f, 20.f, 20.f);

	lpRenderer = AC(Renderer);
	lpRenderer->LoadMesh(IMAGE.LoadObjFile("SkyBox", "./rs/obj/Stage/Stage.obj"));

	lpRenderer->SetRenderBegin([&]() { 
		g_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		g_device->SetRenderState(D3DRS_ZENABLE, false);
		g_device->SetRenderState(D3DRS_LIGHTING, false);
		

		g_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
		g_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
		g_device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);


		});
	lpRenderer->SetRenderEnd([&]() { 
		g_device->SetRenderState(D3DRS_ZENABLE, true); 
		g_device->SetRenderState(D3DRS_LIGHTING, true);
		g_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		});

}

void SkyBox::Update()
{
	transform->pos = CAMERA.GetPos();
}
