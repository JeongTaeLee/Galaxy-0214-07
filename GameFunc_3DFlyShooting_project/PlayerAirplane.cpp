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
#include "SoundManager.h"
//Object
#include "PlayerMissile.h"
#include "PlayerBullet.h"
#include "PlayerAim.h"
#include "MonsterDirector.h"
#include "MonsterCreater.h"
#include "MonsterAirPlane.h"
#include "EnemyCircle.h"
#include "LockOned.h"
#include "SpeedEffect.h"
#include "LifeBar.h"
#include "PlayerHitEffect.h"
#include "WeaponUI.h"
#include "LoseEnding.h"
#include "VictroyEnding.h"
#include "GameVictroy.h"

PlayerAirplane::PlayerAirplane()
	:lpAim(nullptr),
	lpCreater(nullptr),
	lpLockOnMonster(nullptr),
	lpDirector(nullptr),
	lpLockOned(nullptr),
	lpSpeedEffect(nullptr),
	lpLifeBar(nullptr),
	lpHitEffect(nullptr),

	vDirectorPos(transform->pos + Vector3(0.f, 25.f, 0.f)),

	eGunState(GunState::E_GUNSTATE_MACHINE),

	fCameraDistance(0.f),
	fCameraAngle(0.f),
	bCameraBack(false),

	fAttackDelay(0.2f),
	fAttackAccrue(0.f),

	fLockOnDelay(0.3f),
	fLockOnAccrue(0.f),

	iLife(5),
	fHitAccrue(0.f), fHitDelay(1.f),
	
	bLockOned(false),
	bLeftRight(false),
	bWarningSound(false)
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
	lpCamera = CAMERA.ChangeCamera("PlayerCamera");

	transform->eUpdateType = E_UPDATE_02;
	transform->pos = Vector3(3000.f, 3000.f, 3000.f);
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
#pragma region CreateUI
	lpAim = OBJECT.AddObject<PlayerAim>();
	lpDirector = OBJECT.AddObject<MonsterDirector>();
	lpDirector->SetPos(vDirectorPos);

	lpLockOned = OBJECT.AddObject<LockOned>();
	lpLockOned->SetActive(false);

	lpLifeBar = OBJECT.AddObject<LifeBar>();
	
	lpSpeedEffect = OBJECT.AddObject<SpeedEffect>();
	lpSpeedEffect->SetActive(false);

	lpHitEffect = OBJECT.AddObject<PlayerHitEffect>();
	lpHitEffect->SetActive(false);

	lpWeaponUI = OBJECT.AddObject<WeaponUI>();
	lpWeaponUI->ChangeWeapon(0);
#pragma endregion CreateUI
}

void PlayerAirplane::Release()
{
}

