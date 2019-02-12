#pragma once
#include "AirPlane.h"


#define PlayerRollAngle D3DXToRadian(1.5)
#define PlayerPitchAngle D3DXToRadian(1.5)
#define PlayerYawAngle D3DXToRadian(1.0f)

#define PlayerAccel 5.f
#define PlayerUnAccel 10.f

class PlayerAirplane :
	public AirPlane
{
private:
	Vector3 vCameraPos;
	Vector3 vCameraLookAt;
	Vector3 vCameraUp;
	Quaternion qCameraRot;

	float fCameraDistance;
	float fCameraLookAtDistance;

	float fCameraAngle;

	float fMaxSpeed;

	bool bCameraBack;
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

