#include "DXUT.h"
#include "GameOver.h"

#include "ImageManager.h"
#include "GameManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"

#include "UIRenderer.h"

#include "Button.h"

GameOver::GameOver()
{
}


GameOver::~GameOver()
{
}

void GameOver::Init()
{
	GameResult::Init();
	lpRenderer->SetTexture(IMAGE.LoadTexture("GameOver", "./rs/Sprite/UI/GameOver.png"), true);

	Button* button = OBJECT.AddObject<Button>();
	button->transform->pos = Vector3(WINSIZEX / 2, 531.f, 0.f);
	button->SetTexture(IMAGE.LoadTexture("Replay", "./rs/Sprite/UI/Replay.png"), true);
	button->SetFunc([]() {
			SCENE.ChangeScene(SCENE.sNowScene);
		});
	button->AutoRect();

	button = OBJECT.AddObject<Button>();
	button->transform->pos = Vector3(WINSIZEX / 2, 616.f, 0.f);
	button->SetTexture(IMAGE.LoadTexture("MainScreen", "./rs/Sprite/UI/MainScreen.png"), true);
	button->SetFunc([]() {
		SCENE.ChangeScene("MainManu");
		});
	button->AutoRect();
}
