#include "DXUT.h"
#include "UIRenderer.h"


UIRenderer::UIRenderer()
	:lpTexture(nullptr), reSrc({0, 0, 0, 0}), vCenterPos(0.f, 0.f, 0.f)
{
}


UIRenderer::~UIRenderer()
{
}

void UIRenderer::SetTexture(texture* texture, bool bAutoCenter, const Vector3 & centerPos)
{
	lpTexture = texture;

	reSrc = { 0, 0, lpTexture->info.Width, lpTexture->info.Height };

	if (bAutoCenter)
		vCenterPos = Vector3(lpTexture->info.Width / 2, lpTexture->info.Height / 2, 0.f);
	else
		vCenterPos = centerPos;
}

void UIRenderer::ChangeTexture(texture* texture)
{
	lpTexture = texture;
}

void UIRenderer::SetCenterPos(const Vector3& centerPos)
{
	vCenterPos = centerPos;
}
