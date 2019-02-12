#include "DXUT.h"
#include "PlayerAirplane.h"

//Component
#include "Renderer.h"
#include "ShaderRenderer.h"
#include "Transform.h"
#include "SphereCollider.h"
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
	fCameraDistance(0.f), fCameraLookAtDistance(0.f),
	bCameraBack(false), fMaxSpeed(0.f)
{
	D3DXQuaternionIdentity(&qCameraRot);
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
			lpRenderer->SetShaderVector("gWorldCamera", &Vector4(CAMERA.GetPos(), 1.f));
			lpRenderer->SetShaderTexture("gDiffuseMap", lpRenderer->GetMesh()->GetDiffuseMap(0));
			lpRenderer->SetShaderTexture("gSpecularMap", lpRenderer->GetMesh()->GetSpecularMap(0));
			lpRenderer->SetShaderFloat("gAmbient", 0.3f);
		});
#pragma endregion RendererSetting

#pragma region CameraSetting
	fCameraAngle = D3DXToRadian(20.f);
	fCameraDistance = 150.f;

	CamreaSetting();
#pragma endregion CameraSetting 

#pragma region Collider
	AC(SphereCollider)->InitSphere(Vector3(40.f, 0.f, -20.f), 20);
	AC(SphereCollider)->InitSphere(Vector3(-40.f, 0.f, -20.f), 20);
	AC(SphereCollider)->InitSphere(Vector3(0.f, 0.f, 20.f), 20);
	AC(SphereCollider)->InitSphere(Vector3(0.f, 0.f, -20.f), 20);
#pragma endregion Collider
}

void PlayerAirplane::Update()
{
	InputMouse();
	InputKeyboard();

	if (fSpeed > fMaxSpeed)
		fSpeed -= PlayerUnAccel;

	transform->pos += vAxis[E_AXIS_FORWARD] * (fSpeed * Et);

	AirPlane::SetAirPlaneMatrix();

	if (KEYDOWN(VK_SPACE))
	{
		Vector3 LeftFirePos = Vector3(-20.f, 0.f, 30.f);
		Vector3 RightFirePos = Vector3(20.f, 0.f, 30.f);

		D3DXMATRIX matRot;
		D3DXMatrixRotationQuaternion(&matRot, &transform->qRot);
		memcpy(&matRot._41, transform->pos, sizeof(Vector3));

		D3DXVec3TransformCoord(&LeftFirePos, &LeftFirePos, &matRot);
		D3DXVec3TransformCoord(&RightFirePos, &RightFirePos, &matRot);

		OBJECT.AddObject<PlayerBullet>()
			->SetBullet(LeftFirePos, transform->qRot, 2000.f, 1.f);
		OBJECT.AddObject<PlayerBullet>()
			->SetBullet(RightFirePos, transform->qRot, 2000.f, 1.f);
	}

	CamreaSetting();
}

void PlayerAirplane::InputMouse()
{
	Vector2 vGap(INPUT.GetMouseGap());

	float XGap = D3DXToRadian(vGap.x) * 0.05f;
	float YGap = D3DXToRadian(vGap.y) * 0.05f;

	if (XGap)
		fRollAngle = (XGap * -1);
	if (YGap)
		fPitchAngle = (YGap * -1);
}

void PlayerAirplane::InputKeyboard()
{
	if (KEYPRESS(VK_UP))
		fPitchAngle = PlayerPitchAngle;
	if (KEYPRESS(VK_DOWN))
		fPitchAngle = -PlayerPitchAngle;
	
	if (KEYPRESS(VK_LEFT))
		fRollAngle = PlayerRollAngle;
	if (KEYPRESS(VK_RIGHT))
		fRollAngle = -PlayerRollAngle;

	if (KEYPRESS('A'))
		fYawAngle = -PlayerYawAngle;
	if (KEYPRESS('D'))
		fYawAngle = PlayerYawAngle;

	if (KEYPRESS('C'))
		bCameraBack = true;
	else if (KEYPRESS(VK_MBUTTON))
		bCameraBack = true;
	else
		bCameraBack = false;

	if (KEYPRESS('W'))
	{
		if(fSpeed < fMaxSpeed)
			fSpeed += PlayerAccel;
	}
	
	if (KEYPRESS('S'))
	{
		if(fSpeed > 0.f)
			fSpeed -= PlayerUnAccel;
	}

	if (KEYPRESS(VK_LSHIFT))
		fMaxSpeed = 800.f;
	else
		fMaxSpeed = 500.f;	
}

void PlayerAirplane::CamreaSetting()
{
	Vector3 vCameraDir = Vector3(0.f, 0.f, bCameraBack ? 1.f : -1.f);

	D3DXQuaternionSlerp(&qCameraRot, &qCameraRot, &transform->qRot, 0.1f);

	D3DXMATRIX matCamreaRot;
	D3DXMatrixRotationQuaternion(&matCamreaRot, &qCameraRot);
	
	
	//vCameraPos;
	D3DXMATRIX matInitCameraRot;
	D3DXMatrixRotationX(&matInitCameraRot, bCameraBack ? -fCameraAngle : fCameraAngle);

	D3DXVec3TransformNormal(&vCameraDir, &vCameraDir, &matInitCameraRot);
	D3DXVec3TransformNormal(&vCameraDir, &vCameraDir, &matCamreaRot);
	vCameraPos = transform->pos + vCameraDir * fCameraDistance;

	//Up
	vCameraUp = Vector3(0.f, 1.f, 0.f);
	D3DXVec3TransformNormal(&vCameraUp, &vCameraUp, &matCamreaRot);

	//LookAt
	vCameraLookAt = Vector3(0.f, 50.f, 0.f);
	memcpy(&matCamreaRot._41, &transform->pos, sizeof(Vector3));
	
	D3DXVec3TransformCoord(&vCameraLookAt, &vCameraLookAt, &matCamreaRot);
	

	CAMERA.SetCameraPos(vCameraPos, false, 0.f);
	CAMERA.SetCameraLookAt(vCameraLookAt, false, 0.f);
	CAMERA.SetCameraUp(vCameraUp, false, 0.f);
}

void PlayerAirplane::ReceiveCollider(Collider* Other)
{
	fSpeed = 0.f;
}


// ��� �䷱�� cook & torrance