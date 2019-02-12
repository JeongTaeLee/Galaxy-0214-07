#include "DXUT.h"
#include "Bullet.h"

//Manager
#include "TimeManager.h"
#include "ImageManager.h"
#include "CameraManager.h"

//Component
#include "Transform.h"
#include "ShaderRenderer.h"

Bullet::Bullet()
	:lpRenderer(nullptr), vDir(0.f, 0.f, 0.f), 
	vOriginModelDir(0.f, 0.f, 1.f),
	fDamage(0.f), fSpeed(1000.f), fShine(1.f)
{
}


Bullet::~Bullet()
{
}

void Bullet::Init()
{
	transform->bTransformUpdate= false;

	lpRenderer = AC(ShaderRenderer);
	lpRenderer->LoadMesh(IMAGE.LoadObjFile("Bullet", "./rs/obj/Bullet/Bullet.obj"));
	lpRenderer->SetEffect(IMAGE.LoadEffect("Bullet", "Bullet.fx"));

	transform->scale = Vector3(0.01f, 0.01f, 0.02f);
}

void Bullet::Update()
{
	transform->pos += vDir * (fSpeed * Et);

	D3DXMatrixTranslation(&transform->matPos, transform->pos.x, transform->pos.y, transform->pos.z);
	D3DXMatrixScaling(&transform->matScale, transform->scale.x, transform->scale.y, transform->scale.z);
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
}





