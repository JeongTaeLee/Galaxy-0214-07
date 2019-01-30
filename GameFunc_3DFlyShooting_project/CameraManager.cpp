#include "DXUT.h"
#include "CameraManager.h"


CameraManager::CameraManager()
	:vPos(0.f, 100.f, -100.f), vLookAt(0.f, 0.f, 0.f), vUp(0.f, 1.f, 0.f)
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
}

void CameraManager::SetProjMatrix()
{
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI * 0.5f, WINSIZEX / WINSIZEY, 1.f, 1000.f);
}

void CameraManager::SetViewTransform()
{
	g_device->SetTransform(D3DTS_VIEW, &matView);
}
