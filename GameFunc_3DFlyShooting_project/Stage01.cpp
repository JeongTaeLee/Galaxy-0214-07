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

	PlayerAirplane* player = OBJECT.AddObject<PlayerAirplane>();
	player->SetMonsterDirector(director);
	director->SetPlayer(player);

	MeteorAdmin* meteor = OBJECT.AddObject <MeteorAdmin>();
	meteor->SetPlayer(player);
	meteor->CreateMeteor();
	
	MonsterCreater* monster = OBJECT.AddObject<MonsterCreater>();
	monster->SetMonsterDirector(director);
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
	IMAGE.LoadTextures("EffectA%d", "./rs/Sprite/Effect_A/Effect00%02d.png", 1, 30, true);

	//UI
	IMAGE.LoadTexture("Aim", "./rs/Sprite/UI/Aim.png", true);
	IMAGE.LoadTexture("EnemyCircle", "./rs/Sprite/UI/EnemyCircle.png", true);

	bLoadingComplete = true;
}
