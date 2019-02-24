#include "DXUT.h"
#include "VictroyEnding.h"

#include"TimeManager.h"
#include "ObjectManager.h"
#include "GameManager.h"

#include "UIRenderer.h"

#include "GameVictroy.h"

VictroyEnding::VictroyEnding()
:lpRenderer(nullptr),
fAccrue(0.f), fDelay(0.1f),
iCount(0),
bEnd(false)
{
}


VictroyEnding::~VictroyEnding()
{
}

void VictroyEnding::Init()
{
	LoadImages(veEndings, "WinEnding%d", "./rs/Sprite/Ending_Win/(%d).png", 1, 51);

	lpRenderer = AC(UIRenderer);
	lpRenderer->SetTexture(veEndings[0], false);
}

void VictroyEnding::Update()
{
	if (!bEnd)
	{
		fAccrue += Et;

		if (fAccrue >= fDelay)
		{
			fAccrue = 0.f;

			lpRenderer->ChangeTexture(veEndings[iCount]);

			if (iCount < veEndings.size() - 1)
				++iCount;
			else
			{
				bEnd = true;
				OBJECT.AddObject<GameVictroy>();
			}
		}
	}
}
