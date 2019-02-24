#include "DXUT.h"
#include "MonsterMissile.h"

#include "TimeManager.h"
#include "ObjectManager.h"

#include "PlayerAirplane.h"
#include "MissileCircle.h"

#include "Transform.h"
#include "Collider.h"
MonsterMissile::MonsterMissile()
	:lpMissileCircle(nullptr)
{
	sTag = "MonsterMissile";

	fTargetingTime = 10.f;
	fTargetingAccrue = 0.f;
}


MonsterMissile::~MonsterMissile()
{
}

void MonsterMissile::Init()
{
	Missile::Init();

	lpMissileCircle = OBJECT.AddObject<MissileCircle>();
	lpMissileCircle->SetMissile(this);
}

void MonsterMissile::Release()
{
	lpMissileCircle->SetDestroy(true);
}

void MonsterMissile::Update()
{
	Missile::Update();

	PlayerAirplane* player = (PlayerAirplane*)lpTarget;
	player->SetLockOned();



	if (fTargetingTime <= fTargetingAccrue)
	{
		CreateEffectA(transform->worldPos, Vector3(50.f, 50.f, 50.f));
		SetDestroy(true);
		SetActive(false);
		return;
	}
	else
		fTargetingAccrue += Et;
}

void MonsterMissile::ReceiveCollider(Collider* lpOther)
{
	if (lpOther->gameObject->sTag == "PlayerAirPlane")
	{	
		float fRandomScale = GetRandomNumber(150.f, 300.f);
		                                                   
		CreateEffectA(transform->pos, Vector3(fRandomScale, fRandomScale, 1.f), 0.01f);
		SetDestroy(true);
	}
}
