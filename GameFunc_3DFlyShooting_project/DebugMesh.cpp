#include "DXUT.h"
#include "DebugMesh.h"

//Component
#include "Collider.h"
#include "SphereCollider.h"
#include "Transform.h"
DebugMesh::DebugMesh()
{
}


DebugMesh::~DebugMesh()
{
}

void DebugMesh::Release()
{
	Renderer::Release();
	SAFE_RELEASE(lpDebugMesh);
}

void DebugMesh::Render()
{
	if (lpDebugMesh && lpCollider)
	{
		Vector3 vPos = lpCollider->GetColliderPos();

		D3DXMATRIX matPos;
		D3DXMatrixTranslation(&matPos, vPos.x, vPos.y, vPos.z);

		D3DXMATRIX matRot;
		D3DXMatrixRotationQuaternion(&matRot, &transform->qRot);

		g_device->SetTransform(D3DTS_WORLD, &(matRot * matPos));

		g_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		g_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		if (lpDebugMesh)
			lpDebugMesh->DrawSubset(0);

		g_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		g_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
}

void DebugMesh::SetDebugMesh(Collider* collider)
{
	lpCollider = collider;

	switch (collider->GetColliderType())
	{
	case ColliderType::ColliderType_Sphere:
	{
		SphereCollider* sphereCollider = static_cast<SphereCollider*>(collider);
		D3DXCreateSphere(g_device, sphereCollider->GetRadius(), 20, 20, &lpDebugMesh, nullptr);
		break;
	}
	default:
		break;
	}
}
