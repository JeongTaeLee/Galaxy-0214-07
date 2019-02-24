#pragma once
#include "Scene.h"
class Intro :
	public Scene
{
public:
	Intro();
	virtual ~Intro();

	virtual void Init()	override;
	virtual void Release()	override;

	virtual void LoadingResource() override;
};

