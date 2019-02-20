#include "DXUT.h"
#include "UIRenderer.h"

#include "GameObject.h"

//Manager
#include "ObjectManager.h"
#include "ImageManager.h"

UIRenderer::UIRenderer()
	:lpTexture(nullptr), d3dxColor(1.f, 1.f, 1.f, 1.f),
	reSrc({0, 0, 0, 0}), vCenterPos(0.f, 0.f, 0.f), iLayer(0)
{
}


UIRenderer::~UIRenderer()
{
}

void UIRenderer::Init()
{
	OBJECT.RegisterUIRenderer(this);
	transform->eUpdateType = E_UPDATE_UI;
}

void UIRenderer::Release()
{
	OBJECT.UnRegisterUIRenderer(this);
}

void UIRenderer::Render()
{
	IMAGE.GetSprite()->SetTransform(&transform->matWorld);
	IMAGE.GetSprite()->Draw(lpTexture->lpD3DTexture, &reSrc, &vCenterPos,
		nullptr, d3dxColor);
}

void UIRenderer::SetTexture(texture* texture, bool bAutoCenter, const Vector3 & centerPos)
{
	lpTexture = texture;

	reSrc = { 0, 0, (LONG)lpTexture->info.Width, (LONG)lpTexture->info.Height };

	if (bAutoCenter)
		vCenterPos = Vector3(lpTexture->info.Width / 2, lpTexture->info.Height / 2, 0.f);
	else
		vCenterPos = centerPos;
}

void UIRenderer::ChangeTexture(texture* texture)
{
	lpTexture = texture;
}

void UIRenderer::SerSrc(RECT re)
{
	reSrc = re;
}

void UIRenderer::SetColor(const D3DXCOLOR& color)
{
	d3dxColor = color;	
}

void UIRenderer::SetCenterPos(const Vector3& centerPos)
{
	vCenterPos = centerPos;
}
