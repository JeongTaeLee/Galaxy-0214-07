#include "DXUT.h"
#include "MonsterAirPlane.h"

//Manager
#include "ImageManager.h"

//Component
#include "ShaderRenderer.h"
#include "SphereCollider.h"
MonsterAirPlane::MonsterAirPlane()
	:lpRenderer(nullptr), lpCollider(nullptr), fHp(0.f)
{
}


MonsterAirPlane::~MonsterAirPlane()
{
}

void MonsterAirPlane::Init()
{
	lpRenderer = AC(ShaderRenderer);
	lpCollider = AC(SphereCollider);
	lpRenderer->SetEffect(IMAGE.LoadEffect("Lighting", "Lighting.fx"));

}
