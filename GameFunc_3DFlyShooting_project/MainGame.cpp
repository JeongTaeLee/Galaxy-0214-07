#include "DXUT.h"
#include "MainGame.h"

//Scene
#include "Intro.h"
#include "MainManu.h"
#include "Stage01.h"
#include "Stage02.h"


//Manager
#include "SceneManager.h"
#include "ObjectManager.h"
#include "ImageManager.h"
#include "CameraManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "GameManager.h"
#include "SoundManager.h"

//Object
#include "SkyBox.h"
MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}

void MainGame::Init()
{
	IMAGE.LoadTextures("LoadingScreen%d", "./rs/Sprite/Loading/(%d).png", 1, 32, true);

	g_device->SetRenderState(D3DRS_LIGHTING, false);

	INPUT.SetMouseClip(true);
	INPUT.SetShowMouse(false);

	CAMERA.AddCamera("AppearCamera", new Camera);
	CAMERA.AddCamera("PlayerCamera", new Camera);

	SCENE.AddScene("Intro", new Intro);
	SCENE.AddScene("Stage01", new Stage01);
	SCENE.AddScene("Stage02", new Stage02);
	SCENE.AddScene("MainManu", new MainManu);
	SCENE.ChangeScene("Intro");
}

void MainGame::Release()
{
	SceneManager::ReleaseInst();
	ObjectManager::ReleaseInst();
	CameraManager::ReleaseInst();
	InputManager::ReleaseInst();
	TimeManager::ReleaseInst();
	GameManager::ReleaseInst();
	ImageManager::ReleaseInst();
	SoundManager::ReleaseInst();
}

void MainGame::Update()
{
	INPUT.Update();
	if (KEYDOWN('R'))
	{
		if (SCENE.sNowScene == "Stage02" || SCENE.sNowScene == "MainManu")
			SCENE.ChangeScene("Stage01");
	}

	GAMEMANAGER.MissionUpdate();
	SCENE.Update();
	CAMERA.Update();
	OBJECT.Update();

	CAMERA.SetViewMatrix();
}

void MainGame::Render()
{
	OBJECT.Render();

	IMAGE.GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
	SCENE.Render();
	IMAGE.GetSprite()->End();

}

void MainGame::LostDevice()
{
	IMAGE.GetSprite()->OnLostDevice();
}

void MainGame::ResetDevice()
{
	IMAGE.GetSprite()->OnResetDevice();
}
