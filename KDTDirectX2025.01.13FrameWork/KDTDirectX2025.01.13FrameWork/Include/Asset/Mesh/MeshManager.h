#pragma once
#include "../../GameInfo.h"

/*
	Hash ���
		���� : �ð����⵵ 1 (�ſ� ����)
		���� : �޸� ���� ��
*/

class CMeshManager
{
	friend class CAssetManager;

	// private���� �ϴ� ����
	// �ܺο��� ������/�Ҹ��� ����� ���� ����.
	// �㳪 AssetManager���� ��� ���� �����ϱ� ����,
	// friend�������� CAssetManager������ ��밡��
private:
	CMeshManager();
	~CMeshManager();

private:
	// unordered_map : key�� �ߺ� ������
	// Asset�� ���� CSharedPointer�� �־��ָ� �ȴ�.
	std::unordered_map<std::string, CSharedPointer<class CMesh>> mMeshMap;

public:
	bool CreateMesh(const std::string& Name, void* VertexData, int Size, int Count,
		D3D11_USAGE VertexUsage, D3D11_PRIMITIVE_TOPOLOGY Primitive,
		void* IndexData = nullptr, int IndexSize = 0, int IndexCount = 0,
		DXGI_FORMAT Format = DXGI_FORMAT_UNKNOWN, D3D11_USAGE IndexUsage = D3D11_USAGE_DEFAULT);

	class CMesh* FindMesh(const std::string& Name);
	
	bool Init();

};

