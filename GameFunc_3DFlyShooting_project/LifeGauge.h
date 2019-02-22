#pragma once
#include "GameObject.h"

class UIRenderer;

class LifeGauge :
	public GameObject
{
private:
	UIRenderer* lpRenderer;
public:
	LifeGauge();
	virtual ~LifeGauge();
	
	virtual void Init()	override;
};

