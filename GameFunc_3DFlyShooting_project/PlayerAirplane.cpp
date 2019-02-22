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
#include "PlayerMissile.h"
#include "PlayerBullet.h"
#include "PlayerAim.h"
#include "MonsterDirector.h"
#include "MonsterCreater.h"
#include "MonsterAirPlane.h"
#include "EnemyCircle.h"
#include "LockOned.h"
#include "LifeGuid.h"
#include "SpeedEffect.h"

PlayerAirplane::PlayerAirplane()
	:lpAim(nullptr),
	lpCreater(nullptr),
	lpLockOnMonster(nullptr),
	lpDirector(nullptr),

	vDirectorPos(transform->pos + Vector3(0.f, 25.f, 0.f)),

	eGunState(GunState::E_GUNSTATE_MACHINE),

	vCameraPos(0.f, 0.f, 0.f),
	vCameraLookAt(0.f, 0.f, 1.f),
	vCameraUp(0.f, 1.f, 0.f),

	fCameraDistance(0.f),
	fCameraAngle(0.f),
	bCameraBack(false),

	fAttackDelay(0.2f),
	fAttackAccrue(0.f),

	fLockOnDelay(0.3f),
	fLockOnAccrue(0.f),

	iLife(5),
	
	bLockOned(false)
{
	sTag = "PlayerAirPlane";

	D3DXQuaternionIdentity(&qCameraRot);

	fMaxSpeed = 700.f;
}


PlayerAirplane::~PlayerAirplane()
{
}

void PlayerAirplane::Init()
{
	transform->eUpdateType = E_UPDATE_02;
	transform->pos = Vector3(0.f, 0.f, -3000.f);
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

	lpAim = OBJECT.AddObject<PlayerAim>();
	lpDirector = OBJECT.AddObject<MonsterDirector>();
	lpDirector->SetPos(vDirectorPos);

	lpLockOned = OBJECT.AddObject<LockOned>();
	lpLockOned->SetActive(false);

	lpLifeGuid = OBJECT.AddObject<LifeGuid>();
	
	lpSpeedEffect = OBJECT.AddObject<SpeedEffect>();
	lpSpeedEffect->SetActive(false);
}

void PlayerAirplane::Update()
{
	lpLockOned->SetActive(bLockOned);
	bLockOned = false;

	InputMouse();
	InputKeyboard();

	Move();
	Attack();
	Director();
	
	AirPlane::SetAirPlaneMatrix();

	CamreaSetting();
}

void PlayerAirplane::Attack()
{
	if (lpLockOnMonster) 
	{
		if (lpLockOnMonster->GetDestroy())
			lpLockOnMonster = nullptr;
	}

	switch (eGunState)
	{
	case E_GUNSTATE_MISSILE:
		LockOn();
		break;
	case E_GUNSTATE_MACHINE:
		AutoAim();
		break;
	default:
		break;
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

void PlayerAirplane::Move()
{
	if (fSpeed > fMaxSpeed)
		fSpeed = fMaxSpeed;
	if (0 > fSpeed)
		fSpeed = 0.f;

	if (fSpeed < 100)
		lpSpeedEffect->SetActive(false);
	else
		lpSpeedEffect->SetActive(true);

	transform->pos += vAxis[E_AXIS_FORWARD] * (fSpeed * DXUTGetElapsedTime());
} 

void PlayerAirplane::MachineGun()
{	
	Vector3 LeftFirePos = Vector3(-20.f, 0.f, 30.f);
	Vector3 RightFirePos = Vector3(20.f, 0.f, 30.f);

	Matrix matRot;
	D3DXMatrixRotationQuaternion(&matRot, &transform->qRot);
	memcpy(&matRot._41, transform->pos, sizeof(Vector3));

	D3DXVec3TransformCoord(&LeftFirePos, &LeftFirePos, &matRot);
	D3DXVec3TransformCoord(&RightFirePos, &RightFirePos, &matRot);
	
	Quaternion quater01;
	Quaternion quater02;

	if (lpLockOnMonster)
	{
		GetLookAt(quater01, lpLockOnMonster->transform->worldPos, LeftFirePos);
		GetLookAt(quater02, lpLockOnMonster->transform->worldPos, RightFirePos);
	}
	else
	{
		quater01 = transform->qRot;
		quater02 = transform->qRot;
	}
		
	OBJECT.AddObject<PlayerBullet>()
		->SetBullet(LeftFirePos, quater01, 2000.f, 5.f);
	OBJECT.AddObject<PlayerBullet>()
		->SetBullet(RightFirePos, quater02, 2000.f, 5.f);
	
}

void PlayerAirplane::Missile()
{
	if (!lpLockOnMonster)
		return;
	
	if (lpLockOnMonster->GetCircle()->GetLockOn() == false)
		return;

	Vector3 LeftFirePos = Vector3(-20.f, 0.f, 30.f);
	Vector3 RightFirePos = Vector3(20.f, 0.f, 30.f);

	Matrix matRot;
	D3DXMatrixRotationQuaternion(&matRot, &transform->qRot);

	memcpy(&matRot._41, transform->pos, sizeof(Vector3));

	D3DXVec3TransformCoord(&LeftFirePos, &LeftFirePos, &matRot);
	D3DXVec3TransformCoord(&RightFirePos, &RightFirePos, &matRot);

	OBJECT.AddObject<PlayerMissile>()
		->SetMissile(lpLockOnMonster, RightFirePos, vAxis[E_AXIS_FORWARD], 800.f, 20.f, 10.f);
	OBJECT.AddObject<PlayerMissile>()
		->SetMissile(lpLockOnMonster, LeftFirePos, vAxis[E_AXIS_FORWARD], 800.f, 20.f, 10.f);

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
		if (Iter->GetDestroy())
			continue;

		if (Iter->GetCircle()->GetDestroy())
			continue;


		Vector2 vCirclePos = Iter->GetCircle()->transform->pos;
		
		if (Iter->GetCircle()->GetCircleRad() > GetLengthVector2(vCirclePos, vAimPos))
		{
			float fMonsterNowDistance = Iter->GetPlayerDistance();

			if (iLoopCount == 0)
			{
				lpNowLockOnMonster = Iter;
				fMonsterShortDistance = fMonsterNowDistance;
			}
			else if (fMonsterShortDistance > fMonsterNowDistance)
			{
				lpNowLockOnMonster = Iter;
				fMonsterShortDistance = fMonsterNowDistance;
			}

			iLoopCount++;
		}
		else
			Iter->GetCircle()->SetLockOn(false);
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
			{
				lpLockOnMonster = lpNowLockOnMonster;
				lpNowLockOnMonster = nullptr;
			}


			fLockOnAccrue = Et;
		}
	}
	else
	{
		lpLockOnMonster = lpNowLockOnMonster;
		fLockOnAccrue = Et;
	}
}

