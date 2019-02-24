#pragma once
#include "MonsterAirPlane.h"

struct Camera;
class AppearUI;
class Collider;
class BossHpBar;

class MainMonster :
	public MonsterAirPlane
{
protected:
	BossHpBar* lpHpBar;

	Camera* lpCamera;
	AppearUI* lpAppearUI;
	texture* lpApperaTexture;

	Vector3 vTargetPos;
	Vector3 vTargetLookAt;
	bool bCompleteLookAt;
	bool bCompleteAppear;
	bool bCameraInit;

	float fMinCameraLength;

	float fWaitingAccrue;
	float fWaitingDelay;

	std::string sOldCameraName;
public:
	MainMonster();
	virtual ~MainMonster();

	virtual void Init()	override;
	virtual void Update()	override;

	void Appear();
	virtual void Die() PURE;

	virtual void ReceiveCollider(Collider * lpOther) override;
};

