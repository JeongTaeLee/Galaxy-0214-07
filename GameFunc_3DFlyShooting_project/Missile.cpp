#include "DXUT.h"
#include "Missile.h"

//Manager
#include "ImageManager.h"
#include "TimeManager.h"
#include "CameraManager.h"

//Compoent
#include "ShaderRenderer.h"
#include "SphereCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "Collider.h"
Missile::Missile()
	:lpRenderer(nullptr), lpTargetObject(nullptr),
	vOriginDir(0.f, 0.f, 0.f),
	fSpeed(0.f), fDamage(0.f)
{
}


Missile::~Missile()
{
}

void Missile::Init()
{
	transform->eUpdateType = TransformUpdateType::E_UPDATE_02;

	lpRenderer = AC(ShaderRenderer);
	lpRenderer->LoadMesh(IMAGE.LoadObjFile("Missile", "./rs/obj/Missile/C.obj"));
	lpRenderer->SetEffect(IMAGE.LoadEffect("Lighting", "Lighting.fx"));

	lpRenderer->SetRenderBegin(
		[&]() {
			lpRenderer->SetShaderVector("gWorldCamera", &Vector4(CAMERA.GetPos(), 1.f));
			lpRenderer->SetShaderTexture("gDiffuseMap", lpRenderer->GetMesh()->GetDiffuseMap(0));
			lpRenderer->SetShaderTexture("gSpecularMap", lpRenderer->GetMesh()->GetSpecularMap(0));
			lpRenderer->SetShaderFloat("gAmbient", 0.3f);
		});

	AC(SphereCollider)->InitSphere(Vector3(0.f, 0.f, 50.f), 3);

	transform->scale = Vector3(0.5f, 0.5f, 1.f);

}

void Missile::Update()
{
	if (lpTargetObject->GetDestroy())
	{
		float fRandomScale = GetRandomNumber(150.f, 300.f);
		CreateEffectA(transform->pos, Vector3(fRandomScale, fRandomScale, 1.f), 0.01f);
		SetDestroy(true);
		return;
	}

	GetSLerpLookAt(lpTargetObject->transform->worldPos, transform->pos, transform->qRot, 0.5f);

	D3DXMATRIX matRot;
	D3DXMatrixRotationQuaternion(&matRot, &transform->qRot);

	Vector3 vDir = Vector3(0.f, 0.f, 1.f);//vOriginDir;
	D3DXVec3TransformNormal(&vDir, &vDir, &matRot);

	transform->pos += vDir * (fSpeed * Et);
	fSpeed += 50;
}


void Missile::SetMissile(GameObject* _target, const Vector3& vFirePos,const Vector3& _vOriginDir, float _fSpeed, float _fDamage)
{
	lpTargetObject = _target;	
	vOriginDir = _vOriginDir;

	if (lpTargetObject->GetDestroy())
	{
		SetDestroy(true);
		return;
	}
	GetLookAt(transform->qRot, lpTargetObject->transform->worldPos, lpTargetObject->transform->worldPos); 

	transform->pos = vFirePos;
	
	fSpeed = _fSpeed;
	fDamage = _fDamage;
}


