#pragma once
#include "AirPlane.h"

#define PlayerRollAngle D3DXToRadian(2.0)
#define PlayerPitchAngle D3DXToRadian(1.0)
#define PlayerYawAngle D3DXToRadian(1.0f)

#define PlayerAccel 5.f
#define PlayerUnAccel 10.f

enum GunState
{
	E_GUNSTATE_MISSILE,
	E_GUNSTATE_MACHINE,
};

class PlayerAim;
class MonsterCreater;

class PlayerAirplane :
	public AirPlane
{
private:
	PlayerAim* aim;
	MonsterCreater* lpCreater;

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

	void InputMouse();
	void InputKeyboard();
	void CamreaSetting();

	virtual void ReceiveCollider(Collider* Other) override;

public:
	void SetCreater(MonsterCreater * creater);
};

