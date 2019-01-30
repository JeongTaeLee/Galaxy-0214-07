#pragma once
#include "Scene.h"
class Stage01 :
	public Scene
{
public:
	Stage01();
	virtual ~Stage01();

	virtual void Init()	override;
	virtual void Release()	override;

};

