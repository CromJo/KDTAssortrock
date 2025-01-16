#include "ShaderManager.h"

DEFINITION_SINGLE(CShaderManager)

CShaderManager::CShaderManager()
{

}

CShaderManager::~CShaderManager()
{

}

bool CShaderManager::Init()
{
	CreateShader<CColorMeshShader>("ColorMeshShader");

	return true;
}

CGraphicShader* CShaderManager::FindShader(const std::string& Name)
{
	std::unordered_map<std::string, CSharedPointer>::iterator iter = mShaderMap.find(Name);
	//auto iter = mShaderMap.find(Name);
	//auto iterEnd = mShaderMap.end();

	if (iter == mShaderMap.end())
		return nullptr;

	return (CShader*)
}
