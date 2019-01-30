#pragma once
#include "singleton.h"
class CameraManager :
	public singleton<CameraManager>
{
private:
	Vector3 vPos;
	Vector3 vLookAt;
	Vector3 vUp;

	Matrix matView;
	Matrix matProj;
public:
	CameraManager();
	virtual ~CameraManager();

	void Update();

	void SetViewMatrix();
	void SetProjMatrix();
	void SetViewTransform();

	Matrix * GetViewMatrix() { return &matView; }
	Matrix * GetProjMatrix() { return &matProj; }
	Vector3 * GetPos() { return &vPos; }
};

#define CAMERA CameraManager::GetInst()