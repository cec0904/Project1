#pragma once
#include "Shader.h"
class CComputeShader :
	public CShader
{
	friend class CShaderManager;

protected:
	CComputeShader();
	virtual ~CComputeShader();

public:
	virtual bool Init() override;

	virtual void SetShader() final;

};

