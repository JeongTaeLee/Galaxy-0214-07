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
	SortingMonsterCircle();
}

void MonsterCreater::CreateMonsterA()
{
	MonsterA* monster = OBJECT.AddObject<MonsterA>();
	monster->SetCreater(this);
	monster->SetMonsterDirector(lpDirector);
	monster->transform->pos = transform->pos + Vector3(0.f, 50.f, 0.f);
	
	liMonsters.push_back(monster);

}

void MonsterCreater::CreateMonsterB()
{
}

void MonsterCreater::LockOnCheck()
{	
	EnemyCircle* lpNowCircle;
	float fCirCleAimLength = 0.f;
	int iCount = 0;
	
	for (auto Iter : liMonsters)
	{
		/*
		Vector2 Aim(WINSIZEX / 2, WINSIZEY / 2);
		Vector2 Circle(Iter->GetCircle()->transform->pos.x, Iter->GetCircle()->transform->pos.y);

		if (Iter->GetCircle()->GetCircleRad() > GetLengthVector2(Circle, Aim))
		{
			float fPlayerLenth = GetLengthVector3(lpPlayer->transform->pos, Iter->transform->pos);
			
			if (iCount == 0)
			{
				fShortLength = fPlayerLenth;
				lpCircle = Iter->GetCircle();
	
				lpCircle->LockOnProcess();
			}
			else if (fShortLength > fPlayerLenth)
			{
				fShortLength = fPlayerLenth;
				lpCircle = Iter->GetCircle();
			
				lpCircle->LockOnProcess();
			}
			else
				Iter->GetCircle()->ResetLockOn();

			++iCount;
		}
		else
			Iter->GetCircle()->ResetLockOn();
		*/

		Vector2 vCirclePos(Iter->GetCircle()->transform->pos);
		Vector2 vAimPos(WINSIZEX / 2, WINSIZEY / 2);

		float fNowCirCleAimLength = GetLengthVector2(vCirclePos, vAimPos);
		if (iCount == 0)
		{
			lpNowCircle = Iter->GetCircle();
			fCirCleAimLength = fNowCirCleAimLength;

			++iCount;
			continue;
		}


		if (fCirCleAimLength > fNowCirCleAimLength)
		{

		}
		
		++iCount
	}

	
	/*
	if (lpCircle && lpCircle->GetLockOn())
	{
		if(lpLockOnMonster != lpCircle->GetMonster())
		{
			if (lpLockOnMonster)
			{
				lpLockOnMonster->GetCircle() -> ResetLockOn();
				lpLockOnMonster->GetCircle()->SetRendererLayer(0);
			}
			
			lpLockOnMonster = lpCircle->GetMonster();
			lpLockOnMonster->GetCircle()->SetRendererLayer(1);
		}			
	}
	*/
	
	

}

void MonsterCreater::DestroyListMonster(MonsterAirPlane* airPlane)
{
	if (lpLockOnMonster == airPlane)
		lpLockOnMonster = nullptr;

	liMonsters.remove(airPlane);
}

void MonsterCreater::SortingMonsterCircle()
{
	MonsterAirPlane* lpShortMonster = nullptr;
	float fShortLength = 0.f;

	int iCount = 0;

	for (auto Iter : liMonsters)
	{
		if (iCount == 0)
		{
			lpShortMonster = Iter;
			fShortLength = Iter->GetPlayerLength();
		}
		else if (fShortLength > Iter->GetPlayerLength())
		{
			lpShortMonster = lpShortMonster;
			fShortLength = Iter->GetPlayerLength();
		}
		else
			Iter->GetCircle()->SetRendererLayer(0);

		++iCount;
	}

	if (lpShortMonster)
		lpShortMonster->GetCircle()->SetRendererLayer(1);

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
