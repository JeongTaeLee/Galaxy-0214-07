#pragma once
#include "GameObject.h"

class UIRenderer;

class SpeedEffect :
	public GameObject
{
public:
	UIRenderer* lpUIRenderer;

	std::vector<texture*> vTexture;

	int iCount;
	float fAccrue;
public:
	SpeedEffect();
	~SpeedEffect();

	virtual void Init()	override;
	virtual void Update()	override;
};

