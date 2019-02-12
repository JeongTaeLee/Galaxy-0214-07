#pragma once
#include "Component.h"

enum ColliderType
{
	ColliderType_Sphere,
};

class DebugMesh;

class Collider :
	public Component
{
protected:
	ColliderType eColliderType;
	
	Vector3 vOriginColliderPos;
	Vector3 vColliderPos;
	
#ifdef DEBUG
	DebugMesh* lpDebugMesh;
#endif

public:
	Collider();
	virtual ~Collider();

	virtual void Init()	override;
	virtual void Release() override;
	virtual void Update()	override;

	void SetColliderInfo(ColliderType _eColliderType, const Vector3& _vColliderPos);

	virtual bool CheckCollision(Collider* lpOther) PURE;
	virtual void SendCollision(Collider* lpOther);

	const Vector3& GetColliderPos() { return vColliderPos; }
	ColliderType GetColliderType() { return eColliderType; }
};

