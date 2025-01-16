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
    std::unordered_map<std::string, CSharedPointer<CMesh>>::iterator iter = mMeshMap.find(Name);
    
    if (iter == mMeshMap.end())
        return nullptr;
    
    return (CMesh*)iter->second.Get();
}

bool CMeshManager::Init()
{
    // Vertical, Horizontal, Depth로 Mesh를 구성한다
    
    // Local Position : 물체가 처음으로 생성된 좌표를 말한다.
    //      물체의 가운대로 좌표를 잡는지,
    //      우측상단, 좌측상단 등의 위치로 좌표를 잡는지에 따라
    //      계산방식이 달라진다.
    // World Position : 가상 공간의 첫 좌표를 말한다.
    
    // Shader : GPU가 동작시켜주는 프로그램.
    //  HLSL을 이용하여 Shader 프로그램을 작성.
    // Shader 종류
    //  1. Vertex Shader : 출력하는 형태의 

    // 변환
    // View Space 변환 : 카메라를 World Space 기준으로 가지고온 후,
    //      자신이 바라보던 시점을 Z+값으로 변환한 다음,
    //      모든 사물들도 카메라가 이동/회전한만큼 이동/회전해주는 변환 방식.

    // Back Face Culling : 안보이는 부분을 출력하지 않게하여 자원을 아끼는 방식.

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
