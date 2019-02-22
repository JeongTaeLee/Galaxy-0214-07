#pragma once
#include "GameObject.h"

class UIRenderer;
class LifeGauge;

class LifeBar :
	public GameObject
{
private:
	UIRenderer* lpRenderer;
	
	std::vector<LifeGauge*> veGauge;
public:
	LifeBar();
	virtual ~LifeBar();

	virtual void Init()	override;
	
	void SetLife(int life);
};

