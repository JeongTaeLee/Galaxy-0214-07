#include "DXUT.h"
#include "SpeedEffect.h"

//Manager
#include "ImageManager.h"

#include "TimeManager.h"
//Compoent
#include "UIRenderer.h"
#include "Transform.h"
SpeedEffect::SpeedEffect()
	:iCount(0),fAccrue(0.f)
{
}


SpeedEffect::~SpeedEffect()
{
}

void SpeedEffect::Init()
{
	transform->pos = Vector3(WINSIZEX / 2, WINSIZEY / 2, 0.f);

	for (int i = 1; i <= 3; ++i)
	{
		char key[256];
		sprintf(key, "SpeedEffect%d", i);

		vTexture.push_back(IMAGE.LoadTexture(key, " "));
	}

	lpUIRenderer = AC(UIRenderer);
	lpUIRenderer->SetTexture(vTexture[0], true);
}

void SpeedEffect::Update()
{
	fAccrue += Et;

	if (fAccrue > 0.05f)
	{
		fAccrue = 0.f;

		lpUIRenderer->ChangeTexture(vTexture[iCount]);

		if (iCount < 2)
			++iCount;
		else
			iCount = 0;

		DEBUG_LOG(iCount);
	}
}
