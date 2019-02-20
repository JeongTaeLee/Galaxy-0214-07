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

MonsterCreater::MonsterCreater()
	:lpDirector(nullptr),
	fCreateAccrue(0.f), fCreateDelay(5.f),
	lpLockOnMonster(nullptr)
{
}


MonsterCreater::~MonsterCreater()
{
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

void MonsterCreater::CreateMonsterA()
{
	MonsterA* monster = OBJECT.AddObject<MonsterA>();
	monster->SetCreater(this);
	monster->SetMonsterDirector(lpDirector);
	monster->SetPlayer(lpPlayer);
	monster->transform->pos = transform->pos + Vector3(0.f, 50.f, 0.f);
	

	liMonsters.push_back(monster);

}

void MonsterCreater::CreateMonsterB()
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

		switch (eType)
		{
		case E_MonsterA:
			CreateMonsterA();
			break;
		case E_MonsterB:
			CreateMonsterA();
			break;
		default:
			break;
		}
	}
	else
		fCreateAccrue += Et;
}
