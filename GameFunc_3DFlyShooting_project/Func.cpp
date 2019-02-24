#include "DXUT.h"
#include "Func.h"

//Manager
#include "CameraManager.h"
#include "ObjectManager.h"
#include "ImageManager.h"
#include "SoundManager.h"

//Component
#include "Transform.h"

//Object
#include "EffectA.h"


float GetLengthVector2(const Vector2& v1, const Vector2& v2)
{
	Vector2 vLength = v1 - v2;
	return D3DXVec2Length(&vLength);
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

void GetSLerpLookAt(const Vector3& v1, const Vector3& v2, Quaternion& nowQuater, float fS)
{
	Vector3 vDir = v1 - v2;
	normalize(vDir);

	Matrix matRot;
	D3DXMatrixLookAtLH(&matRot, &D3DXVECTOR3(0, 0, 0), &vDir,&D3DXVECTOR3(0, 1, 0));
	D3DXMatrixTranspose(&matRot, &matRot); 

	D3DXQUATERNION currQ;
	D3DXQuaternionRotationMatrix(&currQ, &matRot);
	D3DXQuaternionSlerp(&nowQuater, &nowQuater, &currQ, fS);
}

void GetLookAt(Quaternion& q, const Vector3& v1, const Vector3& v2)
{
	Vector3 vDir = v1 - v2;
	normalize(vDir);

	D3DXMATRIX matRot;
	D3DXMatrixLookAtLH(&matRot, &Vector3(0.f, 0.f, 0.f), &vDir, &Vector3(0.f, 1.f, 0.f));
	D3DXMatrixTranspose(&matRot, &matRot); //

	D3DXQuaternionRotationMatrix(&q, &matRot);
}

void CreateEffectA(const Vector3& pos, const Vector3& scale, float speed)
{
	EffectA* effect = OBJECT.AddObject<EffectA>();
  	effect->transform->pos = pos;

	SOUND.DuplicatePlay("Explosion");
	effect->SetEffect("EffectA%d", "./rs/Sprite/Effect_A/(%d).png", 1, 14, scale, speed);
}

void LoadImages(std::vector<texture*>& veTex, const std::string& keys, const std::string& paths, int mn, int mx)
{
	for (int i = mn; i <= mx; ++i)
	{
		char key[256];
		sprintf(key, keys.c_str(), i);
		
		char path[256];
		sprintf(path, paths.c_str(), i);

		veTex.push_back(IMAGE.LoadTexture(key, " ", false));
	}
}
