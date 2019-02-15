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
	transform->scale = Vector3(4.f, 4.f, 4.f);

	MonsterAirPlane::Init();

	lpRenderer->LoadMesh(IMAGE.LoadObjFile("MonsterA", "./rs/obj/MonsterA/MonsterA.obj"));

	lpRenderer->SetRenderBegin(
		[&]() {
			lpRenderer->SetShaderVector("gWorldCamera", &Vector4(CAMERA.GetPos(), 1.f));
			lpRenderer->SetShaderTexture("gDiffuseMap", lpRenderer->GetMesh()->GetDiffuseMap(0));
			lpRenderer->SetShaderTexture("gSpecularMap", lpRenderer->GetMesh()->GetSpecularMap(0));
			lpRenderer->SetShaderFloat("gAmbient", 0.3f);
		});

	lpCollider->InitSphere(Vector3(0.f, 0.f, 40.f), 30);

	fHp = 100.f;
}

void MonsterA::Update()
{
	LookAtPlayer();
}
