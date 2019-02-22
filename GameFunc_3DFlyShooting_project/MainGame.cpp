#include "DXUT.h"
#include "MainGame.h"

//Scene
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
	g_device->SetRenderState(D3DRS_LIGHTING, false);

	INPUT.SetMouseClip(true);
	INPUT.SetShowMouse(false);

	SCENE.AddScene("Stage01", new Stage01);
	SCENE.AddScene("Stage02", new Stage02);
	SCENE.AddScene("MainManu", new MainManu);
	SCENE.ChangeScene("Stage01");
}

void MainGame::Release()
{

	SceneManager::ReleaseInst();
	ObjectManager::ReleaseInst();
	ImageManager::ReleaseInst();
	CameraManager::ReleaseInst();
	InputManager::ReleaseInst();
	TimeManager::ReleaseInst();
	GameManager::ReleaseInst();
}

void MainGame::Update()
{
	INPUT.Update();
	if (KEYDOWN('R'))
	{
		if (SCENE.sNowScene == "Stage02" || SCENE.sNowScene == "MainManu")
			SCENE.ChangeScene("Stage01");
	}


	SCENE.Update();
	OBJECT.Update();

	CAMERA.Update();
}

void MainGame::Render()
{
	OBJECT.Render();
}

void MainGame::LostDevice()
{
	IMAGE.GetSprite()->OnLostDevice();
}

void MainGame::ResetDevice()
{
	IMAGE.GetSprite()->OnResetDevice();
}
