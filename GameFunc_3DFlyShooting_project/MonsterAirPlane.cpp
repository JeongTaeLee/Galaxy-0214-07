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
#include "MonsterCreater.h"
#include "PlayerAirplane.h"
MonsterAirPlane::MonsterAirPlane()
	: lpCreater(nullptr),
	lpEnemyCircle(nullptr),
	lpPlayer(nullptr),
	lpCollider(nullptr), 
	eState(E_MONSTERSTATE_IDLE),
	fHp(0.f),
	fAttackDelay(0.f), fAttackAccrue(0.f),
	fDieEffectDelay(0.05f), fDieEffectAccrue(0.05f),
	iDieEffectCount(0), iDieEffectAmount(3),
	fMoveLength(400.f), fAttackLength(400.f),
	bAttaking(true), bFlight(false),
	fPlayerLength(0.f)
{
	sTag = "Monster";
}


MonsterAirPlane::~MonsterAirPlane()
{
}

void MonsterAirPlane::Init()
{
	transform->eUpdateType = E_UPDATE_02;

	lpRenderer = AC(ShaderRenderer);
	lpCollider = AC(SphereCollider);
	lpRenderer->SetEffect(IMAGE.LoadEffect("Lighting", "Lighting.fx"));

	lpRenderer->SetRenderBegin(
		[&]() {
			lpRenderer->SetShaderVector("gWorldCamera", &Vector4(CAMERA.GetPos(), 1.f));
			lpRenderer->SetShaderTexture("gDiffuseMap", lpRenderer->GetMesh()->GetDiffuseMap(0));
			lpRenderer->SetShaderTexture("gSpecularMap", lpRenderer->GetMesh()->GetSpecularMap(0));
			lpRenderer->SetShaderFloat("gAmbient", 0.5f);
		});

	lpEnemyCircle = OBJECT.AddObject<EnemyCircle>();
	lpEnemyCircle->SetMonster(this);
}

void MonsterAirPlane::Update()
{
	if (lpPlayer)
	{
		if (lpPlayer->GetDestroy())
			lpPlayer = nullptr;		
	}
	
	if (!lpPlayer)
	{
		SetDestroy(true);
		lpPlayer = nullptr;
	}
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

	fPlayerLength = GetLengthVector3(lpPlayer->transform->worldPos, transform->worldPos);
}

void MonsterAirPlane::Release()
{
}

void MonsterAirPlane::IdleBehavior()
{
	if (!bFlight)
	{
		if (fPlayerLength > fMoveLength)
			Move();
	}

	if (fPlayerLength <= fAttackLength)
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

	SetAxis();
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
		{ 
			eState = E_MONSTERSTATE_DIE;
			lpCreater->DestroyListMonster(this);
			lpEnemyCircle->SetDestroy(true);
		}
	}
	if (lpOther->gameObject->sTag == "Monster")
	{
	}
	
}
