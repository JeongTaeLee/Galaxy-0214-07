#pragma once
#include "GameObject.h"

class ShaderRenderer;

class Missile :
	public GameObject
{
protected:
	ShaderRenderer* lpRenderer;
	GameObject* lpTargetObject;

	Vector3 vOriginDir;

	float fSpeed;
	float fDamage;
public:
	Missile();
	virtual ~Missile();

	virtual void Init()	override;
	virtual void Update()	override;

	void SetMissile(GameObject* _target, const Vector3& vFirePos, const Vector3 & vOriginDir, float fSpeed, float fDamage);

public:
	float GetSpeed() { return fSpeed;}
	float GetDamage() { return fDamage; }
};

