#pragma once
#include "GameObject.h"

class ShaderRenderer;
class PlayerAirplane;
class MonsterAirPlane;

class MonsterDirector :
	public GameObject
{
private:
	PlayerAirplane* lpPlayer;

	ShaderRenderer* lpRenderer;

	Vector3 vPlayerPos;

	Vector3 vShortPos;
	float fShortLength;
public:
	MonsterDirector();
	virtual ~MonsterDirector();
	
	virtual void Init()	override;
	virtual void Update() override;
	
	void DirectionMonster();
	void ReceviePMLength(const Vector3 & pos, float fLength);

public:
	void SetPlayerPos(const Vector3 & vPos) { vPlayerPos = vPos;}
	void SetPlayer(PlayerAirplane* airPlane) { lpPlayer = airPlane; }
};

   