#include "DXUT.h"
#include "MiddleBossA.h"

#include "ImageManager.h"
#include "TimeManager.h"
#include "ObjectManager.h"
#include "GameManager.h"

#include "ShaderRenderer.h"
#include "SphereCollider.h"
#include "Transform.h"

#include "PlayerAirplane.h"
#include "MonsterBullet.h"
#include "MonsterMissile.h"
#include "StageMission.h"

MiddleBossA::MiddleBossA()
	:vFirePos01(-87.f, 17.f, 14.f),
	vFirePos02(87.f, 17.f, 14.f)
{
	fMinCameraLength = 300;
	iLife = 50;

	fSpeed = 100.f;
	fMoveLength = 200.f;	

	fAttackDelay = 1.f;

	fMissileDelay = 20.f;
	fMissileAccrue = 0.f;

	iDieEffectAmount = 10;
}


MiddleBossA::~MiddleBossA()
{
}

void MiddleBossA::Init()
{
	MainMonster::Init();

	lpRenderer->LoadMesh(IMAGE.LoadObjFile("MiddleBossA", "./rs/obj/MiddleBossA/A_.obj"));
	lpApperaTexture = IMAGE.LoadTexture("MiddleBossAAppear", "./rs/Sprite/UI/1Stage_MidBoss.png");

	lpCollider->InitSphere(Vector3(0.f, 0.f, 0.f), 100);
}

void MiddleBossA::Move()
{
	Vector3 vPlayerPos = Vector3(lpPlayer->transform->pos.x, 0.f, lpPlayer->transform->pos.z);	

	if (fMoveLength < GetLengthVector3(vPlayerPos, transform->worldPos))
	{
		GetSLerpLookAt(vPlayerPos, transform->worldPos, transform->qRot, 0.01f);

		transform->pos += vAxis[E_AXIS_FORWARD] * (fSpeed * Et);
	}
}

void MiddleBossA::Attack()
{
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

void MiddleBossA::Die()
{
	GAMEMANAGER.SetMission(10);
}

void MiddleBossA::AttackType01()
{
	MonsterBullet* bullet = OBJECT.AddObject<MonsterBullet>();

	Quaternion qRot;
	D3DXQuaternionIsIdentity(&qRot);

	Matrix matRot;
	D3DXMatrixRotationQuaternion(&matRot, &transform->qRot);
	memcpy(&matRot._41, &transform->pos, sizeof(Vector3));

	Vector3 vFirePos = Vector3(0.f, 0.f, 0.f);

	
	int PosType = GetRandomNumber(0, 1);
	switch (PosType)
	{
	case 0:
		vFirePos = vFirePos01;
		break;
	case 1:
		vFirePos = vFirePos02;
		break;
	}

	D3DXVec3TransformCoord(&vFirePos, &vFirePos, &matRot);

	GetLookAt(qRot, lpPlayer->transform->worldPos, transform->pos);
	bullet->SetBullet(vFirePos, qRot, 1500.f, 1);
}

void MiddleBossA::AttackType02()
{
	int i = GetRandomNumber(0, 1);
	
	Vector3 vFirePos;

	switch (i)
	{
	case 0:
		vFirePos = vFirePos01;
		break;

	case 1:
		vFirePos = vFirePos02;
		break;
	}

	Matrix matRot;
	D3DXMatrixRotationQuaternion(&matRot, &transform->qRot);
	memcpy(&matRot._41, &transform->pos, sizeof(Vector3));

	D3DXVec3TransformCoord(&vFirePos, &vFirePos, &matRot);

	MonsterMissile* missile = OBJECT.AddObject<MonsterMissile>();
	missile->SetMissile(lpPlayer, vFirePos, transform->qRot, 1, 700.f);

}

