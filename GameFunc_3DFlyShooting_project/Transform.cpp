#include "DXUT.h"
#include "Transform.h"
#include "GameObject.h"


Transform::Transform()
	:pos(0.f, 0.f, 0.f), rot(0.f, 0.f, 0.f),
	scale(1.f, 1.f, 1.f), eUpdateType(E_UPDATE_01)
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
	switch (eUpdateType)
	{
	case E_UPDATE_01:
		UpdateTransform01();
		break;
	case E_UPDATE_02:
		UpdateTransform02();
		break;
	case E_UPDATE_UI:
		UpdateTrasformUI();
		break;
	default:
		break;
	}
}

void Transform::UpdateTransform01()
{
	D3DXMatrixTranslation(&matPos, pos.x, pos.y, pos.z);

	D3DXQuaternionRotationYawPitchRoll(&qRot, rot.y, rot.x, rot.z);
	D3DXMatrixRotationQuaternion(&matRot, &qRot);

	D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);
	
	matWorld	= matScale * matRot * matPos;

	if (gameObject->GetParent())
		matWorld = matWorld * gameObject->GetParent()->transform->matWorld;

	memcpy(&worldPos, &matWorld._41, sizeof(Vector3));

}

void Transform::UpdateTransform02()
{
	D3DXMatrixTranslation(&matPos, pos.x, pos.y, pos.z);

	D3DXMatrixRotationQuaternion(&matRot, &qRot);

	D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);
	
	matWorld	= matScale * matRot * matPos;

	if (gameObject->GetParent())
		matWorld = gameObject->GetParent()->transform->matWorld * matWorld;

	worldPos = Vector3(matWorld._41, matWorld._42, matWorld._43);
}

void Transform::UpdateTrasformUI()
{
	Matrix matRot;
	Matrix matScale;
	Matrix matPos;

	D3DXMatrixScaling(&matScale, scale.x, scale.y, 0.f);

	D3DXMatrixRotationZ(&matRot, rot.z);

	D3DXMatrixTranslation(&matPos, pos.x, pos.y, 0.f);

	matWorld = matScale * matRot * matPos;

	if (gameObject->GetParent())
	{
		D3DXMatrixScaling(&matScale, gameObject->GetParent()->transform->scale.x,
			gameObject->GetParent()->transform->scale.y, 0.f);

		D3DXMatrixRotationZ(&matRot, gameObject->GetParent()->transform->rot.z);

		D3DXMatrixTranslation(&matPos, gameObject->GetParent()->transform->pos.x, gameObject->GetParent()->transform->pos.y, 0.f);

		Matrix matParentWorld = matScale *
			matRot* matPos;

		matWorld = matWorld * matParentWorld;
	}

	memcpy(&worldPos, &matWorld._41, sizeof(Vector3));
}

void Transform::SetTransform()
{
	g_device->SetTransform(D3DTS_WORLD, &matWorld);
}