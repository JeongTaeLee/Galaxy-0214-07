#include "DXUT.h"
#include "CameraManager.h"


CameraManager::CameraManager()
	:vPos(0.f, 0.f, 0.f), vLookAt(0.f, 0.f, 0.f), vUp(0.f, 1, 0),
	vTargetPos(0.f, 0.f, 0.f), vTargetLookAt(0.f, 0.f, 0.f), vTargetUp(0.f, 0.f, 0.f),
	bLerpPos(false), bLerpLookAt(false), bLerpUp(false),
	fLerpPos(0.f), fLerpLookAt(0.f), fLerpUp(0.f)

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
	if (bLerpPos)
	{
		Vector3 vLength = vTargetPos - vPos;
		float fLength	= D3DXVec3Length(&vLength);

		if (0.1f > fLength)
		{
			bLerpPos = false;
			vPos = vTargetPos;
			vTargetPos = Vector3(0.f, 0.f, 0.f);
		}
		else
			D3DXVec3Lerp(&vPos, &vPos, &vTargetPos, fLerpPos);
	}
	if (bLerpLookAt)
	{
		Vector3 vLength = vTargetLookAt - vLookAt;
		float fLength = D3DXVec3Length(&vLength);

		if (0.1f > fLength)
		{
			bLerpLookAt = false;
			vLookAt = vTargetLookAt;
			vTargetLookAt = Vector3(0.f, 0.f, 0.f);
		}
		else
		{
			D3DXVec3Lerp(&vLookAt, &vLookAt, &vTargetLookAt, fLerpLookAt);
		}
	}
	if (bLerpUp)
	{
		Vector3 vLength = vTargetUp - vUp;
		float fLength = D3DXVec3Length(&vLength);

		if (0.1f > fLength)
		{
			bLerpUp = false;
			vUp = vTargetUp;
			vTargetUp = Vector3(0.f, 0.f, 0.f);
		}
		else
			D3DXVec3Lerp(&vUp, &vUp, &vTargetUp, fLerpUp);
	}

	SetViewMatrix();
}

void CameraManager::SetViewMatrix()
{
	D3DXMatrixLookAtLH(&matView, &vPos, &vLookAt, &vUp);
}

void CameraManager::SetProjMatrix()
{
	D3DXMatrixPerspectiveFovLH(&matProj, D3DXToRadian(60), 16.f / 9.f, 1.f, 50000.f);
	D3DXMatrixOrthoLH(&matOrthoProj, (float)WINSIZEX, (float)WINSIZEY, 1.f, 50000.f);
}

void CameraManager::SetCameraTransform()
{
	g_device->SetTransform(D3DTS_VIEW, &matView);
}

void CameraManager::SetProjectionTransform()
{
	g_device->SetTransform(D3DTS_PROJECTION, &matProj);
}

void CameraManager::SetOrthoProjectionTransform()
{
	g_device->SetTransform(D3DTS_PROJECTION, &matOrthoProj);
}

void CameraManager::SetCameraPos(const Vector3& _vPos, bool _bLerpPos, float _fLerp)
{
	if (vPos == _vPos)
		return;

	fLerpPos = _fLerp;

	bLerpPos = _bLerpPos;

	if (bLerpPos)
		vTargetPos = _vPos;
	else
		vPos = _vPos;
}

void CameraManager::SetCameraLookAt(const Vector3& _vLookAt, bool _bLerpLookAt, float _fLerp)
{
	if (vLookAt == _vLookAt)
		return;

	fLerpLookAt = _fLerp;

	bLerpLookAt = _bLerpLookAt;

	if (bLerpLookAt)
		vTargetLookAt = _vLookAt;
	else
		vLookAt = _vLookAt;
}

void CameraManager::SetCameraUp(const Vector3& _vUp, bool _bLerpUp, float _fLerp)
{
	if (vUp == _vUp)
		return;
	
	fLerpUp = _fLerp;

	bLerpUp = _bLerpUp;

	if (bLerpUp)
		vTargetUp = _vUp;
	else
		vUp = _vUp;
}

