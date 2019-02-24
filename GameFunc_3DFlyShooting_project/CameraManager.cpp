#include "DXUT.h"
#include "CameraManager.h"


CameraManager::CameraManager()
	:lpNowCamera(nullptr), lpNextCamera(nullptr)
{
	SetProjMatrix();
	SetViewMatrix();

	SetCameraTransform();
	SetProjectionTransform();
}


CameraManager::~CameraManager()
{
	for (auto Iter : mCamers)
		SAFE_DELETE(Iter.second);
	
	mCamers.clear();
}

Camera* CameraManager::AddCamera(const std::string& key, Camera* _lpCamera)
{
	if (!_lpCamera)
		return nullptr;

	if (auto find = mCamers.find(key); find != mCamers.end())
		return find->second;

	return mCamers.insert(std::make_pair(key.c_str(), _lpCamera)).first->second;
}

Camera* CameraManager::ChangeCamera(const std::string& key)
{
	if (auto find = mCamers.find(key); find != mCamers.end())
	{
		sNowCamera = find->first;
		lpNextCamera = find->second;
		return lpNextCamera;
	}
	return nullptr;
}

Camera* CameraManager::GetCamera(const std::string& key)
{
	if (auto find = mCamers.find(key); find != mCamers.end())
		return find->second;
	
	return nullptr;
}

void CameraManager::DeleteCamera(const std::string& key)
{
	if (auto find = mCamers.find(key); find != mCamers.end())
	{
		if (lpNowCamera == find->second)
			lpNowCamera = nullptr;

		SAFE_DELETE(find->second);
		mCamers.erase(find);
	}
}

void CameraManager::Update()
{
	if (lpNextCamera)
	{
		lpNowCamera = lpNextCamera;
		lpNextCamera = nullptr;
	}
}

void CameraManager::SetViewMatrix()
{
	if(lpNowCamera)
		D3DXMatrixLookAtLH(&matView, &lpNowCamera->vPos, &lpNowCamera->vLookAt, &lpNowCamera->vUp);
}

void CameraManager::SetProjMatrix()
{
	D3DXMatrixPerspectiveFovLH(&matProj, D3DXToRadian(60), 16.f / 9.f, 1.f, 50000.f);
}

void CameraManager::SetCameraTransform()
{
	g_device->SetTransform(D3DTS_VIEW, &matView);
}

void CameraManager::SetProjectionTransform()
{
	g_device->SetTransform(D3DTS_PROJECTION, &matProj);
}

Vector3 CameraManager::GetPos()
{
	if (lpNowCamera)
		return lpNowCamera->vPos;

	return Vector3(0.f, 0.f, 0.f);
	// TODO: 여기에 반환 구문을 삽입합니다.
}

Vector3 CameraManager::GetLookAt()
{
	if (lpNowCamera)
		return lpNowCamera->vLookAt;

	return Vector3(0.f, 0.f, 0.f);
	// TODO: 여기에 반환 구문을 삽입합니다.
}
