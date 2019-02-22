#pragma once
#include "GameObject.h"

class ShaderRenderer;

class Missile :
	public GameObject
{
protected:
	ShaderRenderer* lpRenderer;
	GameObject* lpTargetObject;

	Vector3 vDir;
	Vector3 vOriginDir;

	float fAngle;
	float fSpeed;
	float fDamage;

	float fTargetingAccrue;
	float fTargetingDelay;
public:
	Missile();
	virtual ~Missile();

	virtual void Init()	override;
	virtual void Update()	override;

	void SetMissile(GameObject* _target, const Vector3& vFirePos, const Vector3 & vOriginDir, float fSpeed = 1000.f, float fDamage = 1.f, float fAngle = 20.f);

public:
	float GetSpeed() { return fSpeed;}
	float GetDamage() { return fDamage; }
};

