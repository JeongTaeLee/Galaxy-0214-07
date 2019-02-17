#include "DXUT.h"
#include "BBRenderer.h"

#include "GameObject.h"
//Manager
#include"ImageManager.h"
#include"ObjectManager.h"
#include "CameraManager.h"

//Component
#include "Transform.h"

#include "Func.h"

BBRenderer::BBRenderer()
{
}

BBRenderer::~BBRenderer()
{
}

void BBRenderer::Render()
{
	Matrix matWorld;
	GetBillBoardMatrix(matWorld, transform->worldPos, transform->scale);
	g_device->SetTransform(D3DTS_WORLD, &matWorld);
	
	g_device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	g_device->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	g_device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	g_device->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	g_device->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	g_device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	g_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	g_device->SetRenderState(D3DRS_LIGHTING, false);

	g_device->SetTexture(0, lpTexture->lpD3DTexture);
	IMAGE.lpBillBoardMesh->DrawSubset(0);


	g_device->SetRenderState(D3DRS_LIGHTING, true);
	g_device->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	g_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);


}

void BBRenderer::SetTexture(texture* texture)
{
	lpTexture = texture;
}
