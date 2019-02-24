#include "DXUT.h"
#include "IntroAnimation.h"
#include "UIRenderer.h"

#include "SceneManager.h"
#include "TimeManager.h"


IntroAnimation::IntroAnimation()
	:lpRenderer(nullptr),
	fAccrue(0.f), fDelay(0.1f),
	iCount(0),
	bEnd(false)
{
}


IntroAnimation::~IntroAnimation()
{
}

void IntroAnimation::Init()
{
	LoadImages(veIntro, "Intro%d", " ", 1, 61);

	lpRenderer = AC(UIRenderer);
	lpRenderer->SetTexture(veIntro[0], false);
}

void IntroAnimation::Update()
{
	if (!bEnd)
	{
		fAccrue += Et;

		if (fAccrue >= fDelay)
		{
			fAccrue = 0.f;

			lpRenderer->ChangeTexture(veIntro[iCount]);

			if (iCount < veIntro.size() - 1)
				++iCount;
			else
				SCENE.ChangeScene("MainManu");
		}
	}
}
