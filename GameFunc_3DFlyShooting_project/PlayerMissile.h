#pragma once
#include "Missile.h"

class SphereCollider;

class PlayerMissile :
	public Missile
{
public:
	PlayerMissile();
	~PlayerMissile();

	virtual void ReceiveCollider(Collider* Other) override;
};

