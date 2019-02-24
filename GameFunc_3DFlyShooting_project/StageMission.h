#pragma once
#include "GameObject.h"

class UIRenderer;
class Text;

class StageMission :
	public GameObject
{
private:
	UIRenderer* lpRenderer;
	
	int iNowKill;
	Text* lpTargetKillText;
	Text* lpNowKillText;
	
	Vector3 vTargetPos;
	Vector3 vTargetSize;

	bool bCompleteProcess;
	bool bDisplayEnd;
	
	float fDisplayAccrue;
	float fDisplayDelay;

	float fS;
public:
	StageMission();
	virtual ~StageMission();

	virtual void Init()	override;	
	virtual void Update()	override;
};

