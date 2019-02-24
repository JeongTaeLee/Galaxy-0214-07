#pragma once
#include "GameObject.h"

class ShaderRenderer;

class Missile :
	public GameObject
{
protected:
	ShaderRenderer* lpRenderer;
	GameObject* lpTarget;
	Vector3 vDir;
	Vector3 vOriginDir;

	float fSpeed;
	int iDamage;
public:
	Missile();
	virtual ~Missile();

	virtual void Init()	override;
	virtual void Update()	override;

	void SetMissile(GameObject* lpTarget, const Vector3& vFirePos, Quaternion &qRot, int _iDamage = 1, float _fSpeed = 800.f);
public:
	float GetSpeed() { return fSpeed;}
	int GetDamage() { return iDamage; }
};

