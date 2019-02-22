#include "DXUT.h"
#include "Button.h"

#include "InputManager.h"

#include "UIRenderer.h"
#include "Transform.h"
Button::Button()
	:lpRenderer(nullptr), func(nullptr),
	re({0, 0, 0, 0}), bCenter(false)
{
}


Button::~Button()
{
}

void Button::Init()
{
	lpRenderer = AC(UIRenderer);
}

void Button::Update()
{
	if (::PtInRect(&re, { (LONG)INPUT.GetMousePos().x, (LONG)INPUT.GetMousePos().y }))
	{
		if (lpRenderer->GetColor().a > 0.5f)
			lpRenderer->SetColor(D3DXCOLOR(1.f, 1.f, 1.f, lpRenderer->GetColor().a - 0.1f));
	
		if (KEYUP(VK_LBUTTON))
		{
			if (func)
				func();
		}
	}
	else
	{
		if (lpRenderer->GetColor().a < 1.f)
			lpRenderer->SetColor(D3DXCOLOR(1.f, 1.f, 1.f, lpRenderer->GetColor().a + 0.1f));
	}
}

void Button::SetTexture(texture* lpTex, bool Center)
{
	bCenter = Center;
	lpRenderer->SetTexture(lpTex, bCenter);
}

void Button::AutoRect()
{
	transform->UpdateTransform();
	
	if (bCenter)
		SetRect(&re, (int)transform->pos.x - lpRenderer->GetTexture()->info.Width / 2,
		(int)transform->pos.y - lpRenderer->GetTexture()->info.Height / 2,
		(int)transform->pos.x + lpRenderer->GetTexture()->info.Width / 2,
		(int)transform->pos.y + lpRenderer->GetTexture()->info.Height / 2);
	else
		SetRect(&re, (int)transform->pos.x,
			(int)transform->pos.y,
			(int)transform->pos.x + lpRenderer->GetTexture()->info.Width,
			(int)transform->pos.y + lpRenderer->GetTexture()->info.Height);

}
