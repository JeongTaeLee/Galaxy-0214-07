#include "DXUT.h"
#include "LifeBar.h"

#include "ImageManager.h"
#include "ObjectManager.h"

#include "UIRenderer.h"
#include "Transform.h"

#include "LifeGauge.h"
LifeBar::LifeBar()
{
}


LifeBar::~LifeBar()
{
}

void LifeBar::Init()
{
	transform->pos = Vector3(23.f, 578.f, 0.f);

	lpRenderer = AC(UIRenderer);
	lpRenderer->SetTexture(IMAGE.LoadTexture("LifeBar", "./rs/Sprite/UI/healthBar.png"), false);

	for (int i = 0; i < 5; ++i)
	{
		veGauge.push_back(OBJECT.AddObject<LifeGauge>(this));
		veGauge[i]->transform->pos = Vector3(131.f + (48 * i), 33.f, 0.f);
	}
}

void LifeBar::SetLife(int life)
{
	for (int i = 0; i < 5; ++i)
	{
		if (i < life)
			veGauge[i]->SetActive(true);
		else
			veGauge[i]->SetActive(false);
	}
}
