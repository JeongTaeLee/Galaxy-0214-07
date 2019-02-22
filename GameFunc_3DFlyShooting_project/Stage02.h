#pragma once
#include "Scene.h"
class Stage02 :
	public Scene
{
public:
	Stage02();
	virtual ~Stage02();

	virtual void Init()	override;
	virtual void Release()	override;

	virtual void LoadingResource() override;
};

