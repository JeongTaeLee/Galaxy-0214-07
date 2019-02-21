#include "DXUT.h"
#include "Bullet.h"

//Manager
#include "TimeManager.h"
#include "ImageManager.h"
#include "CameraManager.h"
#include "ObjectManager.h"

//Component
#include "Transform.h"
#include "ShaderRenderer.h"
#include "SphereCollider.h"

//GameObject
#include "EffectA.h"

Bullet::Bullet()
	:lpRenderer(nullptr), vDir(0.f, 0.f, 0.f),
	vOriginModelDir(0.f, 0.f, 1.f),
	fDamage(0.f), fSpeed(1000.f), fShine(1.f),
	fDestroyDelay(3.f), fDestroyAccrue(0.f), 
	fFlightLengthMax(10000.f), fFlightLengthAccrue(0.f)
{
	sTag = "Bullet";
}


Bullet::~Bullet()
{
}

void Bullet::Init()
{
	lpRenderer = AC(ShaderRenderer);
	lpRenderer->LoadMesh(IMAGE.LoadObjFile("BasicBullet", "./rs/obj/Bullet/Bullet.obj"));
	lpRenderer->SetEffect(IMAGE.LoadEffect("Bullet", "Bullet.fx"));

	transform->scale = Vector3(0.01f, 0.01f, 0.01f);

	transform->eUpdateType = E_UPDATE_02;
}

void Bullet::Update()
{
	if (fFlightLengthAccrue > fFlightLengthMax)
	{
		SetDestroy(true);
	}

	transform->pos += vDir * (fSpeed * Et);
	fFlightLengthAccrue += (fSpeed * Et);

	DestroyProcess();
}

void Bullet::DestroyProcess()
{
	fDestroyAccrue += Et;
}

void Bullet::SetBullet(const Vector3& FirePos, const Quaternion & _qRot, float _fSpeed, float _fDamage)
{	
	transform->pos = FirePos;
	transform->qRot = _qRot;
	
	D3DXMATRIX matRot;
	D3DXMatrixRotationQuaternion(&matRot, &_qRot);
	D3DXVec3TransformCoord(&vDir, &vOriginModelDir, &matRot);
	
	fSpeed = _fSpeed;
	fDamage = _fDamage;

	AC(SphereCollider)->InitSphere(Vector3(0.f, 0.f, 50.f), 3);
}





