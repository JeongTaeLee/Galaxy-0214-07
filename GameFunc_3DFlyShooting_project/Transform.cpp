#include "DXUT.h"
#include "Transform.h"


Transform::Transform()
	:pos(0.f, 0.f, 0.f), worldPos(0.f, 0.f, 0.f), 
	rot(0.f, 0.f, 0.f), scale(1.f, 1.f, 1.f),
	v4Pos(0.f, 0.f, 0.f, 1.f)
{
	D3DXMatrixIdentity(&matWorld);
}


Transform::~Transform()
{
}

void Transform::UpdateTransform()
{
	Matrix matPos;
	D3DXMatrixTranslation(&matPos, pos.x, pos.y, pos.z);

	Matrix matRotX;
	D3DXMatrixRotationX(&matRotX, rot.x);

	Matrix matRotY;
	D3DXMatrixRotationY(&matRotY, rot.y);

	Matrix matRotZ;
	D3DXMatrixRotationZ(&matRotZ, rot.z);

	Matrix matRot = matRotX * matRotY * matRotZ;

	Matrix matScale;
	D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);
	
	matWorld	= matScale * matRot * matPos;
	worldPos	= Vector3(matWorld._41, matWorld._42, matWorld._43);
	v4Pos		= Vector4(matWorld._41, matWorld._42, matWorld._43, v4Pos.w);
}

void Transform::SetTransform()
{
	g_device->SetTransform(D3DTS_WORLD, &matWorld);
}
