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
#include "EnemyCircle.h"
#include "PlayerAirplane.h"
#include "BossA.h"
MonsterCreater::MonsterCreater()
	:lpDirector(nullptr),
	fCreateAccrue(0.f), fCreateDelay(5.f),
	lpLockOnMonster(nullptr)
{
}


MonsterCreater::~MonsterCreater()
{
}

void MonsterCreater::Init()
{
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
	if (lpPlayer)
	{
		if (lpPlayer->GetDestroy())
			lpPlayer = nullptr;
	}

	if (!lpPlayer)
		return; 

	CreateMonster();
}

void MonsterCreater::CreateMonsterA(const Vector3 & createPos)
{
	MonsterA* monster = OBJECT.AddObject<MonsterA>();
	monster->SetMonsterDirector(lpDirector);
	monster->transform->pos = createPos;
	
	liMonsters.push_back(monster);
}

void MonsterCreater::CreateMonsterB(const Vector3& createPos)
{
}

void MonsterCreater::DestroyListMonster(MonsterAirPlane* airPlane)
{
	if (lpLockOnMonster == airPlane)
		lpLockOnMonster = nullptr;

	liMonsters.remove(airPlane);
}

void MonsterCreater::CreateMonster()
{
	if (fCreateAccrue > fCreateDelay)
	{
		fCreateAccrue = 0.f;

		MonsterType eType = (MonsterType)GetRandomNumber(0, 1);
		Vector3 vCreatePos = veCreatePos[GetRandomNumber(0, (int)veCreatePos.size() - 1)];

		switch (eType)
		{
		case E_MonsterA:
			CreateMonsterA(vCreatePos);
			break;
		case E_MonsterB:
			CreateMonsterA(vCreatePos);
			break;
		default:
			break;
		}
	}
	else
		fCreateAccrue += Et;
}