void PlayerAirplane::Update()
{
	lpLockOned->SetActive(bLockOned);
	bLockOned = false;

	if (bWarningSound)
	{
		bWarningSound = false;
		SOUND.Stop("LockOnedWarning");
	}

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

	if (fHitAccrue <= fHitDelay)
		fHitAccrue += Et;
	else
	{
		if (lpHitEffect->GetActive())
			lpHitEffect->SetActive(false);
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


	if (fSpeed <= 100.f)
		lpSpeedEffect->SetActive(false);
	else
	{
		lpSpeedEffect->SetActive(true);

		if (100.f < fSpeed&& fSpeed <= 200.f)
			lpSpeedEffect->SetDelay(0.2f);
		else if (200.f < fSpeed&& fSpeed <= 300.f)
			lpSpeedEffect->SetDelay(0.1f);
		else
			lpSpeedEffect->SetDelay(0.05f);

	}
	
	transform->pos += vAxis[E_AXIS_FORWARD] * (fSpeed * Et);
} 

void PlayerAirplane::MachineGun()
{	
	fAttackAccrue = 0;
	fAttackDelay = 0.1f;

	PlayerBullet* bullet = OBJECT.AddObject<PlayerBullet>();
	Quaternion qRot;
	Vector3 vFirePos;
	Matrix matRot;

	if (bLeftRight)
		vFirePos = Vector3(20.f, 0.f, 30.f);
	else
		vFirePos = Vector3(-20.f, 0.f, 30.f);

	D3DXMatrixRotationQuaternion(&matRot, &transform->qRot);
	memcpy(&matRot._41, &transform->pos, sizeof(Vector3));
	D3DXVec3TransformCoord(&vFirePos, &vFirePos, &matRot);

	if (lpLockOnMonster)
		GetLookAt(qRot, lpLockOnMonster->transform->worldPos, vFirePos);
	else
		qRot = transform->qRot;

	bullet->SetBullet(vFirePos, qRot, 2000.f, 1);

	bLeftRight = !bLeftRight;

	SOUND.DuplicatePlay("PlayerFire");
}

void PlayerAirplane::Missile()
{
	if (!lpLockOnMonster)
		return;
	
	if (lpLockOnMonster->GetCircle()->GetLockOn() == false)
		return;

	fAttackAccrue = 0.f;
	fAttackDelay = 1.f;

	PlayerMissile* missile = OBJECT.AddObject<PlayerMissile>();
	Vector3 vFirePos = Vector3(0.f, 0.f, 0.f);
	Matrix matRot;

	if (bLeftRight)
	{
		vFirePos = Vector3(-30.f, -30.f, 30.f);

		D3DXMatrixRotationQuaternion(&matRot, &transform->qRot);
		memcpy(&matRot._41, &transform->pos, sizeof(Vector3));
		D3DXVec3TransformCoord(&vFirePos, &vFirePos, &matRot);

		missile->SetMissile(lpLockOnMonster, vFirePos, transform->qRot, 10, 1100.f);
	}
	else
	{
		vFirePos = Vector3(30.f, -30.f, 30.f);

		D3DXMatrixRotationQuaternion(&matRot, &transform->qRot);
		memcpy(&matRot._41, &transform->pos, sizeof(Vector3));
		D3DXVec3TransformCoord(&vFirePos, &vFirePos, &matRot);

		missile->SetMissile(lpLockOnMonster, vFirePos, transform->qRot, 10, 1200.f);
	}

	SOUND.DuplicatePlay("MissileFire");

	bLeftRight = !bLeftRight;

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

	if (KEYUP(VK_F4))
	{
		SetDestroy(true);
		OBJECT.AddObject<LoseEnding>();
	}
	if (KEYUP(VK_F3))
	{
		SetDestroy(true);
		OBJECT.AddObject<VictroyEnding>();
	}
	if (KEYUP(VK_F2))
	{
		SetDestroy(true);
		OBJECT.AddObject<GameVictroy>();
	}
	if (KEYUP(VK_F1))
	{
		++iLife;
		lpLifeBar->SetLife(iLife);
	}

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

		lpWeaponUI->ChangeWeapon(0);

		eGunState = E_GUNSTATE_MACHINE;
	}
	if (KEYDOWN('2'))
	{
		lpWeaponUI->ChangeWeapon(1);
		eGunState = E_GUNSTATE_MISSILE;
	}

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
	lpCamera->vPos = transform->pos + vCameraDir * fCameraDistance;

	//Up
	lpCamera->vUp = Vector3(0.f, 1.f, 0.f);
	D3DXVec3TransformNormal(&lpCamera->vUp, &lpCamera->vUp, &matCamreaRot);

	//LookAt
	lpCamera->vLookAt = Vector3(0.f, 11.f, 0.f);
	memcpy(&matCamreaRot._41, &transform->pos, sizeof(Vector3));

	D3DXVec3TransformCoord(&lpCamera->vLookAt, &lpCamera->vLookAt, &matCamreaRot);
}


void PlayerAirplane::ReceiveCollider(Collider* Other)
{
	if ((Other->gameObject->sTag == "Monster" || Other->gameObject->sTag == "Meteor" || Other->gameObject->sTag == "MonsterBullet" || 
		Other->gameObject->sTag == "MonsterMissile") && iLife != 0)
	{

		if (fHitAccrue >= fHitDelay)
		{
			fHitAccrue = 0.f;
			lpHitEffect->SetActive(true);
			--iLife;
			lpLifeBar->SetLife(iLife);
		}

		if (iLife == 0)
		{
			SetDestroy(true);
			OBJECT.AddObject<LoseEnding>();
		}
	}
}

void PlayerAirplane::SetCreater(MonsterCreater* creater)
{
	lpCreater = creater;
}

void PlayerAirplane::SetLockOned()
{
	bLockOned = true; 
	if (!bWarningSound)
	{
		bWarningSound = true;
		SOUND.Play("LockOnedWarning", 1);

	}
}