#include "DXUT.h"
#include "MainManu.h"

#include "ImageManager.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "InputManager.h"
#include "SoundManager.h"

#include "GameObject.h"
#include "Button.h"
#include "UIRenderer.h"
#include "InfoScreen.h"

MainManu::MainManu()
{
}


MainManu::~MainManu()
{
}

void MainManu::Init()
{
	INPUT.SetMouseClip(false);
	INPUT.SetShowMouse(true);

	GameObject* lpBackGround = OBJECT.AddObject<GameObject>();
	UIRenderer* lpRenderer = lpBackGround->AC(UIRenderer);
	lpRenderer->SetTexture(IMAGE.LoadTexture("MainBackGround", "./rs/Sprite/Main/Main.png"), false);

	Button * lpButton = OBJECT.AddObject<Button>();
	lpButton->transform->pos = Vector3(31, 12, 0.f);
	lpButton->SetTexture(IMAGE.LoadTexture("Start", "./rs/Sprite/Main/Main1.png"), false);
	lpButton->SetFunc([&]() {SCENE.ChangeScene("Stage01"); });
	lpButton->AutoRect();

	lpButton = OBJECT.AddObject<Button>();
	lpButton->transform->pos = Vector3(9, 176, 0.f);
	lpButton->SetTexture(IMAGE.LoadTexture("HowTo", "./rs/Sprite/Main/Main2.png"), false);
	lpButton->SetFunc([&]() {OBJECT.AddObject<InfoScreen>()->SetInfoScreen(IMAGE.LoadTexture("HowToScreen", "./rs/Sprite/Main/HowToScreen.png")); });
	lpButton->AutoRect();

	lpButton = OBJECT.AddObject<Button>();
	lpButton->transform->pos = Vector3(15, 337, 0.f);
	lpButton->SetTexture(IMAGE.LoadTexture("Introduction", "./rs/Sprite/Main/Main3.png"), false);
	lpButton->SetFunc([&]() { OBJECT.AddObject<InfoScreen>()->SetInfoScreen(IMAGE.LoadTexture("IntroductionScreen", "./rs/Sprite/Main/IntroductionScreen.png")); });
	lpButton->AutoRect();

	lpButton = OBJECT.AddObject<Button>();
	lpButton->transform->pos = Vector3(46, 506, 0.f);
	lpButton->SetTexture(IMAGE.LoadTexture("Score", "./rs/Sprite/Main/Main4.png"), false);
	lpButton->SetFunc([&]() { OBJECT.AddObject<InfoScreen>()->SetInfoScreen(IMAGE.LoadTexture("RankingScreen", "./rs/Sprite/Main/RankingScreen.png")); });
	lpButton->AutoRect();

	SOUND.Play("MainMenuSound", 1);
	SOUND.SetVol("MainMenuSound", 90);
}

void MainManu::Release()
{
	SOUND.Stop("MainMenuSound");

	OBJECT.Reset();
	IMAGE.Reset();
}

void MainManu::LoadingResource()
{
	SOUND.AddSound("MainMenuSound", "./rs/Sound/MainMenuSound.wav");

	IMAGE.LoadTexture("MainBackGround", "./rs/Sprite/Main/Main.png");
	IMAGE.LoadTexture("Start", "./rs/Sprite/Main/Main1.png");
	IMAGE.LoadTexture("HowTo", "./rs/Sprite/Main/Main2.png");
	IMAGE.LoadTexture("Introduction", "./rs/Sprite/Main/Main3.png");
	IMAGE.LoadTexture("Score", "./rs/Sprite/Main/Main4.png");	

	IMAGE.LoadTexture("HowToScreen", "./rs/Sprite/Main/HowToScreen.png");
	IMAGE.LoadTexture("IntroductionScreen", "./rs/Sprite/Main/IntroductionScreen.png");
	IMAGE.LoadTexture("RankingScreen", "./rs/Sprite/Main/RankingScreen.png");

	bLoadingComplete = true;
}
