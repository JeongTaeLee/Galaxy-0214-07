#include "DXUT.h"
#include "BlackHole.h"

//Manager
#include "ImageManager.h"

//Component & GameObject
#include "BBRenderer.h"
#include "Transform.h"
BlackHole::BlackHole()
{
}


BlackHole::~BlackHole()
{
}

void BlackHole::Init()
{
	lpRenderer = AC(BBRenderer);
	lpRenderer->SetTexture(IMAGE.LoadTexture("BlackHole", "./rs/Sprite/EnemyUI/BlackHole.png"));

	transform->pos = Vector3(0.f, 0.f, 0.f);
	transform->scale = Vector3(1000.f, 1000.f, 1000.f);
}
