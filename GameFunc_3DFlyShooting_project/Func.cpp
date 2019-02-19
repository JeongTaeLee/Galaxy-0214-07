#include "DXUT.h"
#include "Func.h"

//Manager
#include "CameraManager.h"
#include "ObjectManager.h"
#include "ImageManager.h"

//Component
#include "Transform.h"

//Object
#include "EffectA.h"

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

float GetLengthVector3(const Vector3& v1, const Vector3& v2)
{
	Vector3 vLength = v1 - v2;
	return  D3DXVec3Length(&vLength);
}

void GetBillBoardMatrix(Matrix& mat, const Vector3& pos, const Vector3& scal)
{
	D3DXMATRIX matView;
	D3DXMatrixIdentity(&matView);
	matView = CAMERA.GetViewMatrix();

	memset(&matView._41, 0, sizeof(D3DXVECTOR3));
	D3DXMatrixInverse(&matView, 0, &matView);

	float fScale[3];

	fScale[0] = scal.x;
	fScale[1] = scal.y;
	fScale[2] = scal.z;

	D3DXVECTOR3 BillPos = pos;
	memcpy(&matView._41, &BillPos, sizeof(D3DXVECTOR3));

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 4; ++j)
			matView(i, j) *= fScale[i];
	}

	mat = matView;
}

void SpaceToClient(Vector3& result, const Vector3& vPos)
{
	//. 변환할 공간 좌표가 있는 viewport 얻음.    
	D3DVIEWPORT9 vp;
	g_device->GetViewport(&vp);
	//. View 변환 행렬과 Projection 변환 행렬의 곱.    
	Matrix	matViewProj = CAMERA.GetViewMatrix() * CAMERA.GetProjMatrix();;
	Vector3 vSpaceToClient;    //. 좌표 변환.      
	D3DXVec3TransformCoord(&vSpaceToClient, &vPos, &matViewProj);
	//. 최종 변환된 좌표 ( x, y, z = 0 )    
	result = Vector3(vp.Width * (vSpaceToClient.x + 1.0f) / 2.0f + vp.X,
		vp.Height * (2.0f - (vSpaceToClient.y + 1.0f)) / 2.0f + vp.Y, 0.0f);
}

void GetLookAt(const Vector3& v1, const Vector3& v2, Quaternion& nowQuater, float fS)
{
	Vector3 vDir = v1 - v2;
	normalize(vDir);

	Matrix matRot;
	D3DXMatrixLookAtLH(&matRot, &D3DXVECTOR3(0, 0, 0), &vDir,
		&D3DXVECTOR3(0, 1, 0));
	D3DXMatrixTranspose(&matRot, &matRot); //

	D3DXQUATERNION currQ;
	D3DXQuaternionRotationMatrix(&currQ, &matRot);
	D3DXQuaternionSlerp(&nowQuater, &nowQuater, &currQ, fS);
}

void CreateEffectA(const Vector3& pos, const Vector3& scale, float speed)
{
	EffectA* effect = OBJECT.AddObject<EffectA>();
  	effect->transform->pos = pos;

	effect->SetEffect("EffectA%d", "./rs/Sprite/Effect_A/Effect00%02d.png", 1, 30, scale, speed);
}
