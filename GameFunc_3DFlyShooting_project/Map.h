#pragma once
#include "GameObject.h"

class Renderer;
class ShaderRenderer;

class Map :
	public GameObject
{
private:
	ShaderRenderer * lpRenderer;
public:
	Map();
	virtual ~Map();

	virtual void Init()	override;
};

