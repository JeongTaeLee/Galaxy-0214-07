#include "DXUT.h"
#include "MonsterAirPlane.h"
#include "Func.h"

//Manager
#include "ImageManager.h"
#include "ObjectManager.h"

//Component
#include "ShaderRenderer.h"
#include "SphereCollider.h"
MonsterAirPlane::MonsterAirPlane()
	:lpPlayer(nullptr), lpCollider(nullptr), fHp(0.f)
{
}


MonsterAirPlane::~MonsterAirPlane()
{
}

void MonsterAirPlane::Init()
{
	transform->bNoneRotationUpdate = false; 

	lpPlayer = OBJECT.FindWithTag("PlayerAirPlane");

	lpRenderer = AC(ShaderRenderer);
	lpCollider = AC(SphereCollider);
	lpRenderer->SetEffect(IMAGE.LoadEffect("Lighting", "Lighting.fx"));
}

void MonsterAirPlane::LookAtPlayer()
{
	Vector3 vDir = lpPlayer->transform->worldPos - transform->worldPos;
	normalize(vDir);

	Matrix matRot;
	D3DXMatrixLookAtLH(&matRot, &D3DXVECTOR3(0, 0, 0), &vDir,
		&D3DXVECTOR3(0, 1, 0));
	D3DXMatrixTranspose(&matRot, &matRot); //

	D3DXQUATERNION currQ;
	D3DXQuaternionRotationMatrix(&currQ, &matRot);
	D3DXQuaternionSlerp(&transform->qRot, &transform->qRot, &currQ, 0.25f);
}
