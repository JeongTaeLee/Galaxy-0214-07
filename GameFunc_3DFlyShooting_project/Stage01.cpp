#include "DXUT.h"
#include "Stage01.h"

//Manager
#include "ObjectManager.h"
#include "ImageManager.h"

//GameObject
#include "PlayerAirplane.h"
#include "MonsterAirPlane.h"
#include "SkyBox.h"
#include "MonsterDirector.h"
#include "MonsterCreater.h"
#include "MeteorAdmin.h"
Stage01::Stage01()
{
}


Stage01::~Stage01()
{
}

void Stage01::Init()
{
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

	bLoadingComplete = true;
}
