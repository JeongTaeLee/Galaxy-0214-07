#include "DXUT.h"
#include "MonsterCreater.h"

#include"Func.h"

//Manager
#include "TimeManager.h"
#include "ObjectManager.h"

//Component & GameObject
#include "MonsterAirPlane.h"
#include "MonsterFlight.h"
#include "MonsterA.h"
#include "MonsterB.h"
#include "BossA.h"

#include "PlayerAirplane.h"

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
}

void MonsterCreater::Update()
{
	if (fCreateAccrue >= fCreateDelay && liMonsters.size() < 1)
	{
		fCreateAccrue = 0.f;

		FlightType flight = (FlightType)GetRandomNumber((int)FlightType::E_FlightA, (int)FlightType::E_FLIGHTC);

		Vector3 CreaterPos = veCreatePos[(int)GetRandomNumber(0, (int)veCreatePos.size() - 1)];

		switch (flight)
		{
		case E_FlightA:
			CreaterFlightA(CreaterPos);
			break;
		case E_FLIGHTB:
			CreaterFlightB(CreaterPos);
			break;
		case E_FLIGHTC:
			CreaterFlightC(CreaterPos);
			break;
		default:
			break;
		}
	}
	else
		fCreateAccrue += Et;
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
	flight->SetFlight(lpPlayer, vCreaterPos, Vector3(0.f, 0.f, 1.f), 1000.f, 800.f);

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

void MonsterCreater::CreaterFlightB(const Vector3& vCreaterPos)
{
	MonsterFlight* flight = OBJECT.AddObject<MonsterFlight>();
	flight->SetFlight(lpPlayer, vCreaterPos, Vector3(0.f, 0.f, 1.f), 1000.f, 700.f);

	MonsterA* monster = OBJECT.AddObject<MonsterA>(flight);
	monster->SetMonsterValue(this, lpPlayer, Vector3(0.f, 0.f, 1.f), true);
	flight->AddFlightMonster(monster, Vector3(150.f, 0.f, 0.f));
	flight->CompleteSetting();

	monster = OBJECT.AddObject<MonsterA>(flight);
	monster->SetMonsterValue(this, lpPlayer, Vector3(0.f, 0.f, 1.f), true);
	flight->AddFlightMonster(monster, Vector3(-150.f, 0.f, 0.f));
	flight->CompleteSetting();

	MonsterB* monster2 = OBJECT.AddObject<MonsterB>(flight);
	monster2->SetMonsterValue(this, lpPlayer, Vector3(0.f, 0.f, 1.f), true);
	flight->AddFlightMonster(monster2, Vector3(0.f, 0.f, 150.f));
	flight->CompleteSetting();
}

void MonsterCreater::CreaterFlightC(const Vector3& vCreaterPos)
{
	MonsterFlight* flight = OBJECT.AddObject<MonsterFlight>();
	flight->SetFlight(lpPlayer, vCreaterPos, Vector3(0.f, 0.f, 1.f), 1000.f, 700.f);

	MonsterA* monster = OBJECT.AddObject<MonsterA>(flight);
	monster->SetMonsterValue(this, lpPlayer, Vector3(0.f, 0.f, 1.f), true);
	flight->AddFlightMonster(monster, Vector3(150.f, 0.f, 0.f));
	flight->CompleteSetting();
	monster = OBJECT.AddObject<MonsterA>(flight);
	monster->SetMonsterValue(this, lpPlayer, Vector3(0.f, 0.f, 1.f), true);
	flight->AddFlightMonster(monster, Vector3(-150.f, 0.f, 0.f));
	flight->CompleteSetting();

	monster = OBJECT.AddObject<MonsterA>(flight);
	monster->SetMonsterValue(this, lpPlayer, Vector3(0.f, 0.f, 1.f), true);
	flight->AddFlightMonster(monster, Vector3(0.f, -150.f, -150.f));
	flight->CompleteSetting();

	monster = OBJECT.AddObject<MonsterA>(flight);
	monster->SetMonsterValue(this, lpPlayer, Vector3(0.f, 0.f, 1.f), true);
	flight->AddFlightMonster(monster, Vector3(0.f, 150.f, -150.f));
	flight->CompleteSetting();

	MonsterB* monster2 = OBJECT.AddObject<MonsterB>(flight);
	monster2->SetMonsterValue(this, lpPlayer, Vector3(0.f, 0.f, 1.f), true);
	flight->AddFlightMonster(monster2, Vector3(0.f, 0.f, 150.f));
	flight->CompleteSetting();

}

