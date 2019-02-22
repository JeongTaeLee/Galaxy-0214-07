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
	fAngle(D3DXToRadian(20.f)),
	fSpeed(0.f), iDamage(1),
	fTargetingAccrue(0.f), fTargetingDelay(0.00f)
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
		CreateEffectA(transform->pos, Vector3(fRandomScale, fRandomScale, 1.f), 0.05f);
		SetDestroy(true);
		return;
	}
	
	Vector3 vTargetDirection = lpTargetObject->transform->worldPos - transform->worldPos;
	normalize(vTargetDirection);

	Vector3 vRotationAxis;
	D3DXVec3Cross(&vRotationAxis, &vDir, &vTargetDirection);

	float thath = acos(D3DXVec3Dot(&vTargetDirection, &vDir));
	
	if(vRotationAxis.z > 0.f)
		thath = acos(D3DXVec3Dot(&vTargetDirection, &vDir));
	else
		thath = -acos(D3DXVec3Dot(&vTargetDirection, &vDir));

	if (fAngle < thath)
		thath = fAngle;

	Matrix matRot;
	D3DXMatrixRotationAxis(&matRot, &vRotationAxis, thath);
	D3DXVec3TransformNormal(&vDir, &vDir, &matRot);
	normalize(vDir);

	GetLookAt(transform->qRot, transform->worldPos + vDir, transform->worldPos);
	
	transform->pos += vDir * (fSpeed * Et);

	DEBUG_VEC(vDir);
}


void Missile::SetMissile(GameObject* _target, const Vector3& vFirePos,const Vector3& _vOriginDir, float _fSpeed, int _fDamage, float _fAngle)
{
	lpTargetObject = _target;	
	vDir	= vOriginDir =_vOriginDir;
	fSpeed	= _fSpeed;
	iDamage = _fDamage;
	fAngle = D3DXToRadian(_fAngle);

	if (lpTargetObject->GetDestroy())
	{
		SetDestroy(true);
		return;
	}
	GetLookAt(transform->qRot, transform->worldPos+vDir, transform->worldPos);

	transform->pos = vFirePos;
	
}


