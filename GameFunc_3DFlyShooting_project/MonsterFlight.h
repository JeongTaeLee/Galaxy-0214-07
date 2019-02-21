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

	Vector3 vDir;
	Vector3 vOriginDir;

	float fShortDistance;

	float fSpeed;
public:
	MonsterFlight();
	virtual ~MonsterFlight();

	virtual void Init()	override;
	virtual void Update()	override;

	void SetFlight(PlayerAirplane* _lpPlayer, const Vector3& vPos, const Vector3& _vOriginDir, float _fShortDistance, float _fSpeed);
	void AddFlightMonster(MonsterAirPlane * _lpMonster, const Vector3 & _vOriginDir);
	void CompleteSetting();
};

