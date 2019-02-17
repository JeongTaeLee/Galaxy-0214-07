#include "DXUT.h"
#include "MonsterAirPlane.h"
#include "Func.h"

//Manager
#include "ImageManager.h"
#include "ObjectManager.h"
#include "CameraManager.h"

//Component
#include "ShaderRenderer.h"
#include "SphereCollider.h"
#include "SphereCollider.h"

//Object
#include "PlayerBullet.h"
#include "EnemyCircle.h"
#include "MonsterDirector.h"
MonsterAirPlane::MonsterAirPlane()
	:lpPlayer(nullptr), lpCollider(nullptr), 
	fHp(0.f), fAttackDelay(0.f), fAttackAccrue(0.f)
{
	sTag = "Monster";
}


MonsterAirPlane::~MonsterAirPlane()
{
}

void MonsterAirPlane::Init()
{
	transform->eUpdateType = E_UPDATE_02;

	lpPlayer = OBJECT.FindWithTag("PlayerAirPlane");

	lpRenderer = AC(ShaderRenderer);
	lpCollider = AC(SphereCollider);
	lpRenderer->SetEffect(IMAGE.LoadEffect("Lighting", "Lighting.fx"));

	lpRenderer->SetRenderBegin(
		[&]() {
			lpRenderer->SetShaderVector("gWorldCamera", &Vector4(CAMERA.GetPos(), 1.f));
			lpRenderer->SetShaderTexture("gDiffuseMap", lpRenderer->GetMesh()->GetDiffuseMap(0));
			lpRenderer->SetShaderTexture("gSpecularMap", lpRenderer->GetMesh()->GetSpecularMap(0));
			lpRenderer->SetShaderFloat("gAmbient", 0.3f);
		});

	lpEnemyCircle = OBJECT.AddObject<EnemyCircle>();
	lpEnemyCircle->SetMonster(this);
}

void MonsterAirPlane::Update()
{
	SendPMLength();
	LookAtPlayer();

	Attack();
}

void MonsterAirPlane::Release()
{
	lpEnemyCircle->SetDestroy(true);
}

void MonsterAirPlane::LookAtPlayer()
{
	Vector3 vDir = lpPlayer->transform->worldPos - transform->worldPos;
	normalize(vDir);

	Matrix matRot;
	D3DXMatrixLookAtLH(&matRot, &D3DXVECTOR3(0, 0, 0), &vDir,
		&D3DXVECTOR3(0, 1, 0));
	D3DXMatrixTranspose(&matRot, &matRot); //

	D3DXQUATERNION currQ;
	D3DXQuaternionRotationMatrix(&currQ, &matRot);
	D3DXQuaternionSlerp(&transform->qRot, &transform->qRot, &currQ, 0.25f);
}

void MonsterAirPlane::SendPMLength()
{
	Vector3 vLength = transform->worldPos - lpPlayer->transform->worldPos;
	float fLength = D3DXVec3Length(&vLength);

	lpMonsterDirector->ReceviePMLength(transform->pos, fLength);
}

void MonsterAirPlane::ReceiveCollider(Collider* lpOther)
{
	if (lpOther->gameObject->sTag == "PlayerBullet")
	{
		PlayerBullet* object = static_cast<PlayerBullet*>(lpOther->gameObject);

		fHp -= object->GetDamage();

 		if (fHp <= 0)
			SetDestroy(true);
	}
}
