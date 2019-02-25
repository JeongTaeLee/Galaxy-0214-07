#include "DXUT.h"
#include "GameManager.h"

#include "ObjectManager.h"
#include "SceneManager.h"
#include "MonsterCreater.h"

#include"StageMission.h"

GameManager::GameManager()
	:iNowState(1), iLastState(1), iKillMonsterCount(0), iTargetKillMonsterCount(1),bMission(false),
	lpStageMission(nullptr), bCompleteMiddleBoss(false), iTotalKill(0)
{
}


GameManager::~GameManager()
{
}


void GameManager::MissionUpdate()
{
	if (iTargetKillMonsterCount <= iKillMonsterCount && bMission)
	{
		if (lpStageMission)
			lpStageMission->SetDestroy(true);
		
		bMission = false;

		auto find = (MonsterCreater*)OBJECT.FindWithTag("MonsterCreater");
		iTargetKillMonsterCount = 1;
		iKillMonsterCount = 0;
	
		if (!bCompleteMiddleBoss)
		{
			find->CreaterMiddleBossA();
			bCompleteMiddleBoss = true;
		}
		else
			find->CreaterBossA();
	}
}

void GameManager::Reset()
{
	iTargetKillMonsterCount = 1;
	iKillMonsterCount = 0;
	iTotalKill = 0;
	bCompleteMiddleBoss = false;
}

void GameManager::SetMission(int iTarget)
{
	bMission = true;  
	iTargetKillMonsterCount = iTarget; 
	iKillMonsterCount = 0;

	lpStageMission = OBJECT.AddObject < StageMission >();
};

