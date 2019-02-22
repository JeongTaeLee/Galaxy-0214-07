#include "DXUT.h"
#include "Stage01.h"

//Manager
#include "ObjectManager.h"
#include "ImageManager.h"
#include "GameManager.h"
//GameObject
#include "PlayerAirplane.h"
#include "MonsterAirPlane.h"
#include "SkyBox.h"
#include "MonsterDirector.h"
#include "MonsterCreater.h"
#include "MeteorAdmin.h"
#include "GameVictroy.h"
#include "GameOver.h"
Stage01::Stage01()
{
}


Stage01::~Stage01()
{
}

void Stage01::Init()
{
	GAMEMANAGER.Reset();

	GAMEMANAGER.iLastState = 1;
	GAMEMANAGER.iNowState = 1;

	OBJECT.AddObject<SkyBox>();

	PlayerAirplane* player = OBJECT.AddObject<PlayerAirplane>();
	MonsterCreater* monster = OBJECT.AddObject<MonsterCreater>();
	MeteorAdmin* meteor = OBJECT.AddObject <MeteorAdmin>();
	
	player->SetCreater(monster);
	meteor->SetPlayer(player);
	meteor->CreateMeteor();
}

void Stage01::Release()
{
	OBJECT.Reset();
}

void Stage01::LoadingResource()
{
	/****OBJ****/
	
	//Player
	IMAGE.LoadObjFile("PlayerAirPlane", "./rs/obj/Player/PlayerAirPlane.obj", true);
	
	//PlayerDirctor
	IMAGE.LoadObjFile("PlayerDirector", "./rs/obj/PlayerDirector/PlayerDirector.obj", true);

	//Stage 
	IMAGE.LoadObjFile("SkyBox_Sphere", "./rs/obj/SkyBox_Sphere/Stage.obj", true);

	//Bullet
	IMAGE.LoadObjFile("BasicBullet", "./rs/obj/Bullet/Bullet.obj", true);
	IMAGE.LoadObjFile("Missile", "./rs/obj/Missile/C.obj", true);

	//Monster
	IMAGE.LoadObjFile("MonsterA", "./rs/obj/MonsterA/MonsterA.obj", true);
	IMAGE.LoadObjFile("MonsterB", "./rs/obj/MonsterB/MonsterB.obj", true);
	IMAGE.LoadObjFile("BossA", "./rs/obj/BossA/B.obj", true);


	//Meteor
	IMAGE.LoadObjFile("Meteor", "./rs/obj/Meteor/Meteor.obj", true);
	/****png****/
	
	//EffectA
	IMAGE.LoadTextures("EffectA%d", "./rs/Sprite/Effect_A/(%d).png", 1, 14, true);

	//UI
	IMAGE.LoadTexture("Aim", "./rs/Sprite/UI/Aim.png", true);
	IMAGE.LoadTexture("LockOnEnemyCircle", "./rs/Sprite/UI/LockOnCircle.png", true);
	IMAGE.LoadTexture("NoneLockOnEnemyCircle", "./rs/Sprite/UI/NoneLockOnCircle.png", true);
	IMAGE.LoadTexture("LockOned", "./rs/Sprite/UI/LockOned.png", true);
	IMAGE.LoadTexture("LifeBar", "./rs/Sprite/UI/healthBar.png", true);
	IMAGE.LoadTexture("LifeGauge", "./rs/Sprite/UI/healthGauge.png", true);

	IMAGE.LoadTextures("SpeedEffect%d", "./rs/Sprite/Speed/%d.png", 1, 3, true);
	IMAGE.LoadTexture("PlayerHitEffect", "./rs/Sprite/UI/PlayerHitEffect.png", true);

	IMAGE.LoadTexture("GameVictory", "./rs/Sprite/UI/GameVictory.png", true);
	IMAGE.LoadTexture("GameOver", "./rs/Sprite/UI/GameOver.png", true);

	IMAGE.LoadTexture("Replay", "./rs/Sprite/UI/Replay.png", true);
	IMAGE.LoadTexture("NextState", "./rs/Sprite/UI/NextState.png", true);
	IMAGE.LoadTexture("MainScreen", "./rs/Sprite/UI/MainScreen.png", true);


	bLoadingComplete = true;
}
