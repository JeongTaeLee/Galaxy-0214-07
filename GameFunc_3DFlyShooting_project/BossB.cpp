#include "DXUT.h"
#include "BossB.h"

//Manager
#include "ImageManager.h"
#include "TimeManager.h"
#include "CameraManager.h"
#include "ObjectManager.h"

//Component
#include "ShaderRenderer.h"
#include "Transform.h"
#include "SphereCollider.h"

#include "PlayerAirplane.h"
#include "MonsterCreater.h"
#include "GameVictroy.h"
#include "MonsterBullet.h"
#include "MonsterMissile.h"
#include "BossHpBar.h"
#include "VictroyEnding.h"


BossB::BossB()
	:vMonsterCreaterPos(0.f, 300.f, -500.f),
	fCreateDelay(15.f), fCreateAccrue(15.f),
	vOriginFirePos(6, 88, 54)
{
	fMinCameraLength = 1500.f;
	iLife = 130;

	fSpeed = 100.f;
	fMoveLength = 200.f;


	fAttackDelay = 0.7f;
	fMissileDelay = 20.f;
	fMissileAccrue = 0.f;

	iDieEffectAmount = 40;
}


BossB::~BossB()
{
}

void BossB::Init()
{
	MainMonster::Init();

	transform->pos = Vector3(0.f, 0.f, 0.f);
	transform->scale = Vector3(2.f, 2.f, 2.f);

	lpRenderer->LoadMesh(IMAGE.LoadObjFile("BossB", "./rs/obj/BossB/C.obj"));
	lpApperaTexture = IMAGE.LoadTexture("BossBAppear", "./rs/Sprite/UI/2Stage_FinalBoss.png");

	lpCollider->InitSphere(Vector3(0.f, 0.f, 0.f), 400);
	AC(SphereCollider)->InitSphere(Vector3(0.f, 0.f, 600.f), 200);
	AC(SphereCollider)->InitSphere(Vector3(0.f, 0.f, -600.f), 200);
}

void BossB::Attack()
{
	CreateMonster();

	if (fAttackAccrue > fAttackDelay)
	{
		fAttackAccrue = 0.f;

		if (fMissileAccrue > fMissileDelay)
		{
			fMissileAccrue = 0.f;
			AttackType02();
		}
		else
			AttackType01();
	}
	else
	{
		fMissileAccrue += Et;
		fAttackAccrue += Et;
	}
}

void BossB::Move()
{
	Vector3 vPlayerPos = Vector3(lpPlayer->transform->pos.x, 0.f, lpPlayer->transform->pos.z);

	if (fMoveLength < GetLengthVector3(vPlayerPos, transform->worldPos))
	{
		GetSLerpLookAt(vPlayerPos, transform->worldPos, transform->qRot, 0.01f);

		transform->pos += vAxis[E_AXIS_FORWARD] * (fSpeed * Et);
	}
}

void BossB::Die()
{
	lpCamera = CAMERA.GetCamera("AppearCamera");
	lpCamera->vPos = transform->pos + vAxis[E_AXIS_FORWARD] * fMinCameraLength;
	lpCamera->vPos.y += 200;
	lpCamera->vLookAt = transform->pos;
	CAMERA.ChangeCamera("AppearCamera");
}

void BossB::AttackType01()
{
	MonsterBullet* bullet = OBJECT.AddObject<MonsterBullet>();

	Quaternion qRot;
	D3DXQuaternionIsIdentity(&qRot);

	Matrix matRot;
	D3DXMatrixRotationQuaternion(&matRot, &transform->qRot);
	memcpy(&matRot._41, &transform->pos, sizeof(Vector3));

	Vector3 vFirePos;

	D3DXVec3TransformCoord(&vFirePos, &vOriginFirePos, &matRot);

	GetLookAt(qRot, lpPlayer->transform->worldPos, transform->pos);
	bullet->SetBullet(vFirePos, qRot, 1500.f, 1);
}

void BossB::AttackType02()
{
	Vector3 vFirePos;

	Matrix matRot;
	D3DXMatrixRotationQuaternion(&matRot, &transform->qRot);
	memcpy(&matRot._41, &transform->pos, sizeof(Vector3));

	D3DXVec3TransformCoord(&vFirePos, &vOriginFirePos, &matRot);

	MonsterMissile* missile = OBJECT.AddObject<MonsterMissile>();
	missile->SetMissile(lpPlayer, vFirePos, transform->qRot, 1, 700.f);
}

void BossB::DieBehavior()
{
	if (lpCollider->GetEnable())
		lpCollider->SetEnable(false);

	if (fDieEffectAccrue > fDieEffectDelay)
	{
		fDieEffectAccrue = 0.f;
		++iDieEffectCount;

		Vector3 RandomPos = GetRandomNumber(
			transform->worldPos - Vector3(500.f, 500.f, 1000.f),
			transform->worldPos + Vector3(500.f, 500.f, 1000.f));
		float RandomScale = GetRandomNumber(500.f, 1000.f);

		CreateEffectA(RandomPos, Vector3(RandomScale, RandomScale, RandomScale), 0.01f);

		if (iDieEffectCount == iDieEffectAmount)
		{
			SetActive(false);
			SetDestroy(true);

			OBJECT.AddObject<VictroyEnding>();
		}
	}
	else
		fDieEffectAccrue += Et;
}

void BossB::CreateMonster()
{
	if (lpCreater->GetMonsterList().size() > 2)
		return;

	fCreateAccrue += Et;

	if (fCreateAccrue > fCreateDelay)
	{
		fCreateAccrue = 0.f;

		Matrix matRot;
		D3DXMatrixRotationQuaternion(&matRot, &transform->qRot);
		memcpy(&matRot._41, &transform->pos, sizeof(Vector3));

		Vector3 CreatePos;
		D3DXVec3TransformCoord(&CreatePos, &vMonsterCreaterPos, &matRot);

		lpCreater->CreaterFlightA(CreatePos);
	}
}
