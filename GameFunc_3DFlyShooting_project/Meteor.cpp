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
	:lpRenderer(nullptr), lpPlayer(nullptr), 
	fOriginColliderScale(30.f)
{
	sTag = "Meteor";
}


Meteor::~Meteor()
{
}

void Meteor::Init()
{
#pragma region Renderer
	lpRenderer = AC(ShaderRenderer);
	lpRenderer->LoadMesh(IMAGE.LoadObjFile("Meteor", "./rs/obj/Meteor/Meteor.obj"));
	
	lpRenderer->SetEffect(IMAGE.LoadEffect("Lighting", "./Lighting"));
	lpRenderer->SetRenderBegin(
		[&]() {
			lpRenderer->SetShaderVector("gWorldCamera", &Vector4(CAMERA.GetPos(), 1.f));
			lpRenderer->SetShaderTexture("gDiffuseMap", lpRenderer->GetMesh()->GetDiffuseMap(0));
			lpRenderer->SetShaderTexture("gSpecularMap", lpRenderer->GetMesh()->GetSpecularMap(0));
			lpRenderer->SetShaderFloat("gAmbient", 0.3f);
		});

#pragma endregion Renderer
#pragma region Collider
	lpCollider = AC(SphereCollider);
	lpCollider->InitSphere(Vector3(0.f, 0.f, 0.f), fOriginColliderScale * transform->scale.x);
	lpCollider->SetEnable(false);
#pragma endregion Collider

	float fScale = GetRandomNumber(5.f, 15.f);
	transform->scale = Vector3(fScale, fScale, fScale);

	float fRotation = GetRandomNumber(0.f, 6.28f);
	transform->rot = Vector3(fRotation, fRotation, fRotation);
}

void Meteor::Update()
{
	if (lpPlayer)
	{
		if (lpPlayer->GetDestroy())
			return;
		else
		{
			Vector3 vLength = lpPlayer->transform->worldPos - transform->pos;
			float fLength = D3DXVec3Length(&vLength);

			if (fLength < (fOriginColliderScale* transform->scale.x) + 500)
				lpCollider->SetEnable(true);
			else
				lpCollider->SetEnable(false);
		}
	}
}

void Meteor::SetPlayer(PlayerAirplane* player)
{
	lpPlayer = player;
}

void Meteor::ReceiveCollider(Collider* lpOther)
{
	if (lpOther->gameObject->sTag == "PlayerAirPlane")
	{
		SetDestroy(true);
	}
}
