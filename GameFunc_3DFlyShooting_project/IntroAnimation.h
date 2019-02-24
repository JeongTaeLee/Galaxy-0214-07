#pragma once
#include "GameObject.h"

class UIRenderer;

class IntroAnimation :
	public GameObject
{
private:
	UIRenderer* lpRenderer;

	std::vector<texture*> veIntro;

	float fAccrue;
	float fDelay;
	int iCount;

	bool bEnd;
public:
	IntroAnimation();
	virtual ~IntroAnimation();

	virtual void Init()	override;
	virtual void Update() override;
};

