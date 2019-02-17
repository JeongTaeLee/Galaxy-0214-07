#pragma once
#include "GameObject.h"

class UIRenderer;

class PlayerAim :
	public GameObject
{
private:
	UIRenderer* lpRenderer;
	
public:
	PlayerAim();
	virtual ~PlayerAim();

	virtual void Init()	override;
};

