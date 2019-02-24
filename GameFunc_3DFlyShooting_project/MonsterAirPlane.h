#pragma once
#include "AirPlane.h"

enum MonsterState
{
	E_MONSTERSTATE_APPEAR,
	E_MONSTERSTATE_IDLE,
	E_MONSTERSTATE_DIE,
};


class ShaderRenderer;
class SphereCollider;
class PlayerAirplane;
class Collider;
class EnemyCircle;
class MonsterCreater;

class MonsterAirPlane :
	public AirPlane
{
protected:
	MonsterState eState;
	
	MonsterCreater* lpCreater;
	PlayerAirplane * lpPlayer;
	EnemyCircle* lpEnemyCircle;

	SphereCollider* lpCollider;

	Vector3 vOriginDir;

	int iLife;

	float fAttackDelay;
	float fAttackAccrue;
	
	float fDieEffectDelay;
	float fDieEffectAccrue;

	int iDieEffectCount;
	int iDieEffectAmount;

	float fMoveLength;
	float fAttackLength;

	float fPlayerDistance;

	bool bFlight;
public:
	MonsterAirPlane();
	virtual ~MonsterAirPlane();

	virtual void Init()	override;
	virtual void Update()	override;
	virtual void Release()	override;
public:
	virtual void IdleBehavior();
	virtual void DieBehavior(); 
	virtual void Attack() {};
	virtual void Move() {};

public:
	EnemyCircle* GetCircle() { return lpEnemyCircle; }
	MonsterState GetState() { return eState; }

	float GetPlayerDistance() { return fPlayerDistance; }
	
	void SetMonsterValue(MonsterCreater* _lpCreater, PlayerAirplane* _lpPlayer, const Vector3& _vOriginDir, bool _bFlight);
	void SetMonsterDie();
public:
	virtual void ReceiveCollider(Collider* lpCollider) override;
};

