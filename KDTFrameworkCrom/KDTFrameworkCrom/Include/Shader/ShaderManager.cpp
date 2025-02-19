#include "ShaderManager.h"
#include "ColorMeshShader.h"

DEFINITION_SINGLE(CShaderManager)

CShaderManager::CShaderManager()
{

}

CShaderManager::~CShaderManager()
{

}

bool CShaderManager::Init()
{
	CreateShader<CColorMeshShader>("ColorMeshVertexShader");

	return true;
}

CShader* CShaderManager::FindShader(const std::string& Name)
{
	std::unordered_map<std::string, CSharedPointer<CShader>>::iterator iter = mShaderMap.find(Name);
	//auto iter = mShaderMap.find(Name);

	if (iter == mShaderMap.end())
		return nullptr;

	return (CShader*)iter->second.Get();
}
