#pragma once
#include "GameObject.h"

class UIRenderer;

class WeaponUI :
	public GameObject
{
private:
	UIRenderer* lpRenderer;

	texture* lpMachine;
	texture* lpMissileUI;
public:
	WeaponUI();
	virtual ~WeaponUI();

	virtual void Init()	override;

	void ChangeWeapon(int i);

};

