#include "DXUT.h"
#include "Stage02.h"

//Manager
#include "ObjectManager.h"
#include "ImageManager.h"
#include "GameManager.h"
#include "InputManager.h"
#include "SoundManager.h"
//GameObject
#include "PlayerAirplane.h"
#include "MonsterAirPlane.h"
#include "SkyBox.h"
#include "MonsterDirector.h"
#include "MonsterCreater.h"
#include "MeteorAdmin.h"
#include "GameVictroy.h"
#include "GameOver.h"
#include "StageMission.h"
#include "MiddleBossA.h"

Stage02::Stage02()
{
}


Stage02::~Stage02()
{
}

void Stage02::Init()
{
	INPUT.SwitchClipMouse();
	INPUT.SwitchShowMouse();

	GAMEMANAGER.Reset();

	GAMEMANAGER.iNowState = 2;
	GAMEMANAGER.iLastState = 2;

	OBJECT.AddObject<SkyBox>();

	GAMEMANAGER.SetMission(20);

	PlayerAirplane* player = OBJECT.AddObject<PlayerAirplane>();
	MonsterCreater* monster = OBJECT.AddObject<MonsterCreater>();
	MeteorAdmin* meteor = OBJECT.AddObject <MeteorAdmin>();

	player->SetCreater(monster);
	meteor->SetPlayer(player);
	meteor->CreateMeteor();

	SOUND.Play("IngameSound", 1);
}

void Stage02::Release()
{
	SOUND.Stop("IngameSound");

	OBJECT.Reset();
	IMAGE.Reset();
}

void Stage02::LoadingResource()
{
	bLoadingComplete = true;
}
