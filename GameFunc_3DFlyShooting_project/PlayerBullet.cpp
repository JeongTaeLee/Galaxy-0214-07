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
	v4BulletColor = Vector4(1.f, 0.f, 0.f, 0.f);
	fShine = 1.f;

	lpRenderer->SetRenderBegin(
		[&]() {
			lpRenderer->SetShaderVector("gBulletColor", &v4BulletColor);
			lpRenderer->SetShaderFloat("gShine", fShine);
		});
}
