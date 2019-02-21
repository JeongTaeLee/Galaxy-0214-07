#pragma once
#include "AirPlane.h"

enum MonsterState
{
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
	MonsterCreater* lpCreater;
	PlayerAirplane * lpPlayer;

	EnemyCircle* lpEnemyCircle;

	SphereCollider* lpCollider;
	
	MonsterState eState;

	Vector3 vOriginDir;

	float fHp;

	float fAttackDelay;
	float fAttackAccrue;
	
	float fDieEffectDelay;
	float fDieEffectAccrue;

	int iDieEffectCount;
	int iDieEffectAmount;

	float fMoveLength;
	float fAttackLength;

	bool bAttaking;
	bool bFlight;

	float fPlayerLength;
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

	void SendPMLength();

public:
	MonsterState GetState() { return eState; }
	EnemyCircle* GetCircle() { return lpEnemyCircle; }

	float GetPlayerLength() { return fPlayerLength; }
	void SetPlayer(PlayerAirplane * airPlane) { lpPlayer = airPlane;}

	void SetMonster(MonsterCreater* Creater, PlayerAirplane * player, bool _bFlight, const Vector3& vDir);
public:
	virtual void ReceiveCollider(Collider* lpCollider) override;
};

