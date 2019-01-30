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
{
}


PlayerAirplane::~PlayerAirplane()
{
}

void PlayerAirplane::Init()
{
	lpRenderer = AC(ShaderRenderer);
	lpRenderer->LoadMesh(IMAGE.LoadObjFile("Player_Airplane", "./rs/obj/Player.obj"));
	lpRenderer->SetEffect(IMAGE.LoadEffect("Lighting", "Lighting.fx"));
	
	lpRenderer->SetRenderBegin(
		[&]() {
			lpRenderer->GetEffect()->SetVector(D3DXHANDLE("gWorldCamera"), 
				&D3DXVECTOR4(CAMERA.GetPos()->x, CAMERA.GetPos()->y, CAMERA.GetPos()->z, 0.f));
			lpRenderer->GetEffect()->SetTexture(D3DXHANDLE("gMap"), lpRenderer->GetMesh()->vMaterial[0]->map->lpD3DTexture);
		});
}
