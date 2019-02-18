#pragma once
#include "AirPlane.h"


#define PlayerRollAngle D3DXToRadian(1.0)
#define PlayerPitchAngle D3DXToRadian(1.0)
#define PlayerYawAngle D3DXToRadian(1.0f)

#define PlayerAccel 5.f
#define PlayerUnAccel 10.f

class PlayerAim;

class PlayerAirplane :
	public AirPlane
{
private:
	PlayerAim* aim;

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
public:
	PlayerAirplane();
	virtual ~PlayerAirplane();

	virtual void Init()	override;
	virtual void Update()	override;

	void InputMouse();
	void InputKeyboard();
	void CamreaSetting();

	virtual void ReceiveCollider(Collider* Other) override;
};

