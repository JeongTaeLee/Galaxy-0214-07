#include "DXUT.h"
#include "MonsterAirPlane.h"
#include "Func.h"

//Manager
#include "ImageManager.h"
#include "ObjectManager.h"
#include "CameraManager.h"
#include "TimeManager.h"
#include "GameManager.h"

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
#include "PlayerMissile.h"
MonsterAirPlane::MonsterAirPlane()
	:
	eState(MonsterState::E_MONSTERSTATE_IDLE),
	lpCreater(nullptr),
	lpPlayer(nullptr),
	lpEnemyCircle(nullptr),
	lpCollider(nullptr),
	iLife(2),
	fAttackDelay(0.f), fAttackAccrue(0.f),
	iDieEffectAmount(3), iDieEffectCount(0),
	fDieEffectDelay(0.f), fDieEffectAccrue(3.f),
	fMoveLength(0.f), fAttackLength(0.f),
	fPlayerDistance(0.f),
	bFlight(false)
{
	sTag = "Monster";
	
}


MonsterAirPlane::~MonsterAirPlane()
{
}

void MonsterAirPlane::Init()
{
	lpRenderer = AC(ShaderRenderer);
	lpCollider = AC(SphereCollider);
	lpRenderer->SetEffect(IMAGE.LoadEffect("Lighting", "Lighting.fx"));

	lpRenderer->SetRenderBegin(
		[&]() {
			lpRenderer->SetShaderVector("gWorldCamera", &Vector4(CAMERA.GetPos(), 1.f));
			lpRenderer->SetShaderTexture("gDiffuseMap", lpRenderer->GetMesh()->GetDiffuseMap(0));

			if(lpRenderer->GetMesh()->GetSpecularMap(0))
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
	}

	fPlayerDistance = GetLengthVector3(lpPlayer->transform->worldPos, transform->worldPos);
}

void MonsterAirPlane::Release()
{
	lpEnemyCircle->SetDestroy(true);
}

void MonsterAirPlane::IdleBehavior()
{
	if (fPlayerDistance >= fMoveLength)
		Move();

	if (fPlayerDistance <= fAttackLength)
		Attack();
}

void MonsterAirPlane::DieBehavior()
{
	if (lpCollider->GetEnable())
		lpCollider->SetEnable(false);

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

void MonsterAirPlane::SetMonsterValue(MonsterCreater* _lpCreater, PlayerAirplane* _lpPlayer, const Vector3& _vOriginDir, bool _bFlight)
{
	lpCreater = _lpCreater;
	lpPlayer = _lpPlayer;
	vOriginDir = _vOriginDir;
	bFlight = _bFlight;

	lpCreater->AddListMonster(this);
	transform->UpdateTransform();
	GetLookAt(transform->qRot, transform->worldPos + vOriginDir, transform->worldPos);
}

void MonsterAirPlane::SetMonsterDie()
{
	eState = E_MONSTERSTATE_DIE;
	lpCreater->DestroyListMonster(this);
}

void MonsterAirPlane::ReceiveCollider(Collider* lpOther)
{
	if (lpOther->gameObject->sTag == "PlayerBullet")
	{
		PlayerBullet* object = static_cast<PlayerBullet*>(lpOther->gameObject);
		iLife -= object->GetDamage();
	}
	if (lpOther->gameObject->sTag == "PlayerMissile")
	{
		PlayerMissile* object = static_cast<PlayerMissile*>(lpOther->gameObject);
		iLife -= object->GetDamage();
	}
	if (lpOther->gameObject->sTag == "PlayerAirPlane")
		iLife = 0;
	
	if (iLife <= 0)
	{
		GAMEMANAGER.iKillMonsterCount += 1;
		SetMonsterDie();
	}
}
