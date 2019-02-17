#pragma once
#include "Bullet.h"

class Collider;

class MonsterBullet :
	public Bullet
{
private:
	
public:
	MonsterBullet();
	virtual ~MonsterBullet();

	virtual void Init()	override;
	virtual void ReceiveCollider(Collider* lpOther) override;
};

