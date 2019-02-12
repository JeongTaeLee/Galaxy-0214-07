#pragma once
#include "Renderer.h"

class Collider;

class DebugMesh :
	public Renderer
{
private:
	LPD3DXMESH lpDebugMesh;
	Collider* lpCollider;
public:
	DebugMesh();
	virtual ~DebugMesh();

	virtual void Release()	override;
	virtual void Render()	override;

	void SetDebugMesh(Collider * collider);
};

