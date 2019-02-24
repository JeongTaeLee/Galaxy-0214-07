#pragma once
#include "MainMonster.h"

struct Camera;

class MiddleBossA :
	public MainMonster
{
private:
	Vector3 vFirePos01;
	Vector3 vFirePos02;

	float fMissileDelay;
	float fMissileAccrue;

public:
	MiddleBossA();
	virtual ~MiddleBossA();

public:
	virtual void Init();

	virtual void Move()	override;
	virtual void Attack()	override;
	virtual void Die() override;
	
	void AttackType01();
	void AttackType02();
};

