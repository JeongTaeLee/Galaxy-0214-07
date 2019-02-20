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

	float fLockOnAccrue;
	bool bLockOn;

	float fRad;

public:
	EnemyCircle();
	virtual ~EnemyCircle();

	virtual void Init()	override;
	virtual void Update() override;
	
	MonsterAirPlane* GetMonster() { return lpMonster; }
	void SetMonster(MonsterAirPlane * monster);
	
	void SetPlayer(PlayerAirplane* airPlane) { lpPlayer = airPlane; }
	void SetRendererLayer(int i);

	void ResetLockOn();
	void LockOnProcess();
	bool GetLockOn() { return bLockOn; }
	float GetLockOnAccrue() { return fLockOnAccrue; }
	float GetCircleRad() { return fRad; }
public:
};

