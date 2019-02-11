#pragma once
#include "GameObject.h"

enum vAxis
{
	E_AXIS_UP,
	E_AXIS_RIGHT,
	E_AXIS_FORWARD,
	E_AXIS,
};

class Renderer;
class ShaderRenderer;

class PlayerAirplane :
	public GameObject
{
private:
	ShaderRenderer * lpRenderer;

	Vector3 vAxis[E_AXIS];

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

