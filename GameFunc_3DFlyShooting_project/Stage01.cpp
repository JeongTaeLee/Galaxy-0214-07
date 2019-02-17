#include "DXUT.h"
#include "Stage01.h"

//Manager
#include "ObjectManager.h"

//GameObject
#include "PlayerAirplane.h"
#include "MonsterAirPlane.h"
#include "SkyBox.h"
#include "MonsterA.h"
#include "MonsterDirector.h"
Stage01::Stage01()
{
}


Stage01::~Stage01()
{
}

void Stage01::Init()
{
	OBJECT.AddObject<SkyBox>();
	
	MonsterDirector * director = OBJECT.AddObject < MonsterDirector >();

	PlayerAirplane* player = OBJECT.AddObject<PlayerAirplane>();
	player->SetMonsterDirector(director);
	director->SetPlayer(player);
	
	MonsterAirPlane* monster = OBJECT.AddObject<MonsterA>();
	monster->SetMonsterDirector(director);
	monster->transform->pos = Vector3(0.f, 0.f, 500.f);
}

void Stage01::Release()
{
	OBJECT.Reset();
}
