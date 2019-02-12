#pragma once
#include "Component.h"
class Transform :
	public Component
{
public:
	Vector3 pos;
	Vector3 worldPos;
	Vector3 rot;
	Vector3 scale;
	
	Quaternion qRot;

	Matrix matRot;
	Matrix matScale;
	Matrix matPos;
	Matrix matWorld;

	bool bTransformUpdate;
public:
	Transform();
	virtual ~Transform();

	void UpdateTransform();
	void UpdateTransform02();
	void SetTransform();
};

