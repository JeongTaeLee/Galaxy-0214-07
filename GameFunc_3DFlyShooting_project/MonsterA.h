#pragma once
#include "MonsterAirPlane.h"
class MonsterA :
	public MonsterAirPlane
{
private:
	bool bSecondAttack;
public:
	MonsterA();
	virtual ~MonsterA();

	virtual void Init()	override;
	virtual void Attack() override;
};

