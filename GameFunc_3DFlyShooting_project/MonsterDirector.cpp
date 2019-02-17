#include "DXUT.h"
#include "MonsterDirector.h"

//Manager
#include "ImageManager.h"
#include "CameraManager.h"

//Component & GameObject
#include "Transform.h"
#include "ShaderRenderer.h"

#include "AirPlane.h"
#include "PlayerAirplane.h"

#include "Func.h"

MonsterDirector::MonsterDirector()
	:lpPlayer(nullptr), lpRenderer(nullptr), 
	fShortLength(0.f)	
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

void MonsterDirector::Update()
{
	if (lpPlayer)
		transform->pos = CAMERA.vLookAt + lpPlayer->GetAxis(AirPlaneAxis::E_AXIS_UP) * 10;


	DirectionMonster();
}

void MonsterDirector::DirectionMonster()
{
	GetLookAt(vShortPos, transform->pos, transform->qRot, 0.5);
	fShortLength = 0;
}

void MonsterDirector::ReceviePMLength(const Vector3 & pos, float fLength)
{
	if (fShortLength == 0.f)
	{
		vShortPos = pos;
		fShortLength = fLength;
	}
	else
	{
		if (fShortLength > fLength)
		{
			vShortPos = pos;
			fShortLength = fLength;
		}
	}
}
