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
	Vector4 v4Pos;
	
	Matrix matWorld;
	Matrix matRot;
	Matrix matScale;
	Matrix matPos;

	bool bTransformUpdate;
public:
	Transform();
	virtual ~Transform();

	void UpdateTransform();
	void UpdateTransform02();
	void SetTransform();
};

