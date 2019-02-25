#include "DXUT.h"
#include "MonsterA2.h"

//Manager
#include "ImageManager.h"
#include "CameraManager.h"
#include "TimeManager.h"
#include "ObjectManager.h"

//Component
#include "Transform.h"
#include "ShaderRenderer.h"
#include "SphereCollider.h"
#include "MonsterBullet.h"
#include "PlayerAirplane.h"

MonsterA2::MonsterA2()
	:bSecondAttack(false)
{
	fAttackDelay = 0.7f;
	fSpeed = 500.f;
	iLife = 4;

	fAttackLength = 1500.f;
}


MonsterA2::~MonsterA2()
{
}

void MonsterA2::Init()
{
	transform->scale = Vector3(3.0f, 3.0f, 3.0f);

	MonsterAirPlane::Init();

	lpRenderer->LoadMesh(IMAGE.LoadObjFile("MonsterA2", "./rs/obj/MonsterA2/MonsterA2.obj"));

	lpCollider->InitSphere(Vector3(0.f, 10.f, 40.f), 50);
}

void MonsterA2::Attack()
{
	if (fAttackLength < GetLengthVector3(lpPlayer->transform->worldPos, transform->worldPos))
		return;

	if (fAttackAccrue >= fAttackDelay)
	{
		fAttackAccrue = 0.f;

		Vector3 vFirePos = Vector3(0.f, 0.f, 0.f);

		if (bSecondAttack)
		{
			vFirePos = Vector3(20.f, 0.f, 0.f);
			fAttackDelay = 1.5f;
		}
		else
		{
			vFirePos = Vector3(-20.f, 0.f, 0.f);
			fAttackDelay = 0.5f;
		}

		bSecondAttack = !bSecondAttack;

		Quaternion qRot;

		if (bFlight)
			qRot = lpParent->transform->qRot;
		else
			qRot = transform->qRot;

		D3DXMATRIX matRot;
		D3DXMatrixRotationQuaternion(&matRot, &qRot);
		memcpy(&matRot._41, &transform->worldPos, sizeof(Vector3));

		D3DXVec3TransformCoord(&vFirePos, &vFirePos, &matRot);

		GetLookAt(qRot, lpPlayer->transform->worldPos, vFirePos);
		OBJECT.AddObject<MonsterBullet>()->SetBullet(vFirePos, qRot, 1500.f, 3);
	}
	else
		fAttackAccrue += Et;
}
