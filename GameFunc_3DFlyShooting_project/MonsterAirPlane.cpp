#include "DXUT.h"
#include "MonsterAirPlane.h"
#include "Func.h"

//Manager
#include "ImageManager.h"
#include "ObjectManager.h"
#include "CameraManager.h"
#include "TimeManager.h"

//Component
#include "ShaderRenderer.h"
#include "SphereCollider.h"
#include "SphereCollider.h"

//Object
#include "PlayerBullet.h"
#include "EnemyCircle.h"
#include "MonsterDirector.h"

#include "Func.h"
MonsterAirPlane::MonsterAirPlane()
	:lpEnemyCircle(nullptr),
	lpPlayer(nullptr),
	lpCollider(nullptr), 
	eState(E_MONSTERSTATE_IDLE),
	fHp(0.f),
	fAttackDelay(0.f), fAttackAccrue(0.f),
	fDieEffectDelay(0.05f), fDieEffectAccrue(0.05f),
	iDieEffectCount(0), iDieEffectAmount(3),
	fMoveLength(400.f), fAttackLength(2000.f),
	bTargeting(true), bAttaking(true)
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
	switch (eState)
	{
	case E_MONSTERSTATE_IDLE:
		IdleBehavior();
		break;
	case E_MONSTERSTATE_DIE:
		DieBehavior();
		break;
	default:
		break;
	}
}

void MonsterAirPlane::Release()
{
	lpEnemyCircle->SetDestroy(true);
}

void MonsterAirPlane::IdleBehavior()
{
	Vector3 vLength = lpPlayer->transform->pos - transform->pos;
	float fLength = D3DXVec3Length(&vLength);

	if (fLength > fMoveLength)
		bTargeting = true;
	else
		bTargeting = false;

	if (fLength <= fAttackLength)
		bAttaking = true;
	else
		bAttaking = false;


	if (bTargeting)
		Move();

	if (bAttaking)
		Attack();

	LookAtPlayer();

	SendPMLength();
}

void MonsterAirPlane::DieBehavior()
{
	if (fDieEffectAccrue > fDieEffectDelay)
	{
		fDieEffectAccrue = 0.f;
		++iDieEffectCount;
		
		Vector3 RandomPos = GetRandomNumber(
			transform->worldPos - Vector3(50.f, 50.f, 0.f),
			transform->worldPos + Vector3(50.f, 50.f, 0.f));
		float RandomScale = GetRandomNumber(200.f, 300.f);

		RandomPos.z = transform->worldPos.z;

		CreateEffectA(RandomPos, Vector3(RandomScale, RandomScale, RandomScale), 0.01f);
	
		if (iDieEffectCount == iDieEffectAmount)
		{
			SetActive(false);
			SetDestroy(true);
		}
	}
	else
		fDieEffectAccrue += Et;

}

void MonsterAirPlane::Move()
{

	bTargeting = true;

	Vector3 vDir = Vector3(0.f, 0.f, 1.f);

	Matrix matRot;
	D3DXMatrixRotationQuaternion(&matRot, &transform->qRot);
	D3DXVec3TransformCoord(&vDir, &vDir, &matRot);

	transform->pos += vDir * (fSpeed * Et);

	
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
			eState = E_MONSTERSTATE_DIE;
	}
}
