#include "DXUT.h"
#include "PlayerAim.h"

//Manager
#include "ImageManager.h"

//Component
#include "UIRenderer.h"
#include "Transform.h"

PlayerAim::PlayerAim()
{
}


PlayerAim::~PlayerAim()
{
}

void PlayerAim::Init()
{
	transform->pos = Vector3(WINSIZEX / 2, WINSIZEY / 2, 0.f);

	lpRenderer = AC(UIRenderer);
	lpRenderer->SetTexture(IMAGE.LoadTexture("Aim", "./rs/Sprite/UI/Aim.png"), true);
}
