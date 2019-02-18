#pragma once
#include "GameObject.h"

class ShaderRenderer;

class Bullet :
	public GameObject
{
protected:
	ShaderRenderer* lpRenderer;

	Vector3 vDir;
	Vector3 vOriginModelDir;
	
	float fDamage;
	float fSpeed;
	float fShine;

	float fDestroyDelay;
	float fDestroyAccrue;
public:
	Bullet();
	virtual ~Bullet();

	virtual void Init()		override;
	virtual void Update()	override;

public:
	void DestroyProcess();
public:
	void SetBullet(const Vector3 & FirePos, const Quaternion& _qRot, float _fSpeed, float _fDamage);

	float GetDamage() { return fDamage; }
};

