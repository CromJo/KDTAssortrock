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
    std::unordered_map<std::string, CSharedPointer<CMesh>>::iterator iter = mMeshMap.find(Name);
    
    if (iter == mMeshMap.end())
        return nullptr;
    
    return (CMesh*)iter->second.Get();
}

bool CMeshManager::Init()
{
    // Vertical, Horizontal, Depth�� Mesh�� �����Ѵ�
    
    // Local Position : ��ü�� ó������ ������ ��ǥ�� ���Ѵ�.
    //      ��ü�� ������ ��ǥ�� �����,
    //      �������, ������� ���� ��ġ�� ��ǥ�� ������� ����
    //      ������� �޶�����.
    // World Position : ���� ������ ù ��ǥ�� ���Ѵ�.
    
    // Shader : GPU�� ���۽����ִ� ���α׷�.
    //  HLSL�� �̿��Ͽ� Shader ���α׷��� �ۼ�.
    // Shader ����
    //  1. Vertex Shader : ����ϴ� ������ 

    // ��ȯ
    // View Space ��ȯ : ī�޶� World Space �������� ������� ��,
    //      �ڽ��� �ٶ󺸴� ������ Z+������ ��ȯ�� ����,
    //      ��� �繰�鵵 ī�޶� �̵�/ȸ���Ѹ�ŭ �̵�/ȸ�����ִ� ��ȯ ���.

    // Back Face Culling : �Ⱥ��̴� �κ��� ������� �ʰ��Ͽ� �ڿ��� �Ƴ��� ���.

    FVertexColor BoxVertex[8] =
    {
        FVertexColor(-0.5f, 0.5f, -0.5f, 1.f, 0.f, 0.f, 1.f),
        FVertexColor(0.5f, 0.5f, -0.5f, 0.f, 1.f, 0.f, 1.f),
        FVertexColor(-0.5f, -0.5f, -0.5f, 0.f, 0.f, 1.f, 1.f),
        FVertexColor(0.5f, -0.5f, -0.5f, 1.f, 1.f, 0.f, 1.f),

        FVertexColor(-0.5f, 0.5f, 0.5f, 1.f, 0.f, 1.f, 1.f),
        FVertexColor(0.5f, 0.5f, 0.5f, 0.f, 1.f, 1.f, 1.f),
        FVertexColor(-0.5f, -0.5f, 0.5f, 1.f, 1.f, 1.f, 1.f),
        FVertexColor(0.5f, -0.5f, 0.5f, 1.f, 0.f, 0.f, 1.f),
    };

    unsigned short BoxIndex[36] =
    {
        0, 1, 3, 0, 3, 2,
        1, 5, 7, 1, 7, 3,
        5, 4, 6, 5, 6, 7,
        4, 0, 2, 4, 2, 6,
        4, 5, 1, 4, 1, 0,
        2, 3, 7, 2, 7, 6
    };

    if (!(CreateMesh("Box", BoxVertex, sizeof(FVertexColor), 8, D3D11_USAGE_DEFAULT,
        D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, BoxIndex,
        sizeof(unsigned short), 36, DXGI_FORMAT_R16_UINT)))
        return false;

    FVertexColor CenterRect[4] =
    {
        FVertexColor(-0.5f, 0.5f, 0.f, 1.f, 0.f, 0.f, 1.f),
        FVertexColor(0.5f, 0.5f, 0.f, 0.f, 1.f, 0.f, 1.f),
        FVertexColor(-0.5f, -0.5f, 0.f, 0.f, 0.f, 1.f, 1.f),
        FVertexColor(0.5f, -0.5f, 0.f, 1.f, 1.f, 0.f, 1.f),
    };

    unsigned short RectIndex[6] =
    {
        0, 1, 3, 0, 3, 2,
    };

    if (!(CreateMesh("CenterRect", CenterRect, sizeof(FVertexColor), 4, D3D11_USAGE_DEFAULT,
        D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, RectIndex,
        sizeof(unsigned short), 6, DXGI_FORMAT_R16_UINT)))
        return false;

    return true;
}
