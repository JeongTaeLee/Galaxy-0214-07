#pragma once
#include "GameObject.h"

class UIRenderer;

class InfoScreen :
	public GameObject
{
private:
	UIRenderer* lpRenderer;
public:
	InfoScreen();
	virtual ~InfoScreen();

	virtual void Init()	override;
	virtual void Update()	override;


	void SetInfoScreen(texture* lpTex);
};

