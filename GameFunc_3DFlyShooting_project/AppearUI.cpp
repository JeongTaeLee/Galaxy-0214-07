#include "DXUT.h"
#include "AppearUI.h"

#include "UIRenderer.h"
#include "Transform.h"
AppearUI::AppearUI()
{
}


AppearUI::~AppearUI()
{
}

void AppearUI::Update()
{
	if (lpRenderer->GetColor().a < 1.f)
		lpRenderer->SetColor(D3DXCOLOR(1.f, 1.f, 1.f, lpRenderer->GetColor().a + 0.1f));
}

void AppearUI::SetAppearUI(texture* tex)
{
	transform->pos = Vector3(WINSIZEX / 2, WINSIZEY / 2 - 300, 0.f);

	lpRenderer = AC(UIRenderer);
	lpRenderer->SetColor(D3DXCOLOR(1.f, 1.f, 1.f, 0.f));
	lpRenderer->SetTexture(tex, true);
}

