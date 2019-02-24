#include "DXUT.h"
#include "MonsterB2.h"

//Manager
#include "ImageManager.h"
#include "ObjectManager.h"
#include "TimeManager.h"

//Component
#include "ShaderRenderer.h"
#include "SphereCollider.h"

//Object
#include "MonsterMissile.h"
#include "PlayerAirplane.h"

MonsterB2::MonsterB2()
{
	iLife = 10;
	fAttackDelay = 15.f;
	fAttackAccrue = 10.f;
}


MonsterB2::~MonsterB2()
{
}

void MonsterB2::Init()
{
	MonsterAirPlane::Init();

	lpRenderer->LoadMesh(IMAGE.LoadObjFile("MonsterB2", "./rs/obj/MonsterB2/MonsterB2.obj"));

	lpCollider->InitSphere(Vector3(0.f, 10.f, 40.f), 50);
}

void MonsterB2::Attack()
{
	if (fAttackAccrue >= fAttackDelay)
	{
		fAttackAccrue = 0.f;

		MonsterMissile* missile = OBJECT.AddObject<MonsterMissile>();
		missile->SetMissile(lpPlayer, transform->worldPos, transform->qRot, 1, 800.f);
	}
	else
		fAttackAccrue += Et;
}
