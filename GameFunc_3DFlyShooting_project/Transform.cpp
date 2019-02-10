#include "DXUT.h"
#include "Transform.h"
#include "GameObject.h"


Transform::Transform()
	:pos(0.f, 0.f, 0.f), worldPos(0.f, 0.f, 0.f), 
	rot(0.f, 0.f, 0.f), scale(1.f, 1.f, 1.f),
	v4Pos(0.f, 0.f, 0.f, 1.f), bTransformUpdate(true)
{
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matRot);
	D3DXMatrixIdentity(&matScale);
	D3DXMatrixIdentity(&matPos);

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

	Matrix matRotX;
	D3DXMatrixRotationX(&matRotX, rot.x);

	Matrix matRotY;
	D3DXMatrixRotationY(&matRotY, rot.y);

	Matrix matRotZ;
	D3DXMatrixRotationZ(&matRotZ, rot.z);

	matRot = matRotX * matRotY * matRotZ;

	D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);
	
	matWorld	= matScale * matRot * matPos;

	if (gameObject->GetParent())
		matWorld = gameObject->GetParent()->transform->matWorld * matWorld;

	worldPos	= Vector3(matWorld._41, matWorld._42, matWorld._43);
	v4Pos		= Vector4(matWorld._41, matWorld._42, matWorld._43, v4Pos.w);
}

void Transform::UpdateTransform02()
{
	matWorld = matScale * matRot * matPos;

	if (gameObject->GetParent())
		matWorld = gameObject->GetParent()->transform->matWorld * matWorld;

	worldPos = Vector3(matWorld._41, matWorld._42, matWorld._43);
	v4Pos = Vector4(matWorld._41, matWorld._42, matWorld._43, v4Pos.w);
}

void Transform::SetTransform()
{
	g_device->SetTransform(D3DTS_WORLD, &matWorld);
}
