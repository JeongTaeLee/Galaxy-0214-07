#include "DXUT.h"
#include "LifeGuid.h"

//Manger
#include "ImageManager.h"

//Component
#include "UIRenderer.h"
#include "Transform.h"

LifeGuid::LifeGuid()
{
}


LifeGuid::~LifeGuid()
{
}

void LifeGuid::Init()
{
	transform->pos = Vector3(12, 590, 0.f);
	
	lpUIRenderer = AC(UIRenderer);
	lpUIRenderer->SetTexture(IMAGE.LoadTexture("LifeGuid", "./rs/Sprite/UI/healthBar.png"), false);
}
