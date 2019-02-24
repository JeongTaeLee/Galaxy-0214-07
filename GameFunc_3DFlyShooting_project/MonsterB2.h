#pragma once
#include "MonsterAirPlane.h"

class MonsterB2 :
	public MonsterAirPlane
{
public:
	MonsterB2();
	virtual ~MonsterB2();

	virtual void Init()	override;
	virtual void Attack() override;
};

