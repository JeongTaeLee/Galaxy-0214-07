#include "DXUT.h"
#include "GameVictroy.h"

#include "ImageManager.h"
#include "ObjectManager.h"
#include "GameManager.h"
#include "SceneManager.h"

#include "UIRenderer.h"
#include "Button.h"

GameVictroy::GameVictroy()
{
}


GameVictroy::~GameVictroy()
{
}

void GameVictroy::Init()
{
	GameResult::Init();
	lpRenderer->SetTexture(IMAGE.LoadTexture("GameVictory", "./rs/Sprite/UI/GameVictory.png"), true);

	Button* button = OBJECT.AddObject<Button>();
	button->transform->pos = Vector3(WINSIZEX / 2, 531.f, 0.f);
	button->SetTexture(IMAGE.LoadTexture("NextStage", "./rs/Sprite/UI/NextStage.png"), true);
	button->SetFunc([&]() {
		if (SCENE.sNowScene == "Stage01")
			SCENE.ChangeScene("Stage02");
		else
			SCENE.ChangeScene("MainManu");
		});
	button->AutoRect();

	button = OBJECT.AddObject<Button>();
	button->transform->pos = Vector3(WINSIZEX / 2, 616.f, 0.f);
	button->SetTexture(IMAGE.LoadTexture("MainScreen", "./rs/Sprite/UI/MainScreen.png"), true);
	button->SetFunc([&]() {
			SCENE.ChangeScene("MainManu");
		});
	button->AutoRect();
}
