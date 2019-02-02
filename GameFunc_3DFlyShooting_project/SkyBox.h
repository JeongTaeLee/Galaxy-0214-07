#pragma once
#include "GameObject.h"

class Renderer;
class ShaderRenderer;
class SkyBox :
	public GameObject
{
private:
	ShaderRenderer * lpRenderer;
public:
	SkyBox();
	~SkyBox();

	virtual void Init()	override;
	virtual void Update()	override;
};

