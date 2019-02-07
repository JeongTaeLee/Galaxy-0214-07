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

	CAMERA.SetCameraInfo(vCameraPos, vCameraLookAt, vAxis[E_AXIS_UP]);
#pragma endregion CameraSetting

}

void PlayerAirplane::Update()
{

	InputMouse();
	InputKeyboard();
}

void PlayerAirplane::InputMouse()
{
	Vector2 vGap(INPUT.GetMouseGap());

	D3DXMATRIX matRot;
	Vector3 vDist;
	float fAngle;

	/*
	D3DXVec3Cross(&vAxis[E_AXIS_RIGHT], &vAxis[E_AXIS_FORWARD], &vAxis[E_AXIS_UP]);
	normalize(vAxis[E_AXIS_RIGHT]);
	D3DXVec3Cross(&vAxis[E_AXIS_UP], &vAxis[E_AXIS_RIGHT], &vAxis[E_AXIS_FORWARD]);
	normalize(vAxis[E_AXIS_UP]);	
	
	if (vGap.y != 0)
	{
		fAngle = (D3DXToRadian(vGap.y) * 0.1f);
		
		//vCameraPos
		vDist = vCameraPos - transform->pos;
	
		D3DXMatrixRotationAxis(&matRot, &vAxis[E_AXIS_RIGHT], fAngle);
		memcpy(&matRot._41, &transform->pos, sizeof(Vector3));
	
		D3DXVec3TransformCoord(&vCameraPos, &vDist, &matRot);
		D3DXVec3TransformNormal(&vAxis[E_AXIS_FORWARD], &vAxis[E_AXIS_FORWARD], &matRot);
		normalize(vAxis[E_AXIS_FORWARD]);
	
		//vCameraLookAt
		vDist = vCameraLookAt - transform->pos;
		
		D3DXMatrixRotationAxis(&matRot, &vAxis[E_AXIS_RIGHT], fAngle);
		memcpy(&matRot._41, &transform->pos, sizeof(Vector3));
	
		D3DXVec3TransformCoord(&vCameraLookAt, &vDist, &matRot);
	}

	if (vGap.x != 0)
	{
		fAngle = (D3DXToRadian(vGap.x) * 0.1f);
		
		//vCameraPos
		vDist = vCameraPos - transform->pos;
	
		D3DXMatrixRotationAxis(&matRot, &vAxis[E_AXIS_UP], fAngle);
		memcpy(&matRot._41, &transform->pos, sizeof(Vector3));
	
		D3DXVec3TransformCoord(&vCameraPos, &vDist, &matRot);
		D3DXVec3TransformNormal(&vAxis[E_AXIS_FORWARD], &vAxis[E_AXIS_FORWARD], &matRot);
		normalize(vAxis[E_AXIS_FORWARD]);
	
		//vCameraLookAt
		vDist = vCameraLookAt - transform->pos;
	
		D3DXMatrixRotationAxis(&matRot, &vAxis[E_AXIS_UP], fAngle);
		memcpy(&matRot._41, &transform->pos, sizeof(Vector3));
	
		D3DXVec3TransformCoord(&vCameraLookAt, &vDist, &matRot);
	
	}
	*/

#pragma region AIRPLANE ROTATION

	D3DXMATRIX matXRot;
	D3DXMatrixIdentity(&matXRot);
	D3DXMATRIX matYRot;
	D3DXMatrixIdentity(&matYRot);

	bool bRotation = false;

	if (vGap.y != 0.f)
	{
		float fXRotation = D3DXToRadian(vGap.y) * 0.1f;

		D3DXMatrixRotationAxis(&matXRot, &vAxis[E_AXIS_RIGHT], fXRotation);
		D3DXVec3TransformNormal(&vAxis[E_AXIS_FORWARD], &vAxis[E_AXIS_FORWARD], &matXRot);
		D3DXVec3TransformNormal(&vAxis[E_AXIS_UP], &vAxis[E_AXIS_UP], &matXRot);
		bRotation = true;
	}
	if (vGap.x != 0.f)
	{
		float fYRotation = D3DXToRadian(vGap.x) * 0.1f;

		D3DXMatrixRotationAxis(&matYRot, &vAxis[E_AXIS_UP], fYRotation);
		D3DXVec3TransformNormal(&vAxis[E_AXIS_FORWARD], &vAxis[E_AXIS_FORWARD], &matYRot);
		D3DXVec3TransformNormal(&vAxis[E_AXIS_RIGHT], &vAxis[E_AXIS_RIGHT], &matYRot);
		bRotation = true;
	}

	if (bRotation)
	{
		D3DXMATRIX matTotal = matXRot * matYRot;
		
		D3DXQUATERNION matR;
		D3DXMatrixDecompose(&Vector3(), &matR, &Vector3(), &matTotal);
		
		transform->rot = Vector3(matR.x, matR.y, matR.z);
		DEBUG_VEC(matR);
	}

#pragma endregion AIRPLANE ROTATION

	//CAMERA.SetCameraInfo(vCameraPos, vCameraLookAt, vAxis[E_AXIS_UP]);
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


