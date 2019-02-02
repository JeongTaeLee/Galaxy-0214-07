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
	:lpRenderer(nullptr), vCameraLookAt(0.f, 0.f, 0.f), 
	vCameraPos(0.f, 0.f, 0.f), fCameraDistance(0.f)
{
	memset(&vAxis, 0, sizeof(Vector3) * 3);
	vAxis[E_AXIS_FORWARD] = Vector3(0.f, 0.f, 1.f);
	vAxis[E_AXIS_UP] = Vector3(0.f, 1.f, 0.f);
	vAxis[E_AXIS_RIGHT] = Vector3(1.f, 0.f, 0.f);
}


PlayerAirplane::~PlayerAirplane()
{
}

void PlayerAirplane::Init()
{
	INPUT.SetMouseClip(true);

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
	float fCameraAngle = 160.f * (D3DX_PI / 180);

	vCameraDir.x = 0.f;
	vCameraDir.y = sinf(fCameraAngle);
	vCameraDir.z = cosf(fCameraAngle);

	fCameraDistance = 160.f;
	vCameraPos = vCameraDir * fCameraDistance;
	vCameraLookAt = transform->pos + Vector3(0.f, 70.f, 0.f);

	CAMERA.SetCameraInfo(vCameraPos, vCameraLookAt);
#pragma endregion CameraSetting

}

void PlayerAirplane::Update()
{
	InputMouse();
	InputKeyboard();
}

void PlayerAirplane::InputMouse()
{
	Vector3 vMouseGap = INPUT.GetMouseGap();

	D3DXMATRIX	matRot;
	D3DXMatrixIdentity(&matRot);

	Vector3		vDist = Vector3(0.f, 0.f, 0.f);

	float		fAngle = 0.f;

	if (vMouseGap.x != 0.f)
	{
		fAngle = (D3DXToRadian(vMouseGap.x) * 3) * Et;

		D3DXMatrixRotationY(&matRot, fAngle);
		memcpy(&matRot._41, &vCameraLookAt, sizeof(Vector3));

		vDist = vCameraPos - vCameraLookAt;
		D3DXVec3TransformCoord(&vCameraPos, &vDist, &matRot);
		D3DXVec3TransformNormal(&vAxis[E_AXIS_FORWARD], &vAxis[E_AXIS_FORWARD], &matRot);
	
		transform->rot.y += fAngle;
	}
	if (vMouseGap.y != 0.f)
	{	
		Vector3 vUp = Vector3(0.f, 1.f, 0.f);

		D3DXVec3Cross(&vAxis[E_AXIS_RIGHT], &vAxis[E_AXIS_FORWARD], &vUp);
		D3DXVec3Cross(&vAxis[E_AXIS_UP], &vAxis[E_AXIS_RIGHT], &vAxis[E_AXIS_FORWARD]);

		fAngle = (D3DXToRadian(vMouseGap.y) * 3) * Et;

		D3DXMatrixRotationAxis(&matRot, &vAxis[E_AXIS_RIGHT], -fAngle);
		memcpy(&matRot._41, &vCameraLookAt, sizeof(Vector3));

		vDist = vCameraPos - vCameraLookAt;
		D3DXVec3TransformCoord(&vCameraPos, &vDist, &matRot);
		D3DXVec3TransformNormal(&vAxis[E_AXIS_FORWARD], &vAxis[E_AXIS_FORWARD], &matRot);

		transform->rot.x += fAngle;
	}

	CAMERA.SetCameraInfo(vCameraPos, vCameraLookAt);
}

void PlayerAirplane::InputKeyboard()
{
	Vector3 vMove = Vector3(0.f, 0.f, 0.f);

	if (KEYPRESS('W'))
		vMove += vAxis[E_AXIS_FORWARD] * (200 * Et);
	if (KEYPRESS('S'))
		vMove -= vAxis[E_AXIS_FORWARD] * (200 * Et);
		

	transform->pos += vMove;
	vCameraPos += vMove;
	vCameraLookAt += vMove;
}


