#pragma once
#include "Component.h"

struct Mesh;

class Renderer :
	public Component
{
protected:
	Mesh* lpMesh;

	std::function<void()> RenderBegin;
	std::function<void()> RenderEnd;
public:
	Renderer();
	virtual ~Renderer();

	virtual void Init()	override;
	virtual void Release() override;
	virtual void Render() override;

	void LoadMesh(Mesh* _lpMesh);
	Mesh * GetMesh() { return lpMesh; }

	void SetRenderBegin(std::function<void()> _RenderBegin);
	void SetRenderEnd(std::function<void()> _RenderEnd);
};

