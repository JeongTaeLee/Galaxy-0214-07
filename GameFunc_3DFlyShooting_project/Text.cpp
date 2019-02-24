#include "DXUT.h"
#include "Text.h"

//Manager
#include "ImageManager.h"
#include "ObjectManager.h"

#include "Transform.h"
Text::Text()
	:sText("None"), iSize(0), color(D3DXCOLOR(1.f, 1.f, 1.f, 1.f))
{

}


Text::~Text()
{
}

void Text::Init()
{
	transform->eUpdateType = TransformUpdateType::E_UPDATE_UI;

	OBJECT.RegisterUIRenderer(this);
}

void Text::Release()
{
	OBJECT.UnRegisterUIRenderer(this);
}


void Text::Render()
{
	D3DXFONT_DESC dese =
	{
		iSize, 0
		, FW_BOLD, 1, FALSE
		, HANGUL_CHARSET
		, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE
		, TEXT("µ¸¿òÃ¼")
	};

	LPD3DXFONT font = nullptr;
	D3DXCreateFontIndirect(g_device, &dese, &font);

	RECT rc = { 0 };

	IMAGE.GetSprite()->SetTransform(&transform->matWorld);
	font->DrawTextA(IMAGE.GetSprite(), sText.c_str(), -1, &rc, DT_NOCLIP | DT_CENTER, color);

	SAFE_RELEASE(font);
}

void Text::SetText(const std::string& _sText, int _iSize, D3DXCOLOR _color)
{
	sText = _sText;
	iSize = _iSize;
	color = _color;
}
