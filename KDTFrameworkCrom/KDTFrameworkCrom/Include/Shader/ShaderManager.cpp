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

	// 0��° Registry�� ����
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
		// �� ��ü�� ���ŵǴ¼��� �Ҹ��ڰ� ȣ���� �Ǹ鼭,
		// Release�Լ��� �ڵ�����
		// �ڵ������� �Ǵ� ������ CSharedPointer�� ������� ����.
		mShaderMap.erase(iter);
	}

}

bool CShaderManager::CreateConstantBuffer(const std::string& Name, int Size, int Register, int ShadowBufferType)
{
	CConstantBuffer* CBuffer = FindCBuffer(Name);

	if (CBuffer)
		return true;

	CBuffer = new CConstantBuffer;

	// ���� ���� ��
	if (!CBuffer->Init(Size, Register, ShadowBufferType))
	{
		// �����Ҵ� ����
		SAFE_DELETE(CBuffer);

		return false;
	}

	// ���� ���� ��
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
