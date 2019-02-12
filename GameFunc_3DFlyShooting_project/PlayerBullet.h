#pragma once
#include "Bullet.h"
class PlayerBullet :
	public Bullet
{
private:	

public:
	PlayerBullet();
	virtual ~PlayerBullet();

	virtual void Init()	override;
};

