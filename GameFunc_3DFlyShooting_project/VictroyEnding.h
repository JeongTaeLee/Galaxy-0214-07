#pragma once
#include "GameObject.h"

class UIRenderer;

class VictroyEnding :
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
	VictroyEnding();
	virtual ~VictroyEnding();

	virtual void Init() override;
	virtual void Update()	override;
};

