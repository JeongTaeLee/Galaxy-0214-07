#pragma once
#include "GameObject.h"

class UIRenderer;
class MonsterAirPlane;

class EnemyCircle :
	public GameObject
{
private:
	MonsterAirPlane* lpMonster;

	UIRenderer * lpRenderer;
public:
	EnemyCircle();
	virtual ~EnemyCircle();

	virtual void Init()	override;
	virtual void Update() override;
	
	void SetMonster(MonsterAirPlane * monster);
};

