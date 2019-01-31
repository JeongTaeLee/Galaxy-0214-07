#include "DXUT.h"
#include "MainGame.h"

//Scene
#include "Stage01.h"

//Manager
#include "SceneManager.h"
#include "ObjectManager.h"
#include "ImageManager.h"
#include "CameraManager.h"
#include "TimeManager.h"
#include "InputManager.h"

MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}

void MainGame::Init()
{
	SCENE.AddScene("Stage01", new Stage01);
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
}

void MainGame::Update()
{
	INPUT.Update();
	
	SCENE.Update();
	OBJECT.Update();
	
	CAMERA.Update();
}

void MainGame::Render()
{
	CAMERA.SetCameraTransform();
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
