#pragma once

#include "Shader.h"

class ComputeShader :
    public CShader
{
    friend class CShaderManager;

protected:
    ComputeShader();
    virtual ~ComputeShader();

public:
    virtual bool Init();
    virtual void SetShader() final;
};

