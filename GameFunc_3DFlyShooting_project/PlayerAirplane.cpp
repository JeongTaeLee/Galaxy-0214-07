#include "DXUT.h"
#include "PlayerAirplane.h"

//Component
#include "Renderer.h"
#include "ShaderRenderer.h"
#include "Transform.h"

//Manager
#include "ImageManager.h"
#include "CameraManager.h"
#include "TimeManager.h"
#include "InputManager.h"

PlayerAirplane::PlayerAirplane()
	:lpRenderer(nullptr), vForwardDir(0.f, 0.f, 1.f),
	vCameraDir(0.f, 0.f, 0.f), fCameraDistance(350.f),
	fSpeed(50.f), fAddSpeed(0.f)
{
}


PlayerAirplane::~PlayerAirplane()
{
}

void PlayerAirplane::Init()
{
	transform->pos.y += 100;
#pragma region RendererSetting
	lpRenderer = AC(ShaderRenderer);
	lpRenderer->LoadMesh(IMAGE.LoadObjFile("Player_Airplane", "./rs/obj/Player/Player.obj"));
	lpRenderer->SetEffect(IMAGE.LoadEffect("Lighting", "Lighting.fx"));
	
	lpRenderer->SetRenderBegin(
		[&]() {

			lpRenderer->SetShaderVector("gWorldCamera", &CAMERA.GetV4Pos());
			lpRenderer->SetShaderTexture("gMap", lpRenderer->GetMesh()->GetTexture(0));
		});
#pragma endregion RendererSetting

#pragma region CameraSetting
	fCameraAngle = 135.f;

	float z = D3DXToRadian(fCameraAngle);
	float y = D3DXToRadian(fCameraAngle);

	vCameraDir.z = cosf(z);
	vCameraDir.y = sinf(y);

	SetCamera();
#pragma endregion CameraSetting

}

void PlayerAirplane::Update()
{
	Move();
	SetCamera();
}

void PlayerAirplane::Move()
{
	if (KEYPRESS('A') || KEYPRESS('D'))
	{
		float fRotAngle;
		
		if (KEYPRESS('A'))
			fRotAngle = -D3DXToRadian(5);
		if (KEYPRESS('D'))
			fRotAngle = +D3DXToRadian(5);

		D3DXMATRIX matRot;
		D3DXMatrixRotationY(&matRot, fRotAngle);

		D3DXVec3TransformNormal(&vForwardDir, &vForwardDir, &matRot);
		D3DXVec3TransformNormal(&vCameraDir, &vCameraDir, &matRot);
		
		transform->rot.y += fRotAngle;
	}


	if (KEYPRESS('W'))
		transform->pos += vForwardDir * (100 * Et);
	if (KEYPRESS('S'))
		transform->pos += (-vForwardDir) * (100 * Et);
}

void PlayerAirplane::SetCamera()
{
	
	CAMERA.SetCameraInfo(
		transform->worldPos + vCameraDir * fCameraDistance,
		transform->worldPos + Vector3(0.f, 210.f, 0.f));
}
