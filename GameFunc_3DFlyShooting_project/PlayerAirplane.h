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
class MonsterDirector;
class LockOned;
class LifeBar;
class PlayerHitEffect;

class SpeedEffect;

class PlayerAirplane :
	public AirPlane
{
private:
	PlayerAim* lpAim;
	MonsterCreater* lpCreater;
	MonsterAirPlane* lpLockOnMonster;
	MonsterDirector* lpDirector;
	LockOned* lpLockOned;
	SpeedEffect* lpSpeedEffect;
	LifeBar* lpLifeBar;
	PlayerHitEffect* lpHitEffect;

	GunState eGunState;

	Vector3 vCameraPos;
	Vector3 vCameraLookAt;
	Vector3 vCameraUp;
	Quaternion qCameraRot;

	Vector3 vDirectorPos;

	float fCameraDistance;
	float fCameraAngle;
	bool bCameraBack;

	float fAttackDelay;
	float fAttackAccrue;

	float fLockOnDelay;
	float fLockOnAccrue;

	float fHitDelay;
	float fHitAccrue;
	int iLife;

	bool bLockOned;
public:
	PlayerAirplane();
	virtual ~PlayerAirplane();

	virtual void Init()	override;
	virtual void Update()	override;

	void Attack();
	void Move();

	void MachineGun();
	void Missile();

	void LockOn();
	void AutoAim();
	void Director();

	void InputMouse();
	void InputKeyboard();
	void CamreaSetting();

	virtual void ReceiveCollider(Collider* Other) override;
public:
	void SetCreater(MonsterCreater * creater);
	void SetLockOned() { bLockOned = true; }
};

