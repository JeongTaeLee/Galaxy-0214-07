#pragma once
#include "singleton.h"

class MonsterCreater;
class StageMission;
class GameManager :
	public singleton<GameManager>
{
private:
	StageMission* lpStageMission;

	bool bCompleteMiddleBoss;

	bool bMission;
	int iKillMonsterCount;
	int iTargetKillMonsterCount;

public:
	int iTotalKill;
	int iLastState;
	int iNowState;

public:
	GameManager();
	virtual ~GameManager();

	void MissionUpdate();
	void Reset();

	void SetMission(int iTarget);

	int GetNowKillCount() 
	{ return iKillMonsterCount; }
	
	int GetTargetkillCount() 
	{ return iTargetKillMonsterCount; }
	
	void AddNowKill(int i) 
	{
		iKillMonsterCount += i; iTotalKill = iKillMonsterCount;
	}
};

#define GAMEMANAGER GameManager::GetInst()