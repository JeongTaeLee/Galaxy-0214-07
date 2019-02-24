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
	{ iKillMonsterCount += i; }
};

#define GAMEMANAGER GameManager::GetInst()