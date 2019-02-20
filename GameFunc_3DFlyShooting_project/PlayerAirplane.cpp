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
#include "PlayerAim.h"
#include "MonsterDirector.h"
#include "MonsterCreater.h"
#include "MonsterAirPlane.h"
#include "EnemyCircle.h"


PlayerAirplane::PlayerAirplane()
	:vCameraPos(0.f, 0.f, 0.f), vCameraLookAt(0.f, 0.f, 0.f),
	fCameraDistance(0.f), fCameraLookAtDistance(0.f),
	bCameraBack(false), fMaxSpeed(0.f),
	fAttackDelay(0.2f), fAttackAccrue(0.5f),
	fLockOnDelay(0.5f), fLockOnAccrue(0.f),
	eGunState(E_GUNSTATE_MACHINE), lpLockOnMonster(nullptr)
{
	sTag = "PlayerAirPlane";

	D3DXQuaternionIdentity(&qCameraRot);
}


PlayerAirplane::~PlayerAirplane()
{
}

void PlayerAirplane::Init()
{
	transform->eUpdateType = E_UPDATE_02;

	aim = OBJECT.AddObject<PlayerAim>();

	transform->pos = Vector3(0.f, 0.f, -150.f);
	transform->scale = Vector3(0.5f, 0.5f, 0.5f);

#pragma region RendererSetting
	lpRenderer = AC(ShaderRenderer);
	lpRenderer->LoadMesh(IMAGE.LoadObjFile("PlayerAirPlane", "./rs/obj/Player/PlayerAirPlane.obj"));
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
	fCameraAngle = D3DXToRadian(7.f);
	fCameraDistance = 100.f;

	CamreaSetting();
#pragma endregion CameraSetting 

#pragma region Collider
	AC(SphereCollider)->InitSphere(Vector3(20.f, 0.f, -10.f), 8);
	AC(SphereCollider)->InitSphere(Vector3(-20.f, 0.f, -10.f), 8);
	AC(SphereCollider)->InitSphere(Vector3(0.f, 0.f, 5.f), 8);
	AC(SphereCollider)->InitSphere(Vector3(0.f, 0.f, -13.f), 8);
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

	Attack();

	CamreaSetting();
}

void PlayerAirplane::Attack()
{
	if (eGunState == E_GUNSTATE_MISSILE)
	{
		if (lpLockOnMonster)
		{
			if (lpLockOnMonster->GetDestroy())
				lpLockOnMonster = nullptr;
		}
	
		LockOn();
	}

	fAttackAccrue += Et;
	
	if (fAttackAccrue <= fAttackDelay)
		return;

	if (KEYPRESS(VK_SPACE) || KEYPRESS(VK_LBUTTON))
	{
		fAttackAccrue = 0.f;

		switch (eGunState)
		{
		case E_GUNSTATE_MACHINE:
			MachineGun();
			break;

		case E_GUNSTATE_MISSILE:
			Missile();
			break;
		}
	}
}

void PlayerAirplane::MachineGun()
{
	Vector3 LeftFirePos = Vector3(-20.f, 0.f, 30.f);
	Vector3 RightFirePos = Vector3(20.f, 0.f, 30.f);

	D3DXMATRIX matRot;
	D3DXMatrixRotationQuaternion(&matRot, &transform->qRot);
	memcpy(&matRot._41, transform->pos, sizeof(Vector3));

	D3DXVec3TransformCoord(&LeftFirePos, &LeftFirePos, &matRot);
	D3DXVec3TransformCoord(&RightFirePos, &RightFirePos, &matRot);

	OBJECT.AddObject<PlayerBullet>()
		->SetBullet(LeftFirePos, transform->qRot, 1500.f, 5.f);
	OBJECT.AddObject<PlayerBullet>()
		->SetBullet(RightFirePos, transform->qRot, 1500.f, 5.f);
}

void PlayerAirplane::Missile()
{
	
}

