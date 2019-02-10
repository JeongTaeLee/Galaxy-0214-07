#pragma once
#include "singleton.h"
class CameraManager :
	public singleton<CameraManager>
{
private:
	Vector3 vPos;
	Vector3 vLookAt;
	Vector3 vUp;
	Vector4 v4Pos;

	Vector3 vTargetPos;

	bool	bTargeting;
	float	bTargetS;

	Matrix matView;
	Matrix matProj;
public:
	CameraManager();
	virtual ~CameraManager();

	void Update();

	void SetViewMatrix();
	void SetProjMatrix();

	void SetCameraTransform();
	void SetProjectionTransform();

	Matrix & GetViewMatrix() { return matView; }
	Matrix & GetProjMatrix() { return matProj; }
	
	Vector3 & GetPos() { return vPos; }
	Vector4 & GetV4Pos() { return v4Pos; }
	Vector3& GetLookAt() { return vLookAt; }

	void SetCameraInfo(const Vector3& _vPos, const Vector3& _vLook, const Vector3& _vUp, bool _bTargeting = false, float bTargetS = 0.f);
};

#define CAMERA CameraManager::GetInst()
