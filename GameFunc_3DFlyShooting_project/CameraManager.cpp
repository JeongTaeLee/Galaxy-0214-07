#include "DXUT.h"
#include "CameraManager.h"


CameraManager::CameraManager()
	:vPos(0.f, 0.f, 0.f), vLookAt(0.f, 0.f, 0.f), 
	vUp(0.f, 1, 0), vTargetPos(0.f, 0.f, 0.f),
	bTargeting(false), bTargetS(0.f)
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
	if (bTargeting)
	{
		D3DXVec3Lerp(&vPos, &vPos, &vTargetPos, bTargetS);

		Vector3 vLength = vTargetPos - vPos;
		float	fLength = D3DXVec3Length(&vLength);

		if (fLength < 0.1f)
		{
			vPos = vTargetPos;
			vTargetPos = Vector3(0.f, 0.f, 0.f);
			
			bTargeting = false;
		}
	}

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

void CameraManager::SetCameraInfo(const Vector3& _vPos, const Vector3& _vLook, const Vector3& _vUp, bool _bTargeting, float _bTargetS)
{
	if (vPos == _vPos)
		bTargeting = false;
	else
		bTargeting = _bTargeting;

	if (bTargeting)
	{
		vTargetPos = _vPos;
		bTargetS = _bTargetS;
	}
	else
		vPos = _vPos;
		
	vLookAt = _vLook;
	vUp = _vUp;	
}
