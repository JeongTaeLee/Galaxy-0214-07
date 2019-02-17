#pragma once
#include "Renderer.h"
class BBRenderer :
	public Renderer
{
private:
	texture* lpTexture;
public:
	BBRenderer();
	virtual ~BBRenderer();

	virtual void Render()	override;

public:
	void SetTexture(texture* texture);
};

