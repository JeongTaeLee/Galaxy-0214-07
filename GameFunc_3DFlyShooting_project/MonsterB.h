#pragma once
#include "MonsterAirPlane.h"
class MonsterB :
	public MonsterAirPlane
{
public:
	MonsterB();
	virtual ~MonsterB();

	virtual void Init()	override;
	virtual void Attack() override;
};

