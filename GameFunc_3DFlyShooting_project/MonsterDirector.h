#pragma once
#include "GameObject.h"

class ShaderRenderer;
class PlayerAirplane;
class MonsterAirPlane;

class MonsterDirector :
	public GameObject
{
private:
	ShaderRenderer* lpRenderer;
public:
	MonsterDirector();
	virtual ~MonsterDirector();
	
	virtual void Init()	override;
public:
	void SetDirection(MonsterAirPlane* monster);
	void SetPos(Vector3 _vPos);
};

   