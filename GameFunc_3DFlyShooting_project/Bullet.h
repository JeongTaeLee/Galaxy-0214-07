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
public:
	Bullet();
	virtual ~Bullet();

	virtual void Init()		override;
	virtual void Update()	override;

	void SetBullet(const Vector3 & FirePos, const Quaternion& _qRot, float _fSpeed, float _fDamage);
};

