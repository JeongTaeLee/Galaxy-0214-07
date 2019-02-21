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
	std::vector<Vector3> veCreatePos;

	float fCreateAccrue;
	float fCreateDelay;
public:
	MonsterCreater();
	virtual ~MonsterCreater();

	virtual void Init()	override;
	virtual void Update()	override;

	void CreateMonsterA(const Vector3& createPos);
	void CreateMonsterB(const Vector3& createPos);
public:
	void DestroyListMonster(MonsterAirPlane* airPlane);
	void CreateMonster();

public:
	void SetMonsterDirector(MonsterDirector* director) {lpDirector = director;}
	void SetPlayer(PlayerAirplane* airPlane) { lpPlayer = airPlane; }
	
	std::list<MonsterAirPlane*>& GetMonsterList() { return liMonsters; }
};

