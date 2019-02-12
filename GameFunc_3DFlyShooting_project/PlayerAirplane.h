#pragma once
#include "AirPlane.h"


class PlayerAirplane :
	public AirPlane
{
private:
	Vector3 vCameraDir;	
	Vector3 vCameraLookAtDir;

	Vector3 vCameraPos;
	Vector3 vCameraLookAt;

	float fCameraDistance;
	float fCameraLookAtDistance;
public:
	PlayerAirplane();
	virtual ~PlayerAirplane();

	virtual void Init()	override;
	virtual void Update()	override;

	void InputMouse();
	void InputKeyboard();
};

