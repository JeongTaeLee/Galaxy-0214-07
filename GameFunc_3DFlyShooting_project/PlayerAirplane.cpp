#include "DXUT.h"
#include "PlayerAirplane.h"

//Component
#include "Renderer.h"
#include "ShaderRenderer.h"
#include "Transform.h"

//Manager
#include "ImageManager.h"
#include "CameraManager.h"

PlayerAirplane::PlayerAirplane()
	:lpRenderer(nullptr), vForwardDir(0.f, 0.f, 1.f),
	fSpeed(50.f), fAddSpeed(0.f)
{
}


PlayerAirplane::~PlayerAirplane()
{
}

void PlayerAirplane::Init()
{
	lpRenderer = AC(ShaderRenderer);
	lpRenderer->LoadMesh(IMAGE.LoadObjFile("Player_Airplane", "./rs/obj/Player/Player.obj"));
	lpRenderer->SetEffect(IMAGE.LoadEffect("Lighting", "Lighting.fx"));
	
	lpRenderer->SetRenderBegin(
		[&]() {

			lpRenderer->SetShaderVector("gWorldCamera", &CAMERA.GetV4Pos());
			lpRenderer->SetShaderTexture("gMap", lpRenderer->GetMesh()->GetTexture(0));
		});

}

void PlayerAirplane::Update()
{
	Move();
}

void PlayerAirplane::Move()
{
	transform->pos += vForwardDir * (fSpeed * DXUTGetElapsedTime());
}
