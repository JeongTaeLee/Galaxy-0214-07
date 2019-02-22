#include "DXUT.h"
#include "LockOned.h"

//Manager
#include "ImageManager.h"

//Component
#include "UIRenderer.h"
#include "Transform.h"

LockOned::LockOned()
{
}


LockOned::~LockOned()
{
}

void LockOned::Init()
{
	lpRenderer = AC(UIRenderer);
	lpRenderer->SetTexture(IMAGE.LoadTexture("LockOned", "./rs/Sprite/UI/LockOned.png"), true);

	transform->pos = Vector3(WINSIZEX / 2, WINSIZEY / 2 - 100, 0.f);
}
