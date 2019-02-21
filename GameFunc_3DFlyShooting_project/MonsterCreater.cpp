#include "DXUT.h"
#include "MonsterCreater.h"

#include"Func.h"

//Manager
#include "TimeManager.h"
#include "ObjectManager.h"

//Component & GameObject
#include "MonsterA.h"
#include "MonsterDirector.h"
#include "MonsterAirPlane.h"
#include "MonsterFlight.h"
#include "EnemyCircle.h"
#include "PlayerAirplane.h"
#include "BossA.h"
MonsterCreater::MonsterCreater()
	:fCreateAccrue(0.f), fCreateDelay(5.f)
{
}


MonsterCreater::~MonsterCreater()
{
}

void MonsterCreater::Init()
{
	lpPlayer = (PlayerAirplane*)OBJECT.FindWithTag("PlayerAirPlane");

	veCreatePos.push_back(Vector3(0.f, 0.f, 7000.f));
	veCreatePos.push_back(Vector3(7000.f, 0.f, 7000.f));
	veCreatePos.push_back(Vector3(7000.f, 0.f, 0.f));
	veCreatePos.push_back(Vector3(7000.f, 0.f, -7000));

	veCreatePos.push_back(Vector3(0.f, 0.f, -7000.f));
	veCreatePos.push_back(Vector3(-7000.f, 0.f, -7000.f));
	veCreatePos.push_back(Vector3(-7000.f, 0.f, 0.f));
	veCreatePos.push_back(Vector3(-7000.f, 0.f, 7000.f));

	CreaterFlightA(Vector3(0.f, 0.f, 0.f));
}

void MonsterCreater::Update()
{
}

void MonsterCreater::AddListMonster(MonsterAirPlane* airPlane)
{
	liMonsters.push_back(airPlane);
}

void MonsterCreater::DestroyListMonster(MonsterAirPlane* airPlane)
{
	liMonsters.remove(airPlane);
}

void MonsterCreater::CreaterFlightA(const Vector3& vCreaterPos)
{
	MonsterFlight* flight = OBJECT.AddObject<MonsterFlight>();
	flight->SetFlight(lpPlayer, vCreaterPos, Vector3(0.f, 0.f, 1.f), 1000.f, 700.f);

	MonsterA* monster = OBJECT.AddObject<MonsterA>(flight);
	monster->SetMonsterValue(this, lpPlayer, Vector3(0.f, 1.f, 0.f), true);
	flight->AddFlightMonster(monster, Vector3(150.f, 0.f, 0.f));
	flight->CompleteSetting();

	monster = OBJECT.AddObject<MonsterA>(flight);
	monster->SetMonsterValue(this, lpPlayer, Vector3(0.f, 1.f, 0.f), true);
	flight->AddFlightMonster(monster, Vector3(-150.f, 0.f, 0.f));
	flight->CompleteSetting();

	monster = OBJECT.AddObject<MonsterA>(flight);
	monster->SetMonsterValue(this, lpPlayer, Vector3(0.f, 1.f, 0.f), true);
	flight->AddFlightMonster(monster, Vector3(0.f, 0.f, 150.f));
	flight->CompleteSetting();
}

