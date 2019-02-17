#pragma once
#include "Component.h"

enum TransformUpdateType
{
	E_UPDATE_01 = 0,
	E_UPDATE_02,
	E_UPDATE_UI,
};

class Transform :
	public Component
{
public:
	Vector3 pos;
	Vector3 rot;
	Vector3 scale;
	Vector3 worldPos;
	
	Quaternion qRot;

	Matrix matRot;
	Matrix matScale;
	Matrix matPos;
	Matrix matWorld;

	TransformUpdateType eUpdateType;
public:
	Transform();
	virtual ~Transform();

	void UpdateTransform();

	void UpdateTransform01();
	void UpdateTransform02();
	void UpdateTrasformUI();

	void SetTransform();

};

