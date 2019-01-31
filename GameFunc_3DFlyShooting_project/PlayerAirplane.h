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
	float	fSpeed;
	float	fAddSpeed;
public:
	PlayerAirplane();
	virtual ~PlayerAirplane();

	virtual void Init()	override;
	virtual void Update()	override;

	void Move();
};

