#include "DXUT.h"
#include "EffectA.h"

//Manager
#include "ImageManager.h"
#include "TimeManager.h"
//Component
#include "BBRenderer.h"
#include "Transform.h"
EffectA::EffectA()
	:lpRenderer(nullptr), fEffectAccrue(0.f), fEffectDelay(0.f),
	iCount(0)
{
}


EffectA::~EffectA()
{
}

void EffectA::Update()
{
	if (fEffectAccrue >= fEffectDelay)
	{
		fEffectAccrue = 0.f;

		size_t size = vTexture.size();

		if (iCount < (int)size - 1)
			++iCount;
		else
			SetDestroy(true);
		
		lpRenderer->SetTexture(vTexture[iCount]);
	}
	else
		fEffectAccrue += Et;
}

void EffectA::SetEffect(const std::string& keys, const std::string& paths, int mn, int mx, const Vector3& scale, float fDelay)
{
	lpRenderer = AC(BBRenderer);

	transform->scale = scale;

	fEffectAccrue = 0.f;
	fEffectDelay = fDelay;

	for (int i = mn; i <= mx; ++i)
	{
		char key[256];
		sprintf(key, keys.c_str(), i);

		char path[256];
		sprintf(path, paths.c_str(), i);

		vTexture.push_back(IMAGE.LoadTexture(key, path));
	}

	lpRenderer->SetTexture(vTexture[0]);
}
