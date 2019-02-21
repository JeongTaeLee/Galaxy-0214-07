#include "DXUT.h"
#include "MonsterDirector.h"

//Manager
#include "ImageManager.h"
#include "CameraManager.h"

//Component & GameObject
#include "Transform.h"
#include "ShaderRenderer.h"

#include "AirPlane.h"
#include "MonsterAirPlane.h"
MonsterDirector::MonsterDirector()
	:lpRenderer(nullptr)
{
}


MonsterDirector::~MonsterDirector()
{
}

void MonsterDirector::Init()
{
	transform->eUpdateType = E_UPDATE_02;

	lpRenderer = AC(ShaderRenderer);
	lpRenderer->LoadMesh(IMAGE.LoadObjFile("PlayerDirector", "./rs/obj/PlayerDirector/PlayerDirector.obj"));
	lpRenderer->SetEffect(IMAGE.LoadEffect("Lighting", "Lighting.fx"));

	lpRenderer->SetRenderBegin(
		[&]() {
			lpRenderer->SetShaderVector("gWorldCamera", &Vector4(CAMERA.GetPos(), 1.f));
			lpRenderer->SetShaderTexture("gDiffuseMap", lpRenderer->GetMesh()->GetDiffuseMap(0));
			lpRenderer->SetShaderTexture("gSpecularMap", lpRenderer->GetMesh()->GetDiffuseMap(0));
			lpRenderer->SetShaderFloat("gAmbient", 0.3f);
		});

	transform->scale = Vector3(0.6f, 0.6f, 0.6f);
}

void MonsterDirector::SetDirection(MonsterAirPlane* monster)
{
	Quaternion qRot;
	GetLookAt(qRot, monster->transform->worldPos, transform->worldPos);
	transform->qRot = qRot;
}

void MonsterDirector::SetPos(Vector3 _vPos)
{
	transform->pos = _vPos;
}
