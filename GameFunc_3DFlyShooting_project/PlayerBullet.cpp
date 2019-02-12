#include "DXUT.h"
#include "PlayerBullet.h"

//Component
#include "ShaderRenderer.h"

PlayerBullet::PlayerBullet()
{
}


PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::Init()
{
	Bullet::Init();
	fShine = 1.f;

	lpRenderer->SetRenderBegin(
		[&]() {
			lpRenderer->SetShaderVector("gBulletColor", &Vector4(1.f, 0.f, 0.f, 1.f));
			lpRenderer->SetShaderFloat("gShine", fShine);
		});
}
