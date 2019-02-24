#pragma once
#include "MainMonster.h"

class BossHpBar;

class BossA :
	public MainMonster
{
private:
	Vector3 vOriginFirePos;
	Vector3 vMonsterCreaterPos;
	
	float fCreateDelay;
	float fCreateAccrue;

	float fMissileDelay;
	float fMissileAccrue;
public:
	BossA();
	virtual ~BossA();

	virtual void Init()	override;

	virtual void Attack()	override;
	virtual void Move()		override;
	virtual void Die()		override;

	virtual void AttackType01();
	virtual void AttackType02();

	virtual void DieBehavior()	override;

	void CreateMonster();
};

