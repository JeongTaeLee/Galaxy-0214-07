#pragma once
#include "GameObject.h"

class UIRenderer;

class LockOned :
	public GameObject
{
private:
	UIRenderer* lpRenderer;
public:
	LockOned();
	virtual ~LockOned();

	virtual void Init() override;
};

