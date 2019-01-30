#include "DXUT.h"
#include "Stage01.h"

//Manager
#include "ObjectManager.h"

//GameObject
#include "PlayerAirplane.h"

Stage01::Stage01()
{
}


Stage01::~Stage01()
{
}

void Stage01::Init()
{
	OBJECT.AddObject<PlayerAirplane>();
}

void Stage01::Release()
{
	OBJECT.Reset();
}
