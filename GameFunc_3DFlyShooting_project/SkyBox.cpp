#include "DXUT.h"
#include "SkyBox.h"

//Manager
#include "ImageManager.h"
#include "CameraManager.h"

//Component
#include "Renderer.h"
#include "Transform.h"

SkyBox::SkyBox()
{
}


SkyBox::~SkyBox()
{
}

void SkyBox::Init()
{
	lpRenderer = AC(Renderer);
	lpRenderer->LoadMesh(IMAGE.LoadObjFile("SkyBox", "./rs/obj/SkyBox/SkyBox01.obj"));

	lpRenderer->SetRenderBegin([&]() { 
		g_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		g_device->SetRenderState(D3DRS_ZENABLE, false);
		g_device->SetRenderState(D3DRS_LIGHTING, false);
		
		g_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		g_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		g_device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

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
