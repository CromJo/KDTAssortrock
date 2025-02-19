#pragma once

#include "../../GameInfo.h"

class CMeshManager
{
	friend class CAssetManager;

	// �ܺο����� ���� ���ϰ� ���ƾ��ϹǷ� private����
private:
	CMeshManager();
	~CMeshManager();

private:
	// unordered_map�� key�� �ߺ� ���
	// �����Ͱ� �ƴ� �Ϲݰ�ü�̱� ������ erase�ϴ��� 
	// Delete���� ���� �۾��� �� �ʿ䰡 ����. 
	// (�˾Ƽ� ���� �ɰű� ����)
	std::unordered_map<std::string, CSharedPointer<class CMesh>> mMeshMap;

public:
	bool Init();
	bool CreateMesh(const std::string& Name, 
		void* VertexData, int Size,	int Count, 
		D3D11_USAGE VertexUsage,
		D3D11_PRIMITIVE_TOPOLOGY Primitive,
		void* IndexData = nullptr, 
		int IndexSize = 0,	int IndexCount = 0, 
		DXGI_FORMAT Format = DXGI_FORMAT_UNKNOWN,
		D3D11_USAGE IndexUsage = D3D11_USAGE_DEFAULT);

	class CMesh* FindMesh(const std::string& Name);
};

