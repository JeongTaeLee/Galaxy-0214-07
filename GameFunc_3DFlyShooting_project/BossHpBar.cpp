#include "DXUT.h"
#include "BossHpBar.h"

#include "ImageManager.h"
#include "ObjectManager.h"
#include "UIRenderer.h"

BossHpBar::BossHpBar()
	:lpRenderer(nullptr), lpGaugeRenderer(nullptr),
	iHpGauge(0.f)
{
}


BossHpBar::~BossHpBar()
{
}

void BossHpBar::Init()
{
	lpRenderer = AC(UIRenderer);
	lpRenderer->SetTexture(IMAGE.LoadTexture("BossHpBar", "./rs/Sprite/UI/BossHpBar.png"), false);

	lpGaugeRenderer = OBJECT.AddObject<GameObject>(this)->AC(UIRenderer);
	lpGaugeRenderer->SetTexture(IMAGE.LoadTexture("BossHpGauge", "./rs/Sprite/UI/BossHpGauge.png"), false);
	lpGaugeRenderer->gameObject->transform->pos = Vector3(45.f, 30.f, 0.f);
}

void BossHpBar::SetHp(int iHp)
{
	if (iHp <= 0)
		return;

	lpGaugeRenderer->SerSrc({ 0, 0, LONG(iHp * iHpGauge),
		(LONG)lpGaugeRenderer->GetTexture()->info.Height });
}

void BossHpBar::SetHpBar(const Vector3& pos, int iMaxHp)
{
	transform->pos = pos;
	iHpGauge = lpGaugeRenderer->GetTexture()->info.Width / iMaxHp;
}
