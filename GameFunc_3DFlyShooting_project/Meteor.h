#pragma once
#include "GameObject.h"


class ShaderRenderer;
class SphereCollider;
class PlayerAirplane;

class Meteor :
	public GameObject
{
private:
	PlayerAirplane* lpPlayer;

	SphereCollider* lpCollider;
	
	ShaderRenderer * lpRenderer;

	float fOriginColliderScale;
public:
	Meteor();
	virtual ~Meteor();

	virtual void Init() override;
	virtual void Update()	override;

	void SetPlayer(PlayerAirplane* player);
	virtual void ReceiveCollider(Collider* lpOther);
};

