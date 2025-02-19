#pragma once
#include "GraphicShader.h"

class CColorMeshShader :
    public CGraphicShader
{
    friend CShaderManager;

protected:
    CColorMeshShader();
    virtual ~CColorMeshShader();

public:
    virtual bool Init();

};

