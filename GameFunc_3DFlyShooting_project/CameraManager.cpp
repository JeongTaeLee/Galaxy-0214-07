#include "DXUT.h"
#include "CameraManager.h"


CameraManager::CameraManager()
	:vPos(0.f, 0.f, 0.f), vLookAt(0.f, 0.f, 0.f), vUp(0.f, 1, 0)
{
	SetProjMatrix();
	SetViewMatrix();

	SetCameraTransform();
	SetProjectionTransform();
}


CameraManager::~CameraManager()
{
}

void CameraManager::Update()
{
	SetViewMatrix();
}

void CameraManager::SetViewMatrix()
{
	D3DXMatrixLookAtLH(&matView, &vPos, &vLookAt, &vUp);
	v4Pos = Vector4(vPos.x, vPos.y, vPos.z, 1.f);
}

void CameraManager::SetProjMatrix()
{
	D3DXMatrixPerspectiveFovLH(&matProj, D3DXToRadian(90), 16.f / 9.f, 1.f, 50000.f);
}

void CameraManager::SetCameraTransform()
{
	g_device->SetTransform(D3DTS_VIEW, &matView);
}

void CameraManager::SetProjectionTransform()
{
	g_device->SetTransform(D3DTS_PROJECTION, &matProj);
}

void CameraManager::SetCameraInfo(const Vector3 & _vPos, const Vector3 & _vLook)
{
	vPos = _vPos;
	vLookAt = _vLook;
}
