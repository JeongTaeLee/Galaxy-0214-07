#include "DXUT.h"
#include "WeaponUI.h"

#include "ImageManager.h"

#include "UIRenderer.h"
#include "Transform.h"

WeaponUI::WeaponUI()
	:lpRenderer(nullptr),
	lpMachine(nullptr), lpMissileUI(nullptr)
{
}


WeaponUI::~WeaponUI()
{
}

void WeaponUI::Init()
{
	transform->pos = Vector3(1148.f, 652.f, 0.f);

	lpRenderer = AC(UIRenderer);

	lpMachine = IMAGE.LoadTexture("MachineGunUI", "./rs/Sprite/UI/MachingGunUI.png");
	lpMissileUI = IMAGE.LoadTexture("MissileUI", "./rs/Sprite/UI/MissileUI.png");

	lpRenderer->SetTexture(lpMachine, true);
}

void WeaponUI::ChangeWeapon(int i)
{
	if (i == 0)
		lpRenderer->ChangeTexture(lpMachine);
	else
		lpRenderer->ChangeTexture(lpMissileUI);
}
