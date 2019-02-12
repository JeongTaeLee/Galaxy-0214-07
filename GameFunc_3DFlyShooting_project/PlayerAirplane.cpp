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
#include "ObjectManager.h"

//Object
#include "PlayerBullet.h"


PlayerAirplane::PlayerAirplane()
	:vCameraPos(0.f, 0.f, 0.f), vCameraLookAt(0.f, 0.f, 0.f), 
	vCameraDir(0.f, 0.f, 0.f), vCameraLookAtDir(0.f, 0.f, 0.f),
	fCameraDistance(0.f), fCameraLookAtDistance(0.f)

{
}


PlayerAirplane::~PlayerAirplane()
{
}

void PlayerAirplane::Init()
{
	transform->bTransformUpdate = false;
	INPUT.SetMouseClip(true);

#pragma region RendererSetting
	lpRenderer = AC(ShaderRenderer);
	lpRenderer->LoadMesh(IMAGE.LoadObjFile("Player_Airplane", "./rs/obj/Player/PlayerAirPlane.obj"));
	lpRenderer->SetEffect(IMAGE.LoadEffect("Lighting", "Lighting.fx"));
	
	lpRenderer->SetRenderBegin(
		[&]() {
			lpRenderer->SetShaderVector("gWorldCamera", &CAMERA.GetV4Pos());
			lpRenderer->SetShaderTexture("gDiffuseMap", lpRenderer->GetMesh()->GetDiffuseMap(0));
			lpRenderer->SetShaderTexture("gSpecularMap", lpRenderer->GetMesh()->GetSpecularMap(0));
			lpRenderer->SetShaderFloat("gAmbient", 0.3f);
		});
#pragma endregion RendererSetting

#pragma region CameraSetting

	//Pos
	float fCameraAngle = 160.f * (D3DX_PI / 180);
	fCameraDistance = 140.f;

	vCameraDir.x = 0.f;
	vCameraDir.y = sinf(fCameraAngle);
	vCameraDir.z = cosf(fCameraAngle);

	vCameraPos = vCameraDir * fCameraDistance;

	//LookAt
	fCameraLookAtDistance = vCameraPos.y;
	
	vCameraLookAt = transform->pos + Vector3(0.f, fCameraLookAtDistance, 0.f);
	vCameraLookAtDir = vCameraLookAt - transform->pos;
	normalize(vCameraLookAtDir);
	
	vCameraLookAt = vCameraLookAtDir * fCameraLookAtDistance;

	CAMERA.SetCameraPos(vCameraPos, false, 0.1f);
	CAMERA.SetCameraLookAt(vCameraLookAt, false, 0.1f);
	CAMERA.SetCameraUp(vAxis[E_AXIS_UP], false, 0.1f);

#pragma endregion CameraSetting 

}

void PlayerAirplane::Update()
{
	if (KEYDOWN('G'))
	{
		memset(&vAxis, 0, sizeof(Vector3) * 3);
		vAxis[E_AXIS_FORWARD] = Vector3(0.f, 0.f, 1.f);
		vAxis[E_AXIS_UP] = Vector3(0.f, 1.f, 0.f);
		vAxis[E_AXIS_RIGHT] = Vector3(1.f, 0.f, 0.f);

		transform->rot = Vector3(0.f, 0.f, 0.f);
	}

	InputMouse();
	//InputKeyboard();

	D3DXMatrixTranslation(&transform->matPos, transform->pos.x, transform->pos.y, transform->pos.z);
	D3DXMatrixScaling(&transform->matScale, transform->scale.x, transform->scale.y, transform->scale.z);
}

void PlayerAirplane::InputMouse()
{
	// vGap : 전프레임과 현재 프레임의 마우스 위치의 차이.
	Vector2 vGap(INPUT.GetMouseGap());

	//fRollAngle: Forward축으로 돌릴 회전값
	float fRollAngle = -(D3DXToRadian(vGap.x) * 0.05f);
	//fPitchAngle  : Right축으로 돌릴 회전값
	float fPitchAngle = -(D3DXToRadian(vGap.y) * 0.05f);
	//fYawAngle 
	float fYawAngle = 0.f;

#pragma region AIRPLANE ROTATION
	if (fRollAngle)
		AirPlane::RollRotation(fRollAngle);
	if (fYawAngle)
		AirPlane::YawRotation(fYawAngle);
	if (fPitchAngle)
		AirPlane::PitchRotation(fPitchAngle);

	if (fRollAngle || fYawAngle || fPitchAngle)
		D3DXMatrixRotationQuaternion(&transform->matRot, &transform->qRot);
#pragma endregion AIRPLANE ROTATION
}

void PlayerAirplane::InputKeyboard()
{
	transform->pos += vAxis[E_AXIS_FORWARD] * (100 * Et);
	
	/*
	if (KEYDOWN(VK_SPACE))
	{ 
		Vector3 LeftFirePos = Vector3(-20.f, 0.f, 30.f);
		Vector3 RightFirePos = Vector3(20.f, 0.f, 30.f);
	
		D3DXMATRIX matRot = transform->matRot;
		memcpy(&matRot._41, transform->pos, sizeof(Vector3));
	
		D3DXVec3TransformCoord(&LeftFirePos, &LeftFirePos, &matRot);
		D3DXVec3TransformCoord(&RightFirePos, &RightFirePos, &matRot);
	
		OBJECT.AddObject<PlayerBullet>()
			->SetBullet(LeftFirePos, transform->matRot, 1500, 1.f);
		OBJECT.AddObject<PlayerBullet>()
			->SetBullet(RightFirePos, transform->matRot, 1500.f, 1.f);
	}
	
	*/

	//카메라 위치 셋팅
	vCameraPos = transform->pos + (vCameraDir * fCameraDistance);
	vCameraLookAt = transform->pos + (vCameraLookAtDir * fCameraLookAtDistance);
	
	CAMERA.SetCameraPos(vCameraPos, false, 0.1f);
	CAMERA.SetCameraLookAt(vCameraLookAt, true, 0.1f);
	CAMERA.SetCameraUp(vAxis[E_AXIS_UP], true, 0.1f);
}


// 쿡앤 토런스 cook & torrance