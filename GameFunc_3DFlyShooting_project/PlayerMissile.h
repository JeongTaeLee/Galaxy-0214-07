#pragma once
#include "Missile.h"

class SphereCollider;

class PlayerMissile :
	public Missile
{
public:
	PlayerMissile();
	~PlayerMissile();

public:

public:
	virtual void ReceiveCollider(Collider* Other) override;
};

