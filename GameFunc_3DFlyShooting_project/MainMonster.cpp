#include "DXUT.h"
#include "MainMonster.h"

#include "CameraManager.h"
#include "MainMonster.h"
#include "TimeManager.h"
#include "ObjectManager.h"
#include "GameManager.h"
#include "Transform.h"
#include "AppearUI.h"
#include "PlayerAirplane.h"
#include "SphereCollider.h"
#include "PlayerBullet.h"
#include "PlayerMissile.h"
#include "Meteor.h"
#include "MonsterCreater.h"
#include "BossHpBar.h"

MainMonster::MainMonster()
	:lpCamera(nullptr),
	lpApperaTexture(nullptr),
	lpAppearUI(nullptr),

	vTargetPos(0.f, 0.f, 0.f),
	vTargetLookAt(0.f, 0.f, 0.f),
	bCompleteLookAt(false),
	bCompleteAppear(false),
	bCameraInit(false),

	fMinCameraLength(0.f),

	fWaitingAccrue(0.f),
	fWaitingDelay(1.f),

	sOldCameraName("None")

{
}


MainMonster::~MainMonster()
{
}

void MainMonster::Init()
{
	MonsterAirPlane::Init();
	eState = MonsterState::E_MONSTERSTATE_APPEAR;
	lpCamera = CAMERA.GetCamera("AppearCamera");

	lpHpBar = OBJECT.AddObject<BossHpBar>();
	lpHpBar->SetHpBar(Vector3(WINSIZEX / 2 - 430.f, 99.f, 0.f), iLife);
}

void MainMonster::Update()
{
	if (lpPlayer)
	{
		if (lpPlayer->GetDestroy())
		{
			lpPlayer = nullptr;
			return;
		}
	}

	if (!lpPlayer)
	{
		SetDestroy(true);
		return;
	}

	if (eState == E_MONSTERSTATE_APPEAR)
		Appear();
	else
		MonsterAirPlane::Update();
}

void MainMonster::Appear()
{
	if (!bCameraInit)
	{
		bCameraInit = true;

		lpCamera->vPos = CAMERA.GetCamera()->vPos;
		lpCamera->vLookAt = CAMERA.GetCamera()->vLookAt;
		lpCamera->vUp = CAMERA.GetCamera()->vUp;
	
		sOldCameraName = CAMERA.GetNowCameraName();
		CAMERA.ChangeCamera("AppearCamera");

		vTargetPos = transform->pos + vAxis[E_AXIS_FORWARD] * fMinCameraLength;
		vTargetPos.y += 200;

		vTargetLookAt = transform->pos;
	}

	if (!bCompleteAppear)
	{
		D3DXVec3Lerp(&lpCamera->vLookAt, &lpCamera->vLookAt, &vTargetLookAt, 0.02f);
		D3DXVec3Lerp(&lpCamera->vUp, &lpCamera->vUp, &Vector3(0.f, 1.f, 0.f), 0.1f);

		if(3500.f > GetLengthVector3(lpCamera->vLookAt, vTargetLookAt))
		{
			D3DXVec3Lerp(&lpCamera->vPos, &lpCamera->vPos, &vTargetPos, 0.025f);

			float fLength = GetLengthVector3(lpCamera->vPos, vTargetPos);

			if (fLength < 2.f)
			{
				lpAppearUI = OBJECT.AddObject<AppearUI>();
				lpAppearUI->SetAppearUI(lpApperaTexture);

				lpCamera->vPos = vTargetPos;
				lpCamera->vLookAt = vTargetLookAt;
				bCompleteAppear = true;
			}
		}
	}
	else
	{
		fWaitingAccrue += Et;

		if (fWaitingAccrue > fWaitingDelay)
		{
			eState = E_MONSTERSTATE_IDLE;
			CAMERA.ChangeCamera(sOldCameraName);
			lpAppearUI->SetDestroy(true);

			lpPlayer->transform->pos = Vector3(0.f, 500.f, -3000.f);
		}
	}
}

void MainMonster::ReceiveCollider(Collider* lpOther)
{
	if (lpOther->gameObject->sTag == "PlayerBullet")
	{
		PlayerBullet* object = static_cast<PlayerBullet*>(lpOther->gameObject);
		iLife -= object->GetDamage();
		lpHpBar->SetHp(iLife);
	}
	if (lpOther->gameObject->sTag == "PlayerMissile")
	{
		PlayerMissile* object = static_cast<PlayerMissile*>(lpOther->gameObject);
		iLife -= object->GetDamage();
		lpHpBar->SetHp(iLife);
	}

	if (iLife <= 0)
	{
		Die();

		if (lpHpBar)
			lpHpBar->SetDestroy(true);

		lpCreater->EndBossWar();
		SetMonsterDie();
	}
}
