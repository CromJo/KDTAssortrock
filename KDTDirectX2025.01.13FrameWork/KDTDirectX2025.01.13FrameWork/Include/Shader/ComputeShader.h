#pragma once
#include "Shader.h"

class CComputeShader : public CShader
{
	friend class CShaderManager;

protected:
	CComputeShader();
	virtual ~CComputeShader();

public:
	// 순수가상함수 : 무조건적인 자식에서 재정의 요청기능
	virtual bool Init();
	virtual void SetShader() final;
};

