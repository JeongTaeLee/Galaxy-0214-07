#include "DXUT.h"
#include "ShaderRenderer.h"

//Manager
#include "CameraManager.h"
#include "ObjectManager.h"

ShaderRenderer::ShaderRenderer()
	:lpEffect(nullptr)
{
}


ShaderRenderer::~ShaderRenderer()
{
}

void ShaderRenderer::Render()
{
	lpEffect->SetMatrix(D3DXHANDLE("gWorldMatrix"), &transform->matWorld);
	lpEffect->SetMatrix(D3DXHANDLE("gViewMatrix"), &CAMERA.GetViewMatrix());
	lpEffect->SetMatrix(D3DXHANDLE("gProjMatrix"), &CAMERA.GetProjMatrix());
	
	if (RenderBegin)
		RenderBegin(); 

	UINT numPasses = 0;
	lpEffect->Begin(&numPasses, NULL);
	
	for (UINT i = 0; i < numPasses; ++i)
	{
		lpEffect->BeginPass(i);
		
		for (size_t j = 0; j < lpMesh->vMaterial.size(); ++j)
			lpMesh->lpD3DXMesh->DrawSubset(j);

		lpEffect->EndPass();
	}
	
	lpEffect->End();

	if (RenderEnd)
		RenderEnd();
}

void ShaderRenderer::SetEffect(LPD3DXEFFECT _lpEffect)
{
	lpEffect = _lpEffect;
}