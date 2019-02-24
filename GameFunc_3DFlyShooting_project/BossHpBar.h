#pragma once
#include "GameObject.h"

class UIRenderer;

class BossHpBar :
	public GameObject
{
private:
	UIRenderer* lpRenderer;
	UIRenderer* lpGaugeRenderer;
	int iHpGauge;
public:
	BossHpBar();
	virtual ~BossHpBar();

	virtual void Init()	override;

	void SetHp(int iHp);
	void SetHpBar(const Vector3 & pos, int iMaxHp);
};

