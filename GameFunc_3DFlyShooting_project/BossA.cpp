#include "DXUT.h"
#include "BossA.h"

//Manager
#include "ImageManager.h"

//Component
#include "ShaderRenderer.h"
#include "Transform.h"
BossA::BossA()
{
}


BossA::~BossA()
{
}

void BossA::Init()
{
	transform->pos = Vector3(0.f, 0.f, 0.f);
	transform->scale = Vector3(8.f, 8.f, 8.f);

	MonsterAirPlane::Init();
	lpRenderer->LoadMesh(IMAGE.LoadObjFile("BossA", "./rs/obj/BossA/B.obj"));
}

void BossA::Update()
{
}

void BossA::Attack()
{
}
