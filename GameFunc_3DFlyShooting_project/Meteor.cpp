#include "DXUT.h"
#include "Meteor.h"

//Manager
#include "ImageManager.h"
#include "CameraManager.h"

//Component
#include "ShaderRenderer.h"
#include "SphereCollider.h"
#include "Transform.h"
//Object
#include"PlayerAirplane.h"

#include "Func.h"

Meteor::Meteor()
	:eType(E_METEOR_01), lpRenderer(nullptr), lpPlayer(nullptr), 
	fOriginColliderScale(30.f)
{
}


Meteor::~Meteor()
{
}

void Meteor::Init()
{
	float fScale = GetRandomNumber(5.f, 8.f);
	transform->scale = Vector3(fScale, fScale, fScale);

	float fRotation = GetRandomNumber(0.f, 6.28f);
	transform->rot = Vector3(fRotation, fRotation, fRotation);

	lpCollider = AC(SphereCollider);
	lpCollider->InitSphere(Vector3(0.f, 0.f, 0.f), fOriginColliderScale * transform->scale.x);
	lpCollider->SetEnable(false);
}

void Meteor::Update()
{
	if (lpPlayer)
	{
		if (lpPlayer->GetDestroy())
		{
			return;
		}
		else
		{
			Vector3 vLength = lpPlayer->transform->worldPos - transform->pos;
			float fLength = D3DXVec3Length(&vLength);

			if (fLength < (fOriginColliderScale* transform->scale.x) + 100)
				lpCollider->SetEnable(true);
			else
				lpCollider->SetEnable(false);
		}
	}
}

void Meteor::SetMeteor(MeteorType _eType)
{
	eType = _eType;

	lpRenderer = AC(ShaderRenderer);
	
	lpRenderer->SetEffect(IMAGE.LoadEffect("Lighting", "./Lighting.fx"));
	
	lpRenderer->SetRenderBegin([&]() {
		lpRenderer->SetShaderVector("gWorldCamera", &Vector4(CAMERA.GetPos(), 1.f));
		lpRenderer->SetShaderTexture("gDiffuseMap", lpRenderer->GetMesh()->GetDiffuseMap(0));
		lpRenderer->SetShaderTexture("gSpecularMap", lpRenderer->GetMesh()->GetDiffuseMap(0));
		lpRenderer->SetShaderFloat("gAmbient", 0.3f);
		});

	switch (eType)
	{
	case E_METEOR_01:
		lpRenderer->LoadMesh(IMAGE.LoadObjFile("MeteorA", "./rs/obj/Meteor/Meteor1/Meteor_A.obj"));
		break;
	case E_METEOR_02:
		lpRenderer->LoadMesh(IMAGE.LoadObjFile("MeteorB", "./rs/obj/Meteor/Meteor2/Meteor_B.obj"));
		break;
	case E_METEOR_03:
		lpRenderer->LoadMesh(IMAGE.LoadObjFile("MeteorC", "./rs/obj/Meteor/Meteor3/Meteor_C.obj"));
		break;
	default:
		break;
	}
}

void Meteor::SetPlayer(PlayerAirplane* player)
{
	lpPlayer = player;
}
