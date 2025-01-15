#include "MeshManager.h"
#include "StaticMesh.h"

CMeshManager::CMeshManager()
{
}

CMeshManager::~CMeshManager()
{
}

bool CMeshManager::CreateMesh(const std::string& Name, void* VertexData, int Size, int Count, D3D11_USAGE VertexUsage, D3D11_PRIMITIVE_TOPOLOGY Primitive, void* IndexData, int IndexSize, int IndexCount, DXGI_FORMAT Format, D3D11_USAGE IndexUsage)
{
    // 이름을 이용하여 메쉬를 얻어온다
    CMesh* Mesh = FindMesh(Name);

    // 메쉬가 이미있으면 중복 메쉬가 있음을 의미하므로 생성 중단.
    if (Mesh)
        return true;

    Mesh = new CStaticMesh;
    if (!Mesh->CreateMesh(VertexData, Size, Count, VertexUsage, Primitive, IndexData, IndexSize, IndexCount, Format, IndexUsage))
    {
        SAFE_DELETE(Mesh);

        return false;
    }

    mMeshMap.insert(std::make_pair(Name, Mesh));

    return true;
}

CMesh* CMeshManager::FindMesh(const std::string& Name)
{
    std::unordered_map<std::string, CSharedPointer>::iterator iter = mMeshMap.find(Name);
    
    if (iter == mMeshMap.end())
        return nullptr;
    
    return (CMesh*)iter->second.Get();
}
