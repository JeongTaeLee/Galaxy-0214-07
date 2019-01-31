#pragma once
#include "GameObject.h"

class ShaderRenderer;

class Water :
	public GameObject
{
private:
	ShaderRenderer * lpRenderer;
	float fWaterWave;
public:
	Water();
	virtual ~Water();

	virtual void Init()	override;
	virtual void Update()	override;
};

