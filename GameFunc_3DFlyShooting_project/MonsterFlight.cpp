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
	:lpPlayer(nullptr),
	vDir(0.f, 0.f, 0.f), vOriginDir(0.f, 0.f, 0.f),
	fShortDistance(0.f), fSpeed(0.f)
{
}


MonsterFlight::~MonsterFlight()
{
}

void MonsterFlight::Init()
{
	transform->eUpdateType = TransformUpdateType::E_UPDATE_02;
}

void MonsterFlight::Update()
{
	if (lpPlayer)
	{
		if (lpPlayer->GetDestroy())
		{
			SetDestroy(true);
			return;
		}
	}

	GetSLerpLookAt(lpPlayer->transform->worldPos, transform->worldPos, transform->qRot, 0.1f);

	Matrix matRot;
	D3DXMatrixRotationQuaternion(&matRot, &transform->qRot);
	D3DXVec3TransformNormal(&vDir, &vOriginDir, &matRot);

	float fNowDistance = GetLengthVector3(lpPlayer->transform->worldPos, transform->worldPos);
	if (fShortDistance < fNowDistance)
		transform->pos += vDir * (fSpeed * Et);
	
}

void MonsterFlight::SetFlight(PlayerAirplane * _lpPlayer, const Vector3 & vPos, const Vector3& _vOriginDir, float _fShortDistance, float _fSpeed)
{
	lpPlayer = _lpPlayer; 
	transform->pos = vPos;
	vOriginDir = _vOriginDir;

	fShortDistance = _fShortDistance;
	fSpeed = _fSpeed;
}

void MonsterFlight::AddFlightMonster(MonsterAirPlane* _lpMonster, const Vector3& vPos)
{
	Quaternion qRot;
	GetLookAt(qRot, vPos + vOriginDir, vPos);

	_lpMonster->transform->pos = vPos;
	_lpMonster->transform->qRot = qRot;

}

void MonsterFlight::CompleteSetting()
{
	GetLookAt(transform->qRot, lpPlayer->transform->worldPos, transform->pos);
}
