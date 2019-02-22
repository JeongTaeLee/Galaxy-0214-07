#include "DXUT.h"
#include "GameManager.h"


GameManager::GameManager()
	:iNowState(1), iLastState(1), iKillMonsterCount(0)
{
}


GameManager::~GameManager()
{
}

void GameManager::Reset()
{
	iKillMonsterCount = 0;
	iNowState = 1;
}
