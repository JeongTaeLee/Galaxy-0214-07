#pragma once
#include "Scene.h"
class MainManu :
	public Scene
{
public:
	MainManu();
	virtual ~MainManu();

	virtual void Init()	override;
	virtual void Release()	override;

	virtual void LoadingResource() override;
};

