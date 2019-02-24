#pragma once
#include "GameObject.h"

enum FlightType
{
	E_FlightA,
	E_FLIGHTB,
	E_FLIGHTC,
};

class MonsterAirPlane; 
class PlayerAirplane;

class MonsterCreater :
	public GameObject
{
private:
	PlayerAirplane* lpPlayer;

	std::list<MonsterAirPlane*> liMonsters;
	std::vector<Vector3> veCreatePos;

	float fCreateAccrue;
	float fCreateDelay;
	
	bool bBossWar;
public:
	MonsterCreater();
	virtual ~MonsterCreater();

	virtual void Init()	override;
	virtual void Update()	override;
public:
	void AddListMonster(MonsterAirPlane * airPlane);
	void DestroyListMonster(MonsterAirPlane* airPlane);

	void CreaterFlightA(const Vector3 & vCreaterPos);
	void CreaterFlightB(const Vector3& vCreaterPos);
	void CreaterFlightC(const Vector3& vCreaterPos);

	void CreaterMiddleBossA();
	void CreaterBossA();

	void AllDestroyMonster();
public:
	void SetPlayer(PlayerAirplane* airPlane) { lpPlayer = airPlane; }

	bool GetBossWar() { return bBossWar;}
	void EndBossWar();
	std::list<MonsterAirPlane*>& GetMonsterList() { return liMonsters; }
};

