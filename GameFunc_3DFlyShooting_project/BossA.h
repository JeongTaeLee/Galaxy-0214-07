#pragma once
#include "MonsterAirPlane.h"
class BossA :
	public MonsterAirPlane
{
public:
	BossA();
	virtual ~BossA();

	virtual void Init()	override;

	virtual void Update()	override;

	virtual void Attack() override;
};

