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

	/****png****/
	
	//EffectA
	IMAGE.LoadTextures("EffectA%d", "./rs/Sprite/Effect_A/Effect00%02d.png", 1, 30, true);

	//UI
	IMAGE.LoadTexture("Aim", "./rs/Sprite/UI/Aim.png", true);
	IMAGE.LoadTexture("EnemyCircle", "./rs/Sprite/UI/EnemyCircle.png", true);

	bLoadingComplete = true;
}
