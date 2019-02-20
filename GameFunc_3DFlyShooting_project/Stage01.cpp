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

	MonsterDirector* director = OBJECT.AddObject < MonsterDirector >();

	MonsterCreater* monster = OBJECT.AddObject<MonsterCreater>();
	monster->SetMonsterDirector(director);

	PlayerAirplane* player = OBJECT.AddObject<PlayerAirplane>();
	player->SetMonsterDirector(director);
	player->SetCreater(monster);

	monster->SetPlayer(player);
	director->SetPlayer(player);

	MeteorAdmin* meteor = OBJECT.AddObject <MeteorAdmin>();
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

	//Monster
	IMAGE.LoadObjFile("MonsterA", "./rs/obj/MonsterA/MonsterA.obj", true);

	//Meteor
	IMAGE.LoadObjFile("MeteorA", "./rs/obj/Meteor/Meteor1/Meteor_A.obj", true);
	IMAGE.LoadObjFile("MeteorB", "./rs/obj/Meteor/Meteor2/Meteor_B.obj", true);
	IMAGE.LoadObjFile("MeteorC", "./rs/obj/Meteor/Meteor3/Meteor_C.obj", true);

	/****png****/
	
	//EffectA
	IMAGE.LoadTextures("EffectA%d", "./rs/Sprite/Effect_A/(%d).png", 1, 14, true);

	//UI
	IMAGE.LoadTexture("Aim", "./rs/Sprite/UI/Aim.png", true);
	IMAGE.LoadTexture("LockOnEnemyCircle", "./rs/Sprite/UI/LockOnCircle.png", true);
	IMAGE.LoadTexture("NoneLockOnEnemyCircle", "./rs/Sprite/UI/NoneLockOnCircle.png", true);

	bLoadingComplete = true;
}
