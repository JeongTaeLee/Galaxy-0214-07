#pragma once
#include "GameObject.h"

class MonsterAirPlane;
class PlayerAirplane;
class MonsterCreater;

class MonsterFlight :
	public GameObject
{
private:
	PlayerAirplane* lpPlayer;
	MonsterCreater* lpCreater;

	Vector3 vOriginDir;
	float fSpeed;
public:
	MonsterFlight();
	virtual ~MonsterFlight();
	
	virtual void Update()	override;


	void SetFlight(PlayerAirplane* player, MonsterCreater* creater); 
	void AddAirPlane(MonsterAirPlane * lpMonster);

};

