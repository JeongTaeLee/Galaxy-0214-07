#pragma once
#include "GameObject.h"

class UIRenderer;

class Button :
	public GameObject
{
private:
	UIRenderer* lpRenderer;

	std::function<void()> func;
	RECT re;
	bool bCenter;
public:
	Button();
	virtual ~Button();

	virtual void Init()	override;
	virtual void Update()	override;

	void SetTexture(texture* lpTex, bool Center = false);
	void SetFunc(const std::function<void()>& _func) { func = _func; };
	void AutoRect();
};

