#pragma once
#include "GameObject.h"

enum MonsterType
{
	E_MonsterA,
	E_MonsterB,
};

class MonsterDirector;
class MonsterAirPlane; 
class PlayerAirplane;

class MonsterCreater :
	public GameObject
{
private:
	PlayerAirplane* lpPlayer;
	MonsterAirPlane* lpLockOnMonster;
	MonsterDirector* lpDirector;

	std::list<MonsterAirPlane*> liMonsters;

	float fCreateAccrue;
	float fCreateDelay;
public:
	MonsterCreater();
	virtual ~MonsterCreater();

	virtual void Update()	override;

	void CreateMonsterA();
	void CreateMonsterB();

	void LockOnCheck();
public:
	void DestroyListMonster(MonsterAirPlane* airPlane);
	void SortingMonsterCircle();
	void CreateMonster();
public:
	void SetMonsterDirector(MonsterDirector* director) {lpDirector = director;}
	void SetPlayer(PlayerAirplane* airPlane) { lpPlayer = airPlane; }
};

