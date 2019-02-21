#pragma once
#include "GameObject.h"
enum AirPlaneAxis
{
	E_AXIS_UP,
	E_AXIS_RIGHT,
	E_AXIS_FORWARD,
	E_AXIS,
};

class ShaderRenderer;
class MonsterDirector;

class AirPlane :
	public GameObject
{
protected:
	ShaderRenderer* lpRenderer;

	Vector3 vAxis[E_AXIS];

	float fMaxSpeed;
	float fSpeed;

	float fYawAngle;
	float fPitchAngle;
	float fRollAngle;
public:
	AirPlane();
	virtual ~AirPlane();

	void YawRotation(float fAngle);
	void RollRotation(float fAngle);
	void PitchRotation(float fAngle);

	void SetAirPlaneMatrix();
	void SetAxis();

	const Vector3& GetAxis(AirPlaneAxis axis) {	return vAxis[axis]; }
};

