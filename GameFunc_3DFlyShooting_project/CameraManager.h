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
	bool	bLerpPos;
	float	fLerpPos;

	Vector3 vTargetLookAt;
	bool	bLerpLookAt;
	float	fLerpLookAt;

	Vector3 vTargetUp;
	bool	bLerpUp;
	float	fLerpUp;


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

	Matrix& GetViewMatrix() { return matView; }
	Matrix& GetProjMatrix() { return matProj; }

	Vector3& GetPos() { return vPos; }
	Vector4& GetV4Pos() { return v4Pos; }
	Vector3& GetLookAt() { return vLookAt; }

	void SetCameraPos(const Vector3& _vPos, bool _bLerpPos, float _fLerp);
	void SetCameraLookAt(const Vector3& _vLookAt, bool _bLerpPos, float _fLerp = 0.3f);
	void SetCameraUp(const Vector3& _vUp, bool _bLerpUp, float _fLerp = 0.3f);

};

#define CAMERA CameraManager::GetInst()
