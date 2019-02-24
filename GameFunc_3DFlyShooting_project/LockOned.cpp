#include "DXUT.h"
#include "LockOned.h"

//Manager
#include "ImageManager.h"
#include "TimeManager.h"
//Component
#include "UIRenderer.h"
#include "Transform.h"

LockOned::LockOned()
	:lpRenderer(nullptr), fFlashAccrue(0.f), fFlashTime(0.05f)
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

void LockOned::Update()
{
	fFlashAccrue += Et;

	if (fFlashAccrue > fFlashTime)
	{
		fFlashAccrue = 0.f;

		D3DXCOLOR color = lpRenderer->GetColor();
		color.a = color.a * -1;
		lpRenderer->SetColor(color);
	}
}
