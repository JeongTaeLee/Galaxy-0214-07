#pragma once
#include "Collider.h"

class DebugSpherer;

class SphereCollider :
	public Collider
{
private:
	float fRadius;

public:
	SphereCollider();
	virtual ~SphereCollider();

	void InitSphere(Vector3 vSphereCollider, float _fRadius);
public:
	virtual bool CheckCollision(Collider* lpOther) override;
public:
	float GetRadius() { return fRadius; }
};

