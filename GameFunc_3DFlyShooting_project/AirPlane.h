#pragma once
#include "GameObject.h"
enum vAxis
{
	E_AXIS_UP,
	E_AXIS_RIGHT,
	E_AXIS_FORWARD,
	E_AXIS,
};

class ShaderRenderer;

class AirPlane :
	public GameObject
{
protected:
	ShaderRenderer* lpRenderer;

	Vector3 vAxis[E_AXIS];

	float fSpeed;
public:
	AirPlane();
	virtual ~AirPlane();

	void YawRotation(float fAngle);
	void RollRotation(float fAngle);
	void PitchRotation(float fAngle);
};

