#include "DXUT.h"
#include "Transform.h"
#include "GameObject.h"


Transform::Transform()
	:pos(0.f, 0.f, 0.f), worldPos(0.f, 0.f, 0.f), 
	rot(0.f, 0.f, 0.f), scale(1.f, 1.f, 1.f),
	bTransformUpdate(true)
{
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matScale);
	D3DXMatrixIdentity(&matPos);

	D3DXQuaternionRotationYawPitchRoll(&qRot, rot.y, rot.x, rot.z);
	D3DXMatrixRotationQuaternion(&matRot, &qRot);
}


Transform::~Transform()
{
}

void Transform::UpdateTransform()
{
	if (!bTransformUpdate)
	{
		UpdateTransform02();
		return;
	}

	D3DXMatrixTranslation(&matPos, pos.x, pos.y, pos.z);

	D3DXQuaternionRotationYawPitchRoll(&qRot, rot.y, rot.x, rot.z);
	D3DXMatrixRotationQuaternion(&matRot, &qRot);

	D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);
	
	matWorld	= matScale * matRot * matPos;

	if (gameObject->GetParent())
		matWorld = gameObject->GetParent()->transform->matWorld * matWorld;

	worldPos	= Vector3(matWorld._41, matWorld._42, matWorld._43);
}

void Transform::UpdateTransform02()
{
	D3DXMatrixRotationQuaternion(&matRot, &qRot);

	matWorld = matScale * matRot * matPos;

   	if (gameObject->GetParent())
		matWorld = gameObject->GetParent()->transform->matWorld * matWorld;

	worldPos = Vector3(matWorld._41, matWorld._42, matWorld._43);
}

void Transform::SetTransform()
{
	g_device->SetTransform(D3DTS_WORLD, &matWorld);
}
