#pragma once
#include "singleton.h"

struct Camera
{
	Vector3 vPos;
	Vector3 vLookAt;
	Vector3 vUp;
	
	Camera()
		:vPos(0.f, 0.f, 0.f),
		vLookAt(0.f, 0.f, 0.f),
		vUp(0.f, 0.f, 0.f) 
	{}
};

class CameraManager :
	public singleton<CameraManager>
{
public:
	std::string sNowCamera;
	Camera* lpNowCamera;
	Camera* lpNextCamera;
	std::map<std::string, Camera*> mCamers;

	Matrix matView;
	Matrix matProj;
public:
	CameraManager();
	virtual ~CameraManager();

	Camera* AddCamera(const std::string& key, Camera* _lpCamera = nullptr);
	Camera* ChangeCamera(const std::string& key);
	Camera* GetCamera(const std::string& key);
	void DeleteCamera(const std::string& key);
public:
	void Update();

	void SetViewMatrix();
	void SetProjMatrix();

	void SetCameraTransform();
	void SetProjectionTransform();

	Matrix& GetViewMatrix() { return matView; }
	Matrix& GetProjMatrix() { return matProj; }

	Vector3 GetPos();
	Vector3 GetLookAt();

	Camera* GetCamera() { return lpNowCamera; }
	const std::string& GetNowCameraName() { return sNowCamera; }
	
};

#define CAMERA CameraManager::GetInst()
