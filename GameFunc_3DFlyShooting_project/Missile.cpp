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
	:lpRenderer(nullptr), lpTarget(nullptr),
	fSpeed(0.f), iDamage(1)
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
			lpRenderer->SetShaderFloat("gAmbient", 0.6f);
		});

	AC(SphereCollider)->InitSphere(Vector3(0.f, 0.f, 50.f), 3);

	transform->scale = Vector3(1.f, 1.f, 1.f);

}

void Missile::Update()
{
	if (lpTarget->GetDestroy())
	{
		CreateEffectA(transform->worldPos, Vector3(50.f, 50.f, 50.f));
		SetDestroy(true);
		SetActive(false);
		return;
	}

	transform->pos += vDir * (fSpeed * Et);

	Matrix matRot;

	GetSLerpLookAt(lpTarget->transform->worldPos, transform->pos, transform->qRot, 0.1f);	
	D3DXMatrixRotationQuaternion(&matRot, &transform->qRot);

	vDir = Vector3(0.f, 0.f, 1.f);
	D3DXVec3TransformNormal(&vDir, &vDir, &matRot);
}

void Missile::SetMissile(GameObject* _lpTarget, const Vector3& _vFirePos, Quaternion &qRot, int _iDamage, float _fSpeed)
{
	lpTarget = _lpTarget;
	transform->pos = _vFirePos;
	transform->qRot = qRot;
	iDamage = _iDamage;
	fSpeed = _fSpeed;

	D3DXMATRIX matRot;
	D3DXMatrixRotationQuaternion(&matRot, &transform->qRot);
	D3DXVec3TransformCoord(&vDir, &Vector3(0.f, 0.f, 1.f), &matRot);

}
