#pragma once
#include "GameObject.h"

class UIRenderer;

class LoseEnding :
	public GameObject
{
private:
	UIRenderer* lpRenderer;

	std::vector<texture*> veEndings;

	float fAccrue;
	float fDelay;
	int iCount;

	bool bEnd;
public:
	LoseEnding();
	virtual ~LoseEnding();

	virtual void Init() override;
	virtual void Release()	override;
	virtual void Update()	override;
};

