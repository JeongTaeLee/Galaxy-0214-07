#pragma once
#include "GameObject.h"

class Renderer;

class SkyBox :
	public GameObject
{
private:
	Renderer * lpRenderer;
public:
	SkyBox();
	~SkyBox();

	virtual void Init()	override;
	virtual void Update()	override;
};