void PlayerAirplane::AutoAim()
{
	std::list<MonsterAirPlane*>& refMonsters = lpCreater->GetMonsterList();

	MonsterAirPlane* lpNowLockOnMonster = nullptr;
	Vector2 vAimPos = Vector2((float)WINSIZEX / 2.f, (float)WINSIZEY / 2.f);

	float fMonsterShortDistance = 0.f;
	int iLoopCount = 0;

	for (auto Iter : refMonsters)
	{
		if (Iter->GetDestroy())
			continue;

		Vector2 vCirclePos = Iter->GetCircle()->transform->pos;

		if (Iter->GetCircle()->GetCircleRad() > GetLengthVector2(vCirclePos, vAimPos))
		{
			float fMonsterNowDistance = GetLengthVector3(Iter->transform->worldPos, transform->worldPos);

			if (iLoopCount == 0)
			{
				lpNowLockOnMonster = Iter;
				fMonsterShortDistance = fMonsterNowDistance;
			}
			else if (fMonsterShortDistance > fMonsterNowDistance)
			{
				lpNowLockOnMonster = Iter;
				fMonsterShortDistance = fMonsterNowDistance;
			}

			iLoopCount++;
		}
	}

	if (lpLockOnMonster)
	{
		if (lpNowLockOnMonster)
		{
			if (lpLockOnMonster != lpNowLockOnMonster)
			{
				if(lpLockOnMonster->GetCircle()->GetLockOn())
					lpLockOnMonster->GetCircle()->SetLockOn(false);

				lpNowLockOnMonster->GetCircle()->SetLockOn(true);
				lpLockOnMonster = lpNowLockOnMonster;
			}
		}
		else
		{
			if (lpLockOnMonster->GetCircle()->GetLockOn())
				lpLockOnMonster->GetCircle()->SetLockOn(false);
			
			lpLockOnMonster = nullptr;
		}
	}
	else
	{
		if (lpNowLockOnMonster)
		{
			lpNowLockOnMonster->GetCircle()->SetLockOn(true);
			lpLockOnMonster = lpNowLockOnMonster;
			lpNowLockOnMonster = nullptr;
		}
	}



}

void PlayerAirplane::Director()
{
	std::list<MonsterAirPlane*>& refMonsters = lpCreater->GetMonsterList();
	
	MonsterAirPlane* lpShortMonster = nullptr;
	float fShortLength = 0.f;

	int iLoopCount = 0;
	for (auto Iter : refMonsters)
	{
		if (Iter->GetDestroy())
			continue;

		if (iLoopCount == 0)
		{
			lpShortMonster = Iter;
			fShortLength = Iter->GetPlayerDistance();
		}
		else if (fShortLength > Iter->GetPlayerDistance())
		{
			lpShortMonster = Iter;
			fShortLength = Iter->GetPlayerDistance();
		}

		++iLoopCount;
	}

	if(lpShortMonster)
		lpDirector->SetDirection(lpShortMonster);

	D3DXMATRIX matRot;
	D3DXMatrixRotationQuaternion(&matRot, &transform->qRot);
	memcpy(&matRot._41, &transform->pos, sizeof(Vector3));

	Vector3 vPos = Vector3(0.f, 0.f, 0.f);
	D3DXVec3TransformCoord(&vPos, &vDirectorPos, &matRot);
	lpDirector->SetPos(vPos);
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
		fSpeed += PlayerAccel;

	if (KEYPRESS('S'))
		fSpeed -= PlayerUnAccel;

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
	if (Other->gameObject->sTag == "Monster" || Other->gameObject->sTag == "Meteor")
	{
		if (Other->gameObject->sTag == "Monster")
			static_cast<MonsterAirPlane*>(Other->gameObject)->SetMonsterDie();

		if (Other->gameObject->sTag == "Meteor")
			Other->gameObject->SetDestroy(true);

		if (Other->gameObject->sTag == "MonsterBullet")
			iLife -= 1;
	}
}

void PlayerAirplane::SetCreater(MonsterCreater* creater)
{
	lpCreater = creater;
}
