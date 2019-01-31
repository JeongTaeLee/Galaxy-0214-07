#pragma once
#include "GameObject.h"

class Renderer;
class ShaderRenderer;

class PlayerAirplane :
	public GameObject
{
private:
	ShaderRenderer * lpRenderer;

	Vector3 vForwardDir;
	
	Vector3 vCameraDir;
	float fCameraDistance;

	float	fSpeed;
	float	fAddSpeed;

	float fCameraAngle;
public:
	PlayerAirplane();
	virtual ~PlayerAirplane();

	virtual void Init()	override;
	virtual void Update()	override;

	void Move();
	void SetCamera();
};

