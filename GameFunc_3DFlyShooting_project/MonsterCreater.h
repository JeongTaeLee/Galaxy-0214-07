#pragma once
#include "GameObject.h"

enum MonsterType
{
	E_MonsterA,
	E_MonsterB,
};

class MonsterDirector;

class MonsterCreater :
	public GameObject
{
private:
	MonsterDirector* lpDirector;

	float fCreateAccrue;
	float fCreateDelay;
public:
	MonsterCreater();
	virtual ~MonsterCreater();

	virtual void Update()	override;

	void CreateMonsterA();
	void CreateMonsterB();

public:
	void SetMonsterDirector(MonsterDirector* director) {lpDirector = director;}
};

