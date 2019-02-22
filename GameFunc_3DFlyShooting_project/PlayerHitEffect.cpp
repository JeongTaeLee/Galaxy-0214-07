#include "DXUT.h"
#include "PlayerHitEffect.h"

#include "ImageManager.h"
#include "TimeManager.h"

#include "UIRenderer.h"
#include "Transform.h"

PlayerHitEffect::PlayerHitEffect()
	:lpRenderer(nullptr), fFlickerAccrue(0.f), fFlickerDelay(0.05f)
{
}


PlayerHitEffect::~PlayerHitEffect()
{
}

void PlayerHitEffect::Init()
{
	transform->pos = Vector3(WINSIZEX / 2, WINSIZEY / 2, 0.f);

	lpRenderer = AC(UIRenderer);
	lpRenderer->SetTexture(IMAGE.LoadTexture("PlayerHitEffect", "./rs/Sprite/UI/PlayerHitEffect.png"), true);
}

void PlayerHitEffect::Update()
{
	if (fFlickerAccrue >= fFlickerDelay)
	{
		fFlickerAccrue = 0.f;

		lpRenderer->SetColor(D3DXCOLOR(1.f, 1.f, 1.f,  lpRenderer->GetColor().a * -1));
	}
	else
		fFlickerAccrue += Et;
}
