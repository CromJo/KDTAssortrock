#pragma once

#include "../../GameInfo.h"

class CMeshManager
{
	friend class CAssetManager;

	// 외부에서는 생성 못하게 막아야하므로 private선언
private:
	CMeshManager();
	~CMeshManager();

private:
	// unordered_map은 key값 중복 허용
	// 포인터가 아닌 일반객체이기 때문에 erase하더라도 
	// Delete같은 해제 작업을 할 필요가 없다. 
	// (알아서 제거 될거기 떄문)
	std::unordered_map<std::string, CSharedPointer> mMeshMap;

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

