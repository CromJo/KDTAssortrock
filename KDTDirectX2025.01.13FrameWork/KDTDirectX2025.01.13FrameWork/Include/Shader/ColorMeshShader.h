#pragma once
#include "GraphicShader.h"

class CColorMeshShader : public CGraphicShader
{
	friend class CShaderManager;

protected:
	CColorMeshShader();
	virtual ~CColorMeshShader();

private:
	virtual bool Init();
};

