#pragma once
#include "UIRenderer.h"
class Text :
	public UIRenderer
{
private:
	std::string sText;

	int iSize;
	D3DXCOLOR color;
public:
	Text();
	virtual ~Text();
	
	virtual void Init()	override;
	virtual void Release()	override;

	virtual void Render()	override;

	void SetText(const std::string& _sText, int _iSize = 10, D3DXCOLOR _color = D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
};

