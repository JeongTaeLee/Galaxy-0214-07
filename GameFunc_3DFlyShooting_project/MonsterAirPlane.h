#pragma once
#include "AirPlane.h"

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

	float fHp;

	float fAttackDelay;
	float fAttackAccrue;

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


	void LookAtPlayer();
	void SendPMLength();

public:
	virtual void Attack() PURE;
	virtual void Move();
public:
	virtual void ReceiveCollider(Collider* lpCollider) override;
};

