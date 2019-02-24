#include "DXUT.h"
#include "InfoScreen.h"

#include "InputManager.h"

#include "UIRenderer.h"
#include "Transform.h"

InfoScreen::InfoScreen()
	:lpRenderer(nullptr)
{
}


InfoScreen::~InfoScreen()
{
}

void InfoScreen::Init()
{
}

void InfoScreen::Update()
{
	if (KEYUP(VK_ESCAPE))
		SetDestroy(true);
}

void InfoScreen::SetInfoScreen(texture* lpTex)
{
	transform->pos = Vector3(WINSIZEX / 2, WINSIZEY / 2, 0.f);

	lpRenderer = AC(UIRenderer);
	lpRenderer->SetTexture(lpTex, true);

	INPUT.SwitchClipMouse();
	INPUT.SwitchShowMouse();
}
