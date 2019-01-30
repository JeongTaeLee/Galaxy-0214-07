#pragma once
#include "GameObject.h"

class Renderer;
class ShaderRenderer;

class PlayerAirplane :
	public GameObject
{
private:
	ShaderRenderer * lpRenderer;
public:
	PlayerAirplane();
	virtual ~PlayerAirplane();

	virtual void Init()	override;
};

