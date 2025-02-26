#include "ShaderManager.h"
#include "ColorMeshShader.h"
#include "ConstantBuffer.h"

DEFINITION_SINGLE(CShaderManager)

CShaderManager::CShaderManager()
{

}

CShaderManager::~CShaderManager()
{

}

bool CShaderManager::Init()
{
	//CreateShader<CColorMeshShader>("ColorMeshVertexShader");
	CreateShader<CColorMeshShader>("ColorMeshShader");

	// 0번째 Registry를 복사
	CreateConstantBuffer("Transform",
		sizeof(FTransformCBufferInfo), 0,
		EShaderBufferType::Vertex);

	return true;
}

CShader* CShaderManager::FindShader(const std::string& Name)
{
	std::unordered_map<std::string, CSharedPointer<CShader>>::iterator iter = mShaderMap.find(Name);
	//auto iter = mShaderMap.find(Name);

	if (iter == mShaderMap.end())
		return nullptr;

	return iter->second;
}

void CShaderManager::ReleaseShader(const std::string& Name)
{
	std::unordered_map<std::string, CSharedPointer<CShader>>::iterator iter = mShaderMap.find(Name);

	if (iter != mShaderMap.end())
	{
		// 이 객체가 제거되는순간 소멸자가 호출이 되면서,
		// Release함수를 자동실행
		// 자동실행이 되는 이유는 CSharedPointer로 만들었기 때문.
		mShaderMap.erase(iter);
	}

}

bool CShaderManager::CreateConstantBuffer(const std::string& Name, int Size, int Register, int ShadowBufferType)
{
	CConstantBuffer* CBuffer = FindCBuffer(Name);

	if (CBuffer)
		return true;

	CBuffer = new CConstantBuffer;

	// 생설 실패 시
	if (!CBuffer->Init(Size, Register, ShadowBufferType))
	{
		// 동적할당 제거
		SAFE_DELETE(CBuffer);

		return false;
	}

	// 생성 성공 시
	mCBufferMap.insert(std::make_pair(Name, CBuffer));

	return true;
}

CConstantBuffer* CShaderManager::FindCBuffer(const std::string& Name)
{
	std::unordered_map<std::string, CSharedPointer<CConstantBuffer>>::iterator iter = mCBufferMap.find(Name);
	//auto iter = mShaderMap.find(Name);

	if (iter == mCBufferMap.end())
		return nullptr;

	return iter->second;
}

void CShaderManager::ReleaseCBuffer(const std::string& Name)
{
}
