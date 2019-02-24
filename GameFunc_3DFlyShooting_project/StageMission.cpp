#include "DXUT.h"
#include "StageMission.h"

#include "ImageManager.h"
#include "TimeManager.h"
#include "GameManager.h"
#include "ObjectManager.h"

#include "Text.h"
#include "UIRenderer.h"
#include"Transform.h"
StageMission::StageMission()
	:lpRenderer(nullptr), lpTargetKillText(nullptr), lpNowKillText(nullptr),
	iNowKill(0),
	vTargetPos(1135.f, 92.f, 0.f), vTargetSize(0.6f, 0.6f, 1.f), 
	fDisplayAccrue(0.f), fDisplayDelay(2.f), fS(0.f),
	bDisplayEnd(false), bCompleteProcess(false)
{
	sTag = "StageMission";
}


StageMission::~StageMission()
{
}

void StageMission::Init()
{
	transform->pos = Vector3(WINSIZEX / 2, WINSIZEY / 2, 0.f);

	lpRenderer = AC(UIRenderer);
	lpRenderer->SetTexture(IMAGE.LoadTexture("StageMission", "./rs/Sprite/UI/StageMission.png"), true);	

	char number[256];
	
	lpTargetKillText = OBJECT.AddObject<GameObject>(this)->AC(Text);
	lpTargetKillText->gameObject->transform->pos = Vector3(70.f, 5.f, 0.f);
	sprintf(number, "%02d", GAMEMANAGER.GetTargetkillCount());
	lpTargetKillText->SetText(number, 72);

	lpNowKillText = OBJECT.AddObject<GameObject>(this)->AC(Text);
	lpNowKillText->gameObject->transform->pos = Vector3(-80.f, 5.f, 0.f);
	sprintf(number, "%02d", GAMEMANAGER.GetNowKillCount());
	lpNowKillText->SetText(number, 72);
}


void StageMission::Update()
{
	if (!bCompleteProcess)
	{
		if (!bDisplayEnd)
		{	
			fDisplayAccrue += Et;

			if (fDisplayAccrue > fDisplayDelay)
				bDisplayEnd = true;
		}

		if (bDisplayEnd)
		{
			D3DXVec3Lerp(&transform->pos, &transform->pos, &vTargetPos, 0.1f);
			D3DXVec3Lerp(&transform->scale, &transform->scale, &vTargetSize, 0.1f);

			float fLength = GetLengthVector3(vTargetPos, transform->pos);

			if (fLength < 0.1f)
			{
				transform->pos = vTargetPos;
				transform->scale = vTargetSize;

				bCompleteProcess = true;
			}
		}
	}
	else
	{
		if (iNowKill != GAMEMANAGER.GetNowKillCount())
		{
			iNowKill = GAMEMANAGER.GetNowKillCount();

			char number[256];
			sprintf(number, "%02d", GAMEMANAGER.GetNowKillCount());
			lpNowKillText->SetText(number, 72);

		}
	}

}