#pragma once
#include "MonsterAirPlane.h"
class MonsterA2 :
	public MonsterAirPlane
{
private:
	bool bSecondAttack;
public:
	MonsterA2();
	virtual ~MonsterA2();

	virtual void Init()	override;
	virtual void Attack() override;
};

