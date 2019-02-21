#pragma once
#include "AirPlane.h"

#define PlayerRollAngle D3DXToRadian(3.0f)
#define PlayerPitchAngle D3DXToRadian(1.7f)
#define PlayerYawAngle D3DXToRadian(1.3f)

#define PlayerAccel 5.f
#define PlayerUnAccel 10.f

enum GunState
{
	E_GUNSTATE_MISSILE,
	E_GUNSTATE_MACHINE,
};

class PlayerAim;
class MonsterCreater;
class MonsterAirPlane;

class PlayerAirplane :
	public AirPlane
{
private:
	PlayerAim* aim;
	MonsterCreater* lpCreater;
	MonsterAirPlane* lpLockOnMonster;

	Vector3 vCameraPos;
	Vector3 vCameraLookAt;
	Vector3 vCameraUp;
	Quaternion qCameraRot;

	float fCameraDistance;
	float fCameraLookAtDistance;
	float fCameraAngle;
	bool bCameraBack;

	float fMaxSpeed;

	float fAttackDelay;
	float fAttackAccrue;

	float fLockOnDelay;
	float fLockOnAccrue;

	int iLife;

	GunState eGunState;
public:
	PlayerAirplane();
	virtual ~PlayerAirplane();

	virtual void Init()	override;
	virtual void Update()	override;

	void Attack();
	
	void MachineGun();
	void Missile();
	void LockOn();
	void AutoAim();

	void InputMouse();
	void InputKeyboard();
	void CamreaSetting();

	virtual void ReceiveCollider(Collider* Other) override;

public:
	void SetCreater(MonsterCreater * creater);
};

