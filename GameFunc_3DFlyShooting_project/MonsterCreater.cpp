#include "DXUT.h"
#include "MonsterCreater.h"

#include"Func.h"

//Manager
#include "TimeManager.h"
#include "ObjectManager.h"

//Component & GameObject
#include "MonsterA.h"
#include "MonsterDirector.h"
#include <D3D11.h>


MonsterCreater::MonsterCreater()
	:fCreateAccrue(0.f), fCreateDelay(5.f)
{
}


MonsterCreater::~MonsterCreater()
{
}

void MonsterCreater::Update()
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

void MonsterCreater::CreateMonsterA()
{
	MonsterA* monster = OBJECT.AddObject<MonsterA>();
	monster->SetMonsterDirector(lpDirector);
	monster->transform->pos = transform->pos + Vector3(0.f, 50.f, 0.f);
}

void MonsterCreater::CreateMonsterB()
{
}
