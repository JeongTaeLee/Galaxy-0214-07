#pragma once
#include "GameObject.h"

enum MeteorType
{
	E_METEOR_01,
	E_METEOR_02,
	E_METEOR_03,
};

class ShaderRenderer;
class SphereCollider;
class PlayerAirplane;

class Meteor :
	public GameObject
{
private:
	PlayerAirplane* lpPlayer;

	MeteorType eType;
	SphereCollider* lpCollider;
	
	ShaderRenderer * lpRenderer;

	float fOriginColliderScale;
public:
	Meteor();
	virtual ~Meteor();

	virtual void Init() override;
	virtual void Update()	override;
	void SetMeteor(MeteorType _eType);
	void SetPlayer(PlayerAirplane* player);
};

