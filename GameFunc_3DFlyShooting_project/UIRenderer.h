#pragma once
#include "Component.h"
class UIRenderer :
	public Component
{
protected:
	texture* lpTexture;
	D3DXCOLOR d3dxColor;

	RECT reSrc;
	Vector3 vCenterPos;

	INT iLayer;
public:
	UIRenderer();
	virtual ~UIRenderer();

	virtual void Init()	override;
	virtual void Release() override;
	virtual void Render() override;

	void SetTexture(texture* texture, bool bAutoCenter, const Vector3& centerPos = Vector3(0.f, 0.f, 0.f));
	void ChangeTexture(texture* texture);

	void SerSrc(RECT re);
	void SetColor(const D3DXCOLOR& color);
	void SetCenterPos(const Vector3& centerPos);
	void SetLayer(int _iLayer) { iLayer = _iLayer; }
	int GetLayer() { return iLayer; }
	
public:
	static bool Sorting(UIRenderer* ui01, UIRenderer* ui02)
	{
		if (ui01->GetLayer() < ui02->GetLayer())
			return true;

		return false;
	}
};

