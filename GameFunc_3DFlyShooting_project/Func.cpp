#include "DXUT.h"
#include "Func.h"

Vector3 GetDirectionVector(const Vector3& v1, const Vector3& v2)
{
	Vector3 vDir = v2 - v1;

	if (vDir.x == 0.f || vDir.y == 0.f || vDir.z == 0.f)
	{
		return {};
	}
	normalize(vDir);

	Vector3 vRot(0.f, 0.f, 0.f);

	vRot.x = atan2f(vDir.z, vDir.y);
	vRot.y = atan2f(vDir.x, vDir.z);

	/*
	D3DXMatrixLookAtLH(&m_tInfo.matRot, &D3DXVECTOR3(0, 0, 0), &(TargetDir),
		&D3DXVECTOR3(0, 1, 0));
	D3DXMatrixTranspose(&m_tInfo.matRot, &m_tInfo.matRot); //

	D3DXQUATERNION currQ;
	D3DXQuaternionRotationMatrix(&currQ, &m_tInfo.matRot);
	D3DXQuaternionSlerp(&prevQ, &prevQ, &currQ, 0.25f);
	D3DXMatrixRotationQuaternion(&m_tInfo.matRot, &prevQ);
	*/

	return vRot;
}