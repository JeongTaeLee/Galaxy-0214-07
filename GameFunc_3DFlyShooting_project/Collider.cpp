#include "DXUT.h"
#include "Collider.h"

//Manager
#include "ObjectManager.h"

//Component
#include "Component.h"
#include "DebugMesh.h"

//Object
#include"GameObject.h"

Collider::Collider()
	:vColliderPos(0.f, 0.f, 0.f), vOriginColliderPos(0.f, 0.f,0.f), eColliderType(ColliderType_Sphere)
{
#ifdef DebugCollideRender
	lpDebugMesh = nullptr;
#endif
}


Collider::~Collider()
{
}

void Collider::Init()
{
	OBJECT.RegisterCollider(this);
}

void Collider::Release()
{
	OBJECT.UnRegisterCollider(this);

#ifdef DebugColliderRender
	if(lpDebugMesh)
		lpDebugMesh->bEnable = false;
#endif // DEBUG
}

void Collider::ColliderUpdate()
{
	D3DXMATRIX matObjectRot;
	D3DXMatrixRotationQuaternion(&matObjectRot, &transform->qRot);
	memcpy(&matObjectRot._41, &transform->worldPos, sizeof(Vector3));

	D3DXVec3TransformCoord(&vColliderPos, &vOriginColliderPos, &matObjectRot);
}

void Collider::SetColliderInfo(ColliderType _eColliderType, const Vector3& _vColliderPos)
{
	vOriginColliderPos = _vColliderPos;
	vColliderPos = vOriginColliderPos;
	Update();
}

void Collider::SendCollision(Collider* lpOther)
{
	gameObject->ReceiveCollider(lpOther);
	gameObject->SendCollider(lpOther);
}
