#include "DXUT.h"
#include "SpeedEffect.h"

//Manager
#include "ImageManager.h"

#include "TimeManager.h"
//Compoent
#include "UIRenderer.h"
#include "Transform.h"
SpeedEffect::SpeedEffect()
	:lpUIRenderer(nullptr), iCount(0), 
	fAccrue(0.f), fDelay(0.f)
{
}


SpeedEffect::~SpeedEffect()
{
}

void SpeedEffect::Init()
{
	transform->pos = Vector3(WINSIZEX / 2, WINSIZEY / 2, 0.f);

	lpUIRenderer = AC(UIRenderer);
	
	LoadImages(vTexs, "SpeedEffect%d", "./rs/Sprite/Speed/%d.png", 1, 3);
	lpUIRenderer->SetTexture(vTexs[0], true);

}

void SpeedEffect::Update()
{
	fAccrue += Et;

	if (fAccrue >= fDelay)
	{
		fAccrue = 0.f;
		
		lpUIRenderer->ChangeTexture(vTexs[iCount]);
		
		if (iCount < 2)
			++iCount;
		else
			iCount = 0;
	}
}
