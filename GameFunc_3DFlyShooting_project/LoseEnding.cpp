#include "DXUT.h"
#include "LoseEnding.h"

#include "TimeManager.h"
#include "SoundManager.h"

#include "UIRenderer.h"

#include "ObjectManager.h"
#include "GameOver.h"

LoseEnding::LoseEnding()
	:lpRenderer(nullptr),
	fAccrue(0.f), fDelay(0.1f),
	iCount(0),
	bEnd(false)
{
}


LoseEnding::~LoseEnding()
{
}

void LoseEnding::Init()
{
	LoadImages(veEndings, "LoseEnding%d", "./rs/Sprite/Ending_Lose/(%d).png", 1, 51);

	lpRenderer = AC(UIRenderer);
	lpRenderer->SetTexture(veEndings[0], false);

	SOUND.AllStop();
	SOUND.Play("GameOver", 1);
}

void LoseEnding::Release()
{
	SOUND.Stop("GameOver");
}

void LoseEnding::Update()
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
				OBJECT.AddObject<GameOver>();
			}
		}
	}
}
