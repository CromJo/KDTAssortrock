#pragma once
#include "../../GameInfo.h"

/*
	Hash 방식
		장점 : 시간복잡도 1 (매우 빠름)
		단점 : 메모리 많이 씀
*/

class CMeshManager
{
	friend class CAssetManager;

	// private으로 하는 이유
	// 외부에서 생성자/소멸자 사용을 막기 위함.
	// 허나 AssetManager에서 모든 것을 관리하기 위해,
	// friend선언으로 CAssetManager에서는 사용가능
private:
	CMeshManager();
	~CMeshManager();

private:
	// unordered_map : key값 중복 허용안함
	// Asset을 만들어서 CSharedPointer에 넣어주면 된다.
	std::unordered_map<std::string, CSharedPointer<class CMesh>> mMeshMap;

public:
	bool CreateMesh(const std::string& Name, void* VertexData, int Size, int Count,
		D3D11_USAGE VertexUsage, D3D11_PRIMITIVE_TOPOLOGY Primitive,
		void* IndexData = nullptr, int IndexSize = 0, int IndexCount = 0,
		DXGI_FORMAT Format = DXGI_FORMAT_UNKNOWN, D3D11_USAGE IndexUsage = D3D11_USAGE_DEFAULT);

	class CMesh* FindMesh(const std::string& Name);
	
	bool Init();

};