void PlayerAirplane::LockOn()
{
	std::list<MonsterAirPlane*> & refMonsters = lpCreater->GetMonsterList();

	MonsterAirPlane* lpNowLockOnMonster = nullptr;
	Vector2 vAimPos = Vector2((float)WINSIZEX / 2.f, (float)WINSIZEY / 2.f);

	float fMonsterShortDistance = 0.f;
	int iLoopCount = 0;

	for (auto Iter : refMonsters)
	{
		Vector2 vCirclePos = Iter->GetCircle()->transform->pos;
		
		if (Iter->GetCircle()->GetCircleRad() > GetLengthVector2(vCirclePos, vAimPos))
		{
			float fMonsterNowDistance = GetLengthVector3(Iter->transform->worldPos, transform->worldPos);

			if (iLoopCount == 0)
			{
				lpNowLockOnMonster = Iter;
				fMonsterShortDistance = fMonsterNowDistance;
			}
			else if( fMonsterShortDistance > fMonsterNowDistance)
			{
				lpNowLockOnMonster = Iter;
				fMonsterShortDistance = fMonsterNowDistance;
			}

			iLoopCount++;
		}
	}

	if (lpLockOnMonster)
	{
		if (lpNowLockOnMonster == lpLockOnMonster)
		{
			fLockOnAccrue += Et;

			if (fLockOnAccrue >= fLockOnDelay)
				lpLockOnMonster->GetCircle()->SetLockOn(true);
		}
		else
		{
			if (lpLockOnMonster->GetCircle()->GetLockOn())
			{
				lpLockOnMonster->GetCircle()->SetLockOn(false);
				lpLockOnMonster = nullptr;
			}
			
			if (lpNowLockOnMonster)
				lpLockOnMonster = lpNowLockOnMonster;

			fLockOnAccrue = Et;
		}
	}
	else
	{
		lpLockOnMonster = lpNowLockOnMonster;
		fLockOnAccrue = Et;
	}
}


void PlayerAirplane::InputMouse()
{
	Vector2 vGap(INPUT.GetMouseGap());

	float XGap = D3DXToRadian(vGap.x) * 0.1f;
	float YGap = (D3DXToRadian(vGap.y) * 0.1f);

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
		if (fSpeed < fMaxSpeed)
			fSpeed += PlayerAccel;
	}

	if (KEYPRESS('S'))
	{
		if (fSpeed > 0.f)
			fSpeed -= PlayerUnAccel;
	}

	if (KEYPRESS(VK_LSHIFT))
		fMaxSpeed = 800.f;
	else
		fMaxSpeed = 500.f;

	if (KEYDOWN('1'))
	{
		if (lpLockOnMonster)
		{
			if (lpLockOnMonster->GetCircle()->GetLockOn())
			{
				lpLockOnMonster->GetCircle()->SetLockOn(false);
				lpLockOnMonster = nullptr;
			}
		}

		eGunState = E_GUNSTATE_MACHINE;
	}
	if (KEYDOWN('2'))
		eGunState = E_GUNSTATE_MISSILE;

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
	vCameraLookAt = Vector3(0.f, 11.f, 0.f);
	memcpy(&matCamreaRot._41, &transform->pos, sizeof(Vector3));

	D3DXVec3TransformCoord(&vCameraLookAt, &vCameraLookAt, &matCamreaRot);

	CAMERA.SetCameraPos(vCameraPos, false, 0.f);
	CAMERA.SetCameraLookAt(vCameraLookAt, false, 0.f);
	CAMERA.SetCameraUp(vCameraUp, false, 0.f);
}

void PlayerAirplane::ReceiveCollider(Collider* Other)
{
	if(Other->gameObject->sTag == "Monster" || Other->gameObject->sTag == "Meteor")
		fSpeed = 0.f;
}

void PlayerAirplane::SetCreater(MonsterCreater* creater)
{
	lpCreater = creater;
}
