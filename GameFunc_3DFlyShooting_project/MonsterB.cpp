#include "DXUT.h"
#include "MonsterB.h"

//Manager
#include "ImageManager.h"
#include "ObjectManager.h"

//Component
#include "ShaderRenderer.h"
#include "SphereCollider.h"

//Object
#include "MonsterMissile.h"
MonsterB::MonsterB()
{

	fAttackDelay = fAttackAccrue = 3.f;
}


MonsterB::~MonsterB()
{
}

void MonsterB::Init()
{
	MonsterAirPlane::Init();

	lpRenderer->LoadMesh(IMAGE.LoadObjFile("MonsterB", "./rs/obj/MonsterB/MonsterB.obj"));

	lpCollider->InitSphere(Vector3(0.f, 10.f, 40.f), 50);
}

void MonsterB::Attack()
{
	if (fAttackAccrue >= fAttackDelay)
	{

		//OBJECT.AddObject<MonsterMissile>()
		//	->SetMissile((GameObject*)lpPlayer, transform->worldPos, Vector3(0.f, 0.f, 1.f), 1500.f, 20.f, 10.f);
	}
}
