#include "DXUT.h"
#include "MonsterFlight.h"

//Manager
#include "TimeManager.h"

//Component
#include "Transform.h"

#include "PlayerAirplane.h"
#include "MonsterAirPlane.h"
#include "MonsterCreater.h"
MonsterFlight::MonsterFlight()
	:lpPlayer(nullptr), vOriginDir(0.f, 0.f, 0.f), fSpeed(0.f)
{
}


MonsterFlight::~MonsterFlight()
{
}

void MonsterFlight::Update()
{
	GetSLerpLookAt(lpPlayer->transform->worldPos, transform->worldPos, transform->qRot, 0.015f);

	Vector3 vDir;

	Matrix matRot;
	D3DXMatrixRotationQuaternion(&matRot, &transform->qRot);
	D3DXVec3TransformNormal(&vDir, &vOriginDir, &matRot);

	transform->pos += vDir * (fSpeed * Et);

}

void MonsterFlight::AddAirPlane(MonsterAirPlane* lpMonster)
{
	lpMonster->SetMonster(lpCreater, lpPlayer, vOriginDir, Vector3(0.f, 0.f, 1.f));
}
