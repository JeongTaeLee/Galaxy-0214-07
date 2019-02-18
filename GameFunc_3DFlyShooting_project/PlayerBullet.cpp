#include "DXUT.h"
#include "PlayerBullet.h"

//Component
#include "Collider.h"
#include "ShaderRenderer.h"
#include "Transform.h"

//GameObject;
#include "GameObject.h"

#include "Func.h"

PlayerBullet::PlayerBullet()
{
	sTag = "PlayerBullet";
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
	if (Other->gameObject->sTag == "Monster")
	{
		float fRandomScale = GetRandomNumber(50.f, 200.f);

		CreateEffectA(transform->pos, Vector3(fRandomScale, fRandomScale, 1.f), 0.01f);
		SetDestroy(true);
	}
}
