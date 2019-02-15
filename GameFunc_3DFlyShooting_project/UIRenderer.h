#pragma once
#include "Component.h"
class UIRenderer :
	public Component
{
private:
	texture* lpTexture;

	RECT reSrc;
	Vector3 vCenterPos;
public:
	UIRenderer();
	virtual ~UIRenderer();

	void SetTexture(texture* texture, bool bAutoCenter, const Vector3 & centerPos);
	void ChangeTexture(texture* texture);

	void SetCenterPos(const Vector3& centerPos);
};

