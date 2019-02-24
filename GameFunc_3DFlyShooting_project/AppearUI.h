#pragma once
#include "GameObject.h"

class UIRenderer;

class AppearUI :
	public GameObject
{
private:
	UIRenderer* lpRenderer;
	
public:
	AppearUI();
	virtual ~AppearUI();
	
	virtual void Update()	override;
	void SetAppearUI(texture* tex);
};

