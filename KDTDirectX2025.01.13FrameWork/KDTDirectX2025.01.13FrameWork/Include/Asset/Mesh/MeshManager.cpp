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
    // �̸��� �̿��Ͽ� �޽��� ���´�
    CMesh* Mesh = FindMesh(Name);

    // �޽��� �̹������� �ߺ� �޽��� ������ �ǹ��ϹǷ� ���� �ߴ�.
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
