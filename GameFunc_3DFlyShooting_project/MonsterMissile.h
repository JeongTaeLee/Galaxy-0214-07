#pragma once
#include "Missile.h"

class Collider;

class MonsterMissile :
	public Missile
{
private:
public:
	MonsterMissile();
	~MonsterMissile();

	virtual void Update()	override;

	virtual void ReceiveCollider(Collider* lpOther) override;
};

