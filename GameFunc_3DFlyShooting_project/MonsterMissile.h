#pragma once
#include "Missile.h"

class Collider;
class MissileCircle;

class MonsterMissile :
	public Missile
{
private:
	MissileCircle* lpMissileCircle;

	float fTargetingTime;
	float fTargetingAccrue;
public:
	MonsterMissile();
	~MonsterMissile();

	virtual void Init()		override;
	virtual void Release()	override;

	virtual void Update()	override;
	virtual void ReceiveCollider(Collider* lpOther) override;
};

