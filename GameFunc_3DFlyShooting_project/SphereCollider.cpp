#include "DXUT.h"
#include "SphereCollider.h"


//Component
#include"Transform.h"
#include "DebugMesh.h"

//Object
#include "GameObject.h"

SphereCollider::SphereCollider()
	:fRadius(0.f)
{

}


SphereCollider::~SphereCollider()
{
}

void SphereCollider::InitSphere(Vector3 _vSpherePos, float _fRadius)
{
	fRadius = _fRadius;
	SetColliderInfo(ColliderType::ColliderType_Sphere, _vSpherePos);

#ifdef DebugColliderRender
	lpDebugMesh = gameObject->AC(DebugMesh);
	lpDebugMesh->SetDebugMesh(this);
#endif
}


bool SphereCollider::CheckCollision(Collider* lpOther)
{
	switch (lpOther->GetColliderType())
	{
	case ColliderType_Sphere:
		SphereCollider* Ohter = static_cast<SphereCollider*>(lpOther);
		
		Vector3 vPos = vColliderPos;
		Vector3 vOtherPos = Ohter->GetColliderPos();	

 		float fMaxLength = pow(fRadius + Ohter->GetRadius(), 2.f);
		float fLength = pow(vOtherPos.x - vPos.x, 2.f) + pow(vOtherPos.y - vPos.y, 2.f) + pow(vOtherPos.z - vPos.z, 2.f);
		
		if (fLength < fMaxLength)
		{
			SendCollision(Ohter);
			return true;
		}
		
		break;
	}

	return false;
}

