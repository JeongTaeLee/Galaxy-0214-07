#pragma once
#include "AirPlane.h"

class ShaderRenderer;
class SphereCollider;
class PlayerAirPlane;
class Collider;

class MonsterAirPlane :
	public AirPlane
{
protected:
	GameObject * lpPlayer;
	SphereCollider* lpCollider;

	float fHp;
public:
	MonsterAirPlane();
	virtual ~MonsterAirPlane();

	virtual void Init()	override;

	void LookAtPlayer();

public:
	virtual void ReceiveCollider(Collider* lpCollider) override;
};

