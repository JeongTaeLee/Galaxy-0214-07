#include "DXUT.h"
#include "AirPlane.h"

//Manager
#include "TimeManager.h"

//Component
#include "Transform.h"
#include "ShaderRenderer.h"

AirPlane::AirPlane()
	:lpRenderer(nullptr), 
	fMaxSpeed(0.f), fSpeed(0.f),
	fYawAngle(0.f), fPitchAngle(0.f), fRollAngle(0.f)
{
	vAxis[E_AXIS_UP] = Vector3(0.f, 1.f, 0.f);
	vAxis[E_AXIS_RIGHT] = Vector3(1.f, 0.f, 0.f);
	vAxis[E_AXIS_FORWARD] = Vector3(0.f, 0.f, 1.f);

}


AirPlane::~AirPlane()
{
}


void AirPlane::YawRotation(float fAngle)
{
	Quaternion qRot;
	D3DXQuaternionRotationAxis(&qRot, &vAxis[E_AXIS_UP], fAngle);
	transform->qRot = transform->qRot * qRot;
	
	Matrix matRot;
	D3DXMatrixRotationQuaternion(&matRot, &qRot);
	D3DXVec3TransformNormal(&vAxis[E_AXIS_RIGHT], &vAxis[E_AXIS_RIGHT], &matRot);
	D3DXVec3TransformNormal(&vAxis[E_AXIS_FORWARD], &vAxis[E_AXIS_FORWARD], &matRot);

}

void AirPlane::RollRotation(float fAngle)
{
	Quaternion qRot;
	D3DXQuaternionRotationAxis(&qRot, &vAxis[E_AXIS_FORWARD], fAngle);
	transform->qRot = transform->qRot * qRot;

	Matrix matRot;
	D3DXMatrixRotationQuaternion(&matRot, &qRot);
	D3DXVec3TransformNormal(&vAxis[E_AXIS_RIGHT], &vAxis[E_AXIS_RIGHT], &matRot);
	D3DXVec3TransformNormal(&vAxis[E_AXIS_UP], &vAxis[E_AXIS_UP], &matRot);
}

void AirPlane::PitchRotation(float fAngle)
{
	Quaternion qRot;
	D3DXQuaternionRotationAxis(&qRot, &vAxis[E_AXIS_RIGHT], fAngle);
	transform->qRot = transform->qRot * qRot;

	Matrix matRot;
	D3DXMatrixRotationQuaternion(&matRot, &qRot);
	D3DXVec3TransformNormal(&vAxis[E_AXIS_FORWARD], &vAxis[E_AXIS_FORWARD], &matRot);
	D3DXVec3TransformNormal(&vAxis[E_AXIS_UP], &vAxis[E_AXIS_UP], &matRot);
}

void AirPlane::SetAirPlaneMatrix()
{
	if (fRollAngle)
		AirPlane::RollRotation(fRollAngle);
	if (fYawAngle)
		AirPlane::YawRotation(fYawAngle);
	if (fPitchAngle)
		AirPlane::PitchRotation(fPitchAngle);

	if (fRollAngle || fYawAngle || fPitchAngle)
		fRollAngle = fYawAngle = fPitchAngle = 0.f;

	D3DXMatrixTranslation(&transform->matPos, transform->pos.x, transform->pos.y, transform->pos.z);
	D3DXMatrixScaling(&transform->matScale, transform->scale.x, transform->scale.y, transform->scale.z);
}

void AirPlane::SetAxis()
{
	Matrix matRot;	
	D3DXMatrixRotationQuaternion(&matRot, &transform->qRot);

	D3DXVec3TransformNormal(&vAxis[E_AXIS_FORWARD], &vAxis[E_AXIS_FORWARD], &matRot);
	D3DXVec3TransformNormal(&vAxis[E_AXIS_RIGHT], &vAxis[E_AXIS_RIGHT], &matRot);
	D3DXVec3TransformNormal(&vAxis[E_AXIS_UP], &vAxis[E_AXIS_UP], &matRot);
}
