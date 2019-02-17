#include "DXUT.h"
#include "MonsterA.h"

//Manager
#include "ImageManager.h"
#include "CameraManager.h"

//Component
#include "Transform.h"
#include "ShaderRenderer.h"
#include "SphereCollider.h"
MonsterA::MonsterA()
{
}


MonsterA::~MonsterA()
{
}

void MonsterA::Init()
{
	transform->scale = Vector3(3.0f, 3.0f, 3.0f);

	MonsterAirPlane::Init();

	lpRenderer->LoadMesh(IMAGE.LoadObjFile("MonsterA", "./rs/obj/MonsterA/MonsterA.obj"));

	lpCollider->InitSphere(Vector3(0.f, 10.f, 40.f), 50);

	fHp = 10.f;
}
