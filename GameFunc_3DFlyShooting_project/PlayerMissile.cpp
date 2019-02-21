#include "DXUT.h"
#include "PlayerMissile.h"

#include "SphereCollider.h"
#include "Transform.h"

PlayerMissile::PlayerMissile()
{
	sTag = "PlayerMissile";
}


PlayerMissile::~PlayerMissile()
{
}

void PlayerMissile::ReceiveCollider(Collider* Other)
{
	if (Other->gameObject->sTag == "Monster")
	{
		float fRandomScale = GetRandomNumber(150.f, 300.f);

		CreateEffectA(transform->pos, Vector3(fRandomScale, fRandomScale, 1.f), 0.01f);
		SetDestroy(true);
	}
}