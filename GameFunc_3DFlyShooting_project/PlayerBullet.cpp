#include "DXUT.h"
#include "PlayerBullet.h"

//Component
#include "Collider.h"
#include "ShaderRenderer.h"

//GameObject;
#include "GameObject.h"

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

void PlayerBullet::ReceiveCollider(Collider* Other)
{
	if (Other->gameObject->sTag != "PlayerAirPlane")
	{
		Other->gameObject->SetDestroy(true);
	}
}
