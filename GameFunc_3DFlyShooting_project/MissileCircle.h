#pragma once
#include "GameObject.h"

class UIRenderer;
class Missile;

class MissileCircle :
	public GameObject
{
private:
	Missile* lpMissile;

	UIRenderer* lpRenderer;
public:
	MissileCircle();
	virtual ~MissileCircle();

	virtual void Init()	override;
	virtual void Update()	override;

	void SetMissile(Missile* _lpMissile) { lpMissile = _lpMissile; }
};

