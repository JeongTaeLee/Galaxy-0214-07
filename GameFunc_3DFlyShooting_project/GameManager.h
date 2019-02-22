#pragma once
#include "singleton.h"

class GameManager :
	public singleton<GameManager>
{
public:
	int iLastState;
	int iNowState;
	int iKillMonsterCount;

public:
	GameManager();
	virtual ~GameManager();

	void Reset();
};

#define GAMEMANAGER GameManager::GetInst()