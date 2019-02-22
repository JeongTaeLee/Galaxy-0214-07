#pragma once
#include "GameObject.h"

class UIRenderer;

class PlayerHitEffect :
	public GameObject
{
private:
	UIRenderer* lpRenderer;

	float fFlickerDelay;
	float fFlickerAccrue;
public:
	PlayerHitEffect();
	virtual ~PlayerHitEffect();

	virtual void Init()	override;
	virtual void Update()	override;
};

