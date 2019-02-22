#include "DXUT.h"
#include "MonsterMissile.h"

#include "PlayerAirplane.h"
#include "Transform.h"

#include "Collider.h"
MonsterMissile::MonsterMissile()
{
	sTag = "MonsterMissile";
}


MonsterMissile::~MonsterMissile()
{
}

void MonsterMissile::Update()
{
	Missile::Update();

	if (lpTargetObject)
	{
		PlayerAirplane* player = (PlayerAirplane*)lpTargetObject;
		player->SetLockOned();
	}
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
