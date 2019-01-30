#pragma once
#include"Renderer.h"

class ShaderRenderer :
	public Renderer
{
private:
	LPD3DXEFFECT lpEffect;
public:
	ShaderRenderer();
	virtual ~ShaderRenderer();

	virtual void Render()	override;
	
	void SetEffect(LPD3DXEFFECT _lpEffect);

	LPD3DXEFFECT GetEffect() { return lpEffect; }
};

