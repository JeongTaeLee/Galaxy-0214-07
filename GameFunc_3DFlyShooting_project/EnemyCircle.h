#pragma once
#include "GameObject.h"

class UIRenderer;
class MonsterAirPlane;
class PlayerAirplane;

class EnemyCircle :
	public GameObject
{
private:
	MonsterAirPlane* lpMonster;
	PlayerAirplane* lpPlayer;

	UIRenderer * lpRenderer;
	texture* lpNoneLockOnTexture;
	texture* lpLockOnTexture;

	bool bLockOn;

	float fRad;
public:
	EnemyCircle();
	virtual ~EnemyCircle();

	virtual void Init()	override;
	virtual void Update() override;
	
	MonsterAirPlane* GetMonster() { return lpMonster; }
	void SetMonster(MonsterAirPlane * monster);
	
	bool GetLockOn() { return bLockOn; }
	void SetLockOn(bool _bLockOn);
	
	float GetCircleRad() { return fRad; }
	
	void SetPlayer(PlayerAirplane* airPlane) { lpPlayer = airPlane; }
public:

};

