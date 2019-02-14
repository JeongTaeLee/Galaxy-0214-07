#pragma once
#include "Bullet.h"

class Collider;

class PlayerBullet :
	public Bullet
{
private:	

public:
	PlayerBullet();
	virtual ~PlayerBullet();

	virtual void Init()	override;
	virtual void ReceiveCollider(Collider* Other) override;
	
};

