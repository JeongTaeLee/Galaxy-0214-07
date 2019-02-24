#include "DXUT.h"
#include "MonsterCreater.h"

#include"Func.h"

//Manager
#include "TimeManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
//Component & GameObject
#include "MonsterAirPlane.h"
#include "MonsterFlight.h"
#include "MonsterA.h"
#include "MonsterA2.h"
#include "MonsterB.h"
#include "MonsterB2.h"
#include "BossA.h"
#include "BossB.h"
#include "MiddleBossA.h"
#include "MiddleBossB.h"


#include "PlayerAirplane.h"

MonsterCreater::MonsterCreater()
	:fCreateAccrue(0.f), fCreateDelay(5.f),
	bBossWar(false)
{
	sTag = "MonsterCreater";
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

	//CreaterBossA();
}

void MonsterCreater::Update()
{
	if (lpPlayer)
	{
		if (lpPlayer->GetDestroy())
		{
			lpPlayer = nullptr;
			return;
		}
	}

	if (!lpPlayer)
		return;

#if true
	if (fCreateAccrue >= fCreateDelay && liMonsters.size() < 1 && !bBossWar)
	{
		fCreateAccrue = 0.f;

		FlightType flight = (FlightType)GetRandomNumber((int)FlightType::E_FlightA, (int)FlightType::E_FLIGHTC);
		DEBUG_LOG(flight);

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
#endif
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

	if (SCENE.sNowScene == "Stage01")
	{
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
		flight->AddFlightMonster(monster, Vector3(0.f, 0.f, 150.f));
		flight->CompleteSetting();
	}
	else if (SCENE.sNowScene == "Stage02")
	{
		MonsterA2* monster = OBJECT.AddObject<MonsterA2>(flight);
		monster->SetMonsterValue(this, lpPlayer, Vector3(0.f, 0.f, 1.f), true);
		flight->AddFlightMonster(monster, Vector3(150.f, 0.f, 0.f));
		flight->CompleteSetting();

		monster = OBJECT.AddObject<MonsterA2>(flight);
		monster->SetMonsterValue(this, lpPlayer, Vector3(0.f, 0.f, 1.f), true);
		flight->AddFlightMonster(monster, Vector3(-150.f, 0.f, 0.f));
		flight->CompleteSetting();

		monster = OBJECT.AddObject<MonsterA2>(flight);
		monster->SetMonsterValue(this, lpPlayer, Vector3(0.f, 0.f, 1.f), true);
		flight->AddFlightMonster(monster, Vector3(0.f, 0.f, 150.f));
	}
}

void MonsterCreater::CreaterFlightB(const Vector3& vCreaterPos)
{
	MonsterFlight* flight = OBJECT.AddObject<MonsterFlight>();
	flight->SetFlight(lpPlayer, vCreaterPos, Vector3(0.f, 0.f, 1.f), 1000.f, 700.f);

	if (SCENE.sNowScene == "Stage01")
	{
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
	else if (SCENE.sNowScene == "Stage02")
	{
		MonsterA2* monster = OBJECT.AddObject<MonsterA2>(flight);
		monster->SetMonsterValue(this, lpPlayer, Vector3(0.f, 0.f, 1.f), true);
		flight->AddFlightMonster(monster, Vector3(150.f, 0.f, 0.f));
		flight->CompleteSetting();

		monster = OBJECT.AddObject<MonsterA2>(flight);
		monster->SetMonsterValue(this, lpPlayer, Vector3(0.f, 0.f, 1.f), true);
		flight->AddFlightMonster(monster, Vector3(-150.f, 0.f, 0.f));
		flight->CompleteSetting();

		MonsterB2* monster2 = OBJECT.AddObject<MonsterB2>(flight);
		monster2->SetMonsterValue(this, lpPlayer, Vector3(0.f, 0.f, 1.f), true);
		flight->AddFlightMonster(monster2, Vector3(0.f, 0.f, 150.f));
		flight->CompleteSetting();
	}
}

void MonsterCreater::CreaterFlightC(const Vector3& vCreaterPos)
{
	MonsterFlight* flight = OBJECT.AddObject<MonsterFlight>();
	flight->SetFlight(lpPlayer, vCreaterPos, Vector3(0.f, 0.f, 1.f), 1000.f, 700.f);

	if (SCENE.sNowScene == "Stage01")
	{
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
	else if (SCENE.sNowScene == "Stage02")
	{
		MonsterA2* monster = OBJECT.AddObject<MonsterA2>(flight);
		monster->SetMonsterValue(this, lpPlayer, Vector3(0.f, 0.f, 1.f), true);
		flight->AddFlightMonster(monster, Vector3(150.f, 0.f, 0.f));
		flight->CompleteSetting();

		monster = OBJECT.AddObject<MonsterA2>(flight);
		monster->SetMonsterValue(this, lpPlayer, Vector3(0.f, 0.f, 1.f), true);
		flight->AddFlightMonster(monster, Vector3(-150.f, 0.f, 0.f));
		flight->CompleteSetting();

		monster = OBJECT.AddObject<MonsterA2>(flight);
		monster->SetMonsterValue(this, lpPlayer, Vector3(0.f, 0.f, 1.f), true);
		flight->AddFlightMonster(monster, Vector3(0.f, -150.f, -150.f));
		flight->CompleteSetting();

		monster = OBJECT.AddObject<MonsterA2>(flight);
		monster->SetMonsterValue(this, lpPlayer, Vector3(0.f, 0.f, 1.f), true);
		flight->AddFlightMonster(monster, Vector3(0.f, 150.f, -150.f));
		flight->CompleteSetting();

		MonsterB2 * monster2 = OBJECT.AddObject<MonsterB2>(flight);
		monster2->SetMonsterValue(this, lpPlayer, Vector3(0.f, 0.f, 1.f), true);
		flight->AddFlightMonster(monster2, Vector3(0.f, 0.f, 150.f));
		flight->CompleteSetting();

	}

}

void MonsterCreater::CreaterMiddleBossA()
{
	bBossWar = true;
	AllDestroyMonster();

	if (SCENE.sNowScene == "Stage01")
	{
		MiddleBossA * monster2 = OBJECT.AddObject<MiddleBossA>();
		monster2->SetMonsterValue(this, lpPlayer, Vector3(0.f, 0.f, 1.f), false);
	}
	else if (SCENE.sNowScene == "Stage02")
	{
		MiddleBossB* monster2 = OBJECT.AddObject<MiddleBossB>();
		monster2->SetMonsterValue(this, lpPlayer, Vector3(0.f, 0.f, 1.f), false);
	}
}

void MonsterCreater::CreaterBossA()
{
	bBossWar = true;
	AllDestroyMonster();

	if (SCENE.sNowScene == "Stage01")
	{
		BossA* monster2 = OBJECT.AddObject<BossA>();
		monster2->SetMonsterValue(this, lpPlayer, Vector3(0.f, 0.f, 1.f), false);
	}
	else if (SCENE.sNowScene == "Stage02")
	{
		BossB* monster2 = OBJECT.AddObject<BossB>();
		monster2->SetMonsterValue(this, lpPlayer, Vector3(0.f, 0.f, 1.f), false);
	}
}

void MonsterCreater::AllDestroyMonster()
{
	for (auto Iter : liMonsters)
	{
		Iter->SetDestroy(true);
	}

	liMonsters.clear();

}

void MonsterCreater::EndBossWar()
{
	fCreateAccrue = 0.f;
	bBossWar = false;
}

