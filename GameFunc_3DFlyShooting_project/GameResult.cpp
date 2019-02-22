#include "DXUT.h"
#include "GameResult.h"

#include "GameManager.h"
#include "ObjectManager.h"
#include "InputManager.h"

#include "Text.h"
#include "UIRenderer.h"

GameResult::GameResult()
{
}


GameResult::~GameResult()
{
}

void GameResult::Init()
{
	INPUT.SwitchClipMouse();
	INPUT.SwitchShowMouse();

	transform->pos = Vector3(WINSIZEX / 2, WINSIZEY / 2, 0.f);
	lpRenderer = AC(UIRenderer);

	GameObject* ScoreObject = OBJECT.AddObject<GameObject>();
	ScoreObject->transform->pos = Vector3(346, 371, 0);
	lpScore = ScoreObject->AC(Text);

	GameObject* KillMonsterObject = OBJECT.AddObject<GameObject>();
	KillMonsterObject->transform->pos = Vector3(982, 371, 0);
	lpKillMonster = KillMonsterObject->AC(Text);

	char number[256];
	sprintf(number, "%05d", GAMEMANAGER.iKillMonsterCount * 10);
	lpScore->SetText(number, 50);

	sprintf(number, "%05d", GAMEMANAGER.iKillMonsterCount);
	lpKillMonster->SetText(number, 50);
}