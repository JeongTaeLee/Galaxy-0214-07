#pragma once
#include "AirPlane.h"

enum MosnterState
{
	E_MONSTERSTATE_IDLE,
	E_MONSTERSTATE_DIE,
};


class ShaderRenderer;
class SphereCollider;
class PlayerAirPlane;
class Collider;
class EnemyCircle;

class MonsterAirPlane :
	public AirPlane
{
protected:
	EnemyCircle* lpEnemyCircle;

	GameObject * lpPlayer;
	SphereCollider* lpCollider;
	
	MosnterState eState;

	float fHp;

	float fAttackDelay;
	float fAttackAccrue;
	
	float fDieEffectDelay;
	float fDieEffectAccrue;

	int iDieEffectCount;
	int iDieEffectAmount;

	float fMoveLength;
	float fAttackLength;

	bool bTargeting;
	bool bAttaking;
public:
	MonsterAirPlane();
	virtual ~MonsterAirPlane();

	virtual void Init()	override;
	virtual void Update()	override;
	virtual void Release()	override;

public:
	virtual void IdleBehavior();
	virtual void DieBehavior(); 

public:
	virtual void Attack() PURE;
	virtual void Move();
	void LookAtPlayer();
	void SendPMLength();
public:
	virtual void ReceiveCollider(Collider* lpCollider) override;
};

