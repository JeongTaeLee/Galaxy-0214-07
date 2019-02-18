#include "DXUT.h"
#include "EnemyCircle.h"
#include "Func.h"

//Manager
#include "ImageManager.h"
#include "CameraManager.h"

//Component;
#include "UIRenderer.h"
#include "Transform.h"

#include "MonsterAirPlane.h"

EnemyCircle::EnemyCircle()
	:lpMonster(nullptr), lpRenderer(nullptr)
{
}


EnemyCircle::~EnemyCircle()
{
}

void EnemyCircle::Init()
{
	lpRenderer = AC(UIRenderer);
	lpRenderer->SetTexture(IMAGE.LoadTexture("EnemyCircle", "./rs/Sprite/UI/EnemyCircle.png"), true);
	transform->scale = Vector3(0.5f, 0.5f, 1.f);
}

void EnemyCircle::Update()
{
	Matrix ViewMatrix = CAMERA.GetViewMatrix();

	Vector3 CheckPos;
	D3DXVec3TransformCoord(&CheckPos, &lpMonster->transform->worldPos, &ViewMatrix);

	if (CheckPos.z > 0.f)
	{
		SpaceToClient(transform->pos, lpMonster->transform->worldPos);
		lpRenderer->bEnable = true;
	}
	else
		lpRenderer->bEnable = false;

}

void EnemyCircle::SetMonster(MonsterAirPlane* monster)
{
	lpMonster = monster;
}
