#pragma once
#include "AirPlane.h"

class ShaderRenderer;
class SphereCollider;

class MonsterAirPlane :
	public AirPlane
{
private:
	ShaderRenderer* lpRenderer;
	SphereCollider* lpCollider;

	float fHp;
public:
	MonsterAirPlane();
	virtual ~MonsterAirPlane();

	virtual void Init()	override;
};

