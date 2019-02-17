#pragma once
#include "MonsterAirPlane.h"
class MonsterA :
	public MonsterAirPlane
{
private:
	
public:
	MonsterA();
	virtual ~MonsterA();

	virtual void Init()	override;
};

