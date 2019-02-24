#include "DXUT.h"
#include "LifeGauge.h"

#include "ImageManager.h"

#include "UIRenderer.h"

LifeGauge::LifeGauge()
	:lpRenderer(nullptr)
{
}


LifeGauge::~LifeGauge()
{
}

void LifeGauge::Init()
{
	lpRenderer = AC(UIRenderer);
	lpRenderer->SetTexture(IMAGE.LoadTexture("LifeGauge", "./rs/Sprite/UI/LifeGauge.png"), false);

	
}
