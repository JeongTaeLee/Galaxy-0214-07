#include "DXUT.h"
#include "MainGame.h"

//Scene
#include "Stage01.h"

//Manager
#include "SceneManager.h"
#include "ObjectManager.h"
#include "ImageManager.h"
#include "CameraManager.h"

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

	g_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void MainGame::Release()
{
	SceneManager::ReleaseInst();
	ObjectManager::ReleaseInst();
	ImageManager::ReleaseInst();
	CameraManager::ReleaseInst();
}

void MainGame::Update()
{
	CAMERA.Update();
	SCENE.Update();
	OBJECT.Update();
}

void MainGame::Render()
{
	CAMERA.SetViewTransform();
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
