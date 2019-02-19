#pragma once
#include "GameObject.h"

class Meteor;
class PlayerAirplane;

class MeteorAdmin :
	public GameObject
{
private:
	PlayerAirplane* lpPlayer;

	std::vector<Meteor*> vMeteor;

public:
	MeteorAdmin();
	virtual ~MeteorAdmin();

	virtual void Init()	override;
	virtual void Update()	override;

	void SetPlayer(PlayerAirplane* _lpPlayer);
	void CreateMeteor();
};

