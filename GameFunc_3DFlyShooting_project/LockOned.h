#pragma once
#include "GameObject.h"

class UIRenderer;

class LockOned :
	public GameObject
{
private:
	UIRenderer* lpRenderer;

	float fFlashTime;
	float fFlashAccrue;
public:
	LockOned();
	virtual ~LockOned();

	virtual void Init() override;
	virtual void Update()	override;
};

