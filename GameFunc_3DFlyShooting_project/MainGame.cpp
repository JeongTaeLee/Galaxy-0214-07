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
