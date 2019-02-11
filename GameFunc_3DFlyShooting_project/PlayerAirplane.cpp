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
	:lpRenderer(nullptr), 
	vCameraPos(0.f, 0.f, 0.f), vCameraLookAt(0.f, 0.f, 0.f), 
	vCameraDir(0.f, 0.f, 0.f), vCameraLookAtDir(0.f, 0.f, 0.f),
	fCameraDistance(0.f), fCameraLookAtDistance(0.f)

{
	memset(&vAxis, 0, sizeof(Vector3) * 3);
	vAxis[E_AXIS_FORWARD] = Vector3(0.f, 0.f, 1.f);
	vAxis[E_AXIS_UP] = Vector3(0.f, 1.f, 0.f);
	vAxis[E_AXIS_RIGHT] = Vector3(1.f, 0.f, 0.f);

	transform->scale = Vector3(1, 1, 1);
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
	fCameraDistance = 120.f;

	vCameraDir.x = 0.f;
	vCameraDir.y = sinf(fCameraAngle);
	vCameraDir.z = cosf(fCameraAngle);

	vCameraPos = vCameraDir * fCameraDistance;

	//LookAt
	fCameraLookAtDistance = vCameraPos.y;
	
	vCameraLookAt = transform->pos + Vector3(0.f, fCameraLookAtDistance, 0.f);
	vCameraLookAtDir = vCameraLookAt - transform->pos;
	
	vCameraLookAt = vCameraLookAtDir * fCameraLookAtDistance;
	normalize(vCameraLookAtDir);
	

	CAMERA.SetCameraInfo(vCameraPos, vCameraLookAt, vAxis[E_AXIS_UP]);
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
	InputKeyboard();

	D3DXMatrixTranslation(&transform->matPos, transform->pos.x, transform->pos.y, transform->pos.z);
	D3DXMatrixScaling(&transform->matScale, transform->scale.x, transform->scale.y, transform->scale.z);
}

void PlayerAirplane::InputMouse()
{
	// vGap : �������Ӱ� ���� �������� ���콺 ��ġ�� ����.
	Vector2 vGap(INPUT.GetMouseGap());

	//fRollAngle: Forward������ ���� ȸ����
	float fRollAngle = -(D3DXToRadian(vGap.x) * 0.05f);
	//fPitchAngle  : Right������ ���� ȸ����
	float fPitchAngle = -(D3DXToRadian(vGap.y) * 0.05f);
	//fYawAngle 
	float fYawAngle = 0.f;

	//Ű���� ���� 
	if (KEYPRESS(VK_UP))
		fPitchAngle += D3DXToRadian(2.f);
	if (KEYPRESS(VK_DOWN))
		fPitchAngle -= D3DXToRadian(2.f);

	if (KEYPRESS(VK_RIGHT))
		fRollAngle -= D3DXToRadian(2.f);
	if (KEYPRESS(VK_LEFT))
		fRollAngle += D3DXToRadian(2.f);

	if (KEYPRESS('A'))
		fYawAngle -= D3DXToRadian(0.5f);
	if (KEYPRESS('D'))
		fYawAngle += D3DXToRadian(0.5f);

	// �� ���� ȸ����İ� �ʱ�ȭ
	D3DXMATRIX matRollRot;
	D3DXMatrixIdentity(&matRollRot);

	D3DXMATRIX matPitchRot;
	D3DXMatrixIdentity(&matPitchRot);

	D3DXMATRIX matYawRot;
	D3DXMatrixIdentity(&matYawRot);

#pragma region AIRPLANE ROTATION
	// �÷��̾ ȸ�� �ڵ�

	if (fRollAngle)
	{
		// Forward ������ ȸ���� Matrix�� �ٸ��࿡�� ��������ش� 
		D3DXMatrixRotationAxis(&matRollRot, &vAxis[E_AXIS_FORWARD], fRollAngle);
		
		D3DXVec3TransformNormal(&vAxis[E_AXIS_RIGHT], &vAxis[E_AXIS_RIGHT], &matRollRot);
		D3DXVec3TransformNormal(&vAxis[E_AXIS_UP], &vAxis[E_AXIS_UP], &matRollRot);
	}

	if (fPitchAngle)
	{
		// Right ������ ȸ���� Matrix�� �ٸ��࿡�� ��������ش� 
		D3DXMatrixRotationAxis(&matPitchRot, &vAxis[E_AXIS_RIGHT], fPitchAngle);
		
		D3DXVec3TransformNormal(&vAxis[E_AXIS_FORWARD], &vAxis[E_AXIS_FORWARD], &matPitchRot);
		D3DXVec3TransformNormal(&vAxis[E_AXIS_UP], &vAxis[E_AXIS_UP], &matPitchRot);
	}
	if (fYawAngle)
	{
		// Up ������ ȸ���� Matrix�� �ٸ��࿡�� ��������ش� 
		D3DXMatrixRotationAxis(&matYawRot, &vAxis[E_AXIS_UP], fYawAngle);

		D3DXVec3TransformNormal(&vAxis[E_AXIS_FORWARD], &vAxis[E_AXIS_FORWARD], &matYawRot);
		D3DXVec3TransformNormal(&vAxis[E_AXIS_RIGHT], &vAxis[E_AXIS_RIGHT], &matYawRot);
	}

	if (fPitchAngle || fRollAngle || fYawAngle)
		transform->matRot = transform->matRot * matRollRot * matPitchRot * matYawRot;	

#pragma endregion AIRPLANE ROTATION

#pragma region CAMERA_SETTING	
	// ī�޶� ȸ�� �ڵ�
	// ���� ȸ�� ����� �÷��̾�� ī�޶���ġ, ī�޶�LookAt��ġ�� ���� ���⿡ ��������ش�. 
	if (fRollAngle)
	{
		D3DXVec3TransformNormal(&vCameraLookAtDir, &vCameraLookAtDir, &matRollRot);
		D3DXVec3TransformNormal(&vCameraDir, &vCameraDir, &matRollRot);
	}

	if (fPitchAngle)
	{
		D3DXVec3TransformNormal(&vCameraLookAtDir, &vCameraLookAtDir, &matPitchRot);
		D3DXVec3TransformNormal(&vCameraDir, &vCameraDir, &matPitchRot);
	}

	if (fYawAngle)
	{
		D3DXVec3TransformNormal(&vCameraLookAtDir, &vCameraLookAtDir, &matYawRot);
		D3DXVec3TransformNormal(&vCameraDir, &vCameraDir, &matYawRot);
	}
#pragma endregion CAMERA_SETTING

}

void PlayerAirplane::InputKeyboard()
{
	transform->pos += vAxis[E_AXIS_FORWARD] * (400 * Et);

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

	//ī�޶� ��ġ ����
	vCameraPos = transform->pos + (vCameraDir * fCameraDistance);
	vCameraLookAt = transform->pos + (vCameraLookAtDir * fCameraLookAtDistance);

	CAMERA.SetCameraInfo(vCameraPos, vCameraLookAt, vAxis[E_AXIS_UP], true, 0.9f);
}


// ��� �䷱�� cook & torrance