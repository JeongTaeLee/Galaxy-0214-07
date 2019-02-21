#include "DXUT.h"
#include "MonsterBullet.h"

//Component & GameObject
#include "ShaderRenderer.h"
#include "Collider.h"
#include "Transform.h"

#include "Func.h"

MonsterBullet::MonsterBullet()
{
	sTag = "MonsterBullet";
}


MonsterBullet::~MonsterBullet()
{
}

void MonsterBullet::Init()
{
	Bullet::Init();
	fShine = 1.f;

	lpRenderer->SetRenderBegin(
		[&]() {
			lpRenderer->SetShaderVector("gBulletColor", &Vector4(1.f, 1.f, 0.f, 1.f));
			lpRenderer->SetShaderFloat("gShine", fShine);
		});
}

void MonsterBullet::ReceiveCollider(Collider* lpOther)
{
	if (lpOther->gameObject->sTag == "PlayerAirPlane")
	{
		CreateEffectA(transform->pos);
		SetDestroy(true);
	}
}