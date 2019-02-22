#pragma once
#include "GameObject.h"

class UIRenderer;

class SpeedEffect :
	public GameObject
{
public:
	UIRenderer* lpUIRenderer;

	std::vector<texture*> vTexs;

	int iCount;

	float fAccrue;
	float fDelay;
public:
	SpeedEffect();
	~SpeedEffect();

	virtual void Init()	override;
	virtual void Update()	override;

	void SetDelay(float _fDelay) { fDelay = _fDelay; }
};

