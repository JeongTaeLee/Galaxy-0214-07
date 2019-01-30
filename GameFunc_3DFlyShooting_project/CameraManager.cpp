#include "DXUT.h"
#include "CameraManager.h"


CameraManager::CameraManager()
	:vPos(0.f, 250.f, -350.f), vLookAt(0.f, 200.f, 50.f), vUp(0.f, 1, 0)
{
	SetProjMatrix();
	SetViewMatrix();

	g_device->SetTransform(D3DTS_PROJECTION, &matProj);
}


CameraManager::~CameraManager()
{
}

void CameraManager::Update()
{
}


void CameraManager::SetViewMatrix()
{
	D3DXMatrixLookAtLH(&matView, &vPos, &vLookAt, &vUp);
	v4Pos = Vector4(vPos.x, vPos.y, vPos.z, 1.f);
}

void CameraManager::SetProjMatrix()
{
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI * 0.5f, WINSIZEX / WINSIZEY, 1.f, 1000.f);
}

void CameraManager::SetViewTransform()
{
	g_device->SetTransform(D3DTS_VIEW, &matView);
}
