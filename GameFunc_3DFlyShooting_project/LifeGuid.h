#pragma once
#include "GameObject.h"

class UIRenderer;
class LifeCount;

class LifeGuid :
	public GameObject
{
private:
	UIRenderer* lpUIRenderer;
	
	std::vector<LifeCount*> veLifeCount;
public:
	LifeGuid();
	virtual ~LifeGuid();

	virtual void Init()	override;

};

