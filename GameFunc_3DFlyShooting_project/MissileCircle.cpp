#include "DXUT.h"
#include "MissileCircle.h"

#include "ImageManager.h"
#include "CameraManager.h"

#include "UIRenderer.h"
#include "transform.h"

#include "Missile.h"

MissileCircle::MissileCircle()
	:lpMissile(nullptr),
	lpRenderer(nullptr)
{
}


MissileCircle::~MissileCircle()
{
}

void MissileCircle::Init()
{
	lpRenderer = AC(UIRenderer);
	lpRenderer->SetTexture(IMAGE.LoadTexture("MissileCircle", "./rs/Sprite/UI/MonsterMissile.png"), true);

	transform->scale = Vector3(0.5f, 0.5f, 0.5f);
}

void MissileCircle::Update()
{
	Matrix ViewMatrix = CAMERA.GetViewMatrix();

	Vector3 CheckPos;
	D3DXVec3TransformCoord(&CheckPos, &lpMissile->transform->worldPos, &ViewMatrix);

	if (CheckPos.z > 0.f)
	{
		SpaceToClient(transform->pos, lpMissile->transform->worldPos);
		lpRenderer->SetEnable(true);
	}
	else
		lpRenderer->SetEnable(false);
}
