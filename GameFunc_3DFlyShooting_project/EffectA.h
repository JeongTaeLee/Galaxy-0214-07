#pragma once
#include "GameObject.h"

class BBRenderer;

class EffectA :
	public GameObject
{
private:
	BBRenderer* lpRenderer;

	std::vector<texture*> vTexture;

	int iCount;

	float fEffectAccrue;
	float fEffectDelay;
public:
	EffectA();
	virtual ~EffectA();

	virtual void Update()	override;

	virtual void SetEffect(const std::string& keys, const std::string& paths, int mn, int mx, const Vector3& scale = Vector3(1.f, 1.f, 1.f), float fDelay = 0.05f);
};

