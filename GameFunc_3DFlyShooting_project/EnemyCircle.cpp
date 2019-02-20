#include "DXUT.h"
#include "EnemyCircle.h"

//Manager
#include "ImageManager.h"
#include "CameraManager.h"
#include "TimeManager.h"

//Component;
#include "UIRenderer.h"
#include "Transform.h"

#include "MonsterAirPlane.h"

EnemyCircle::EnemyCircle()
	:lpMonster(nullptr), lpRenderer(nullptr),
	lpNoneLockOnTexture(nullptr), lpLockOnTexture(nullptr),
	bLockOn(false)
{
}


EnemyCircle::~EnemyCircle()
{
}

void EnemyCircle::Init()
{
	lpRenderer = AC(UIRenderer);
	lpRenderer->SetTexture(IMAGE.LoadTexture("NoneLockOnEnemyCircle", "./rs/Sprite/UI/NoneLockOnCircle.png"), true);
	lpNoneLockOnTexture = IMAGE.LoadTexture("NoneLockOnEnemyCircle", "./rs/Sprite/UI/NoneLockOnCircle.png", true);
	lpLockOnTexture = IMAGE.LoadTexture("LockOnEnemyCircle", "./rs/Sprtie/UI/LockOnCircle.png", true);
	transform->scale = Vector3(1.f, 1.f, 1.f);
	
	fRad = 40 * transform->scale.x;

}

void EnemyCircle::Update()
{
	Matrix ViewMatrix = CAMERA.GetViewMatrix();

	Vector3 CheckPos;
	D3DXVec3TransformCoord(&CheckPos, &lpMonster->transform->worldPos, &ViewMatrix);

	if (CheckPos.z > 0.f)
	{
		SpaceToClient(transform->pos, lpMonster->transform->worldPos);
		lpRenderer->SetEnable(true);
	}
	else
		lpRenderer->SetEnable(false);
}

void EnemyCircle::SetMonster(MonsterAirPlane* monster)
{
	lpMonster = monster;
}

void EnemyCircle::SetLockOn(bool _bLockOn)
{
	bLockOn = _bLockOn;

	if (bLockOn)
	{
		lpRenderer->ChangeTexture(lpLockOnTexture);
		lpRenderer->SetLayer(1);
	}
	else
	{
		lpRenderer->ChangeTexture(lpNoneLockOnTexture);
		lpRenderer->SetLayer(0);
	}
}
