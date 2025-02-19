#include "MeshManager.h"
#include "StaticMesh.h"

CMeshManager::CMeshManager()
{
}

CMeshManager::~CMeshManager()
{
}

bool CMeshManager::Init()
{
    // 3D ������ 8���� �����־�� 3D �ڽ� �Ѱ� ��������
    FVertexColor BoxVertex[8] =
    {
        FVertexColor(-0.5f, 0.5f, -0.5f, 1.f, 0.f, 0.f, 1.f),   // 0�� ��
        FVertexColor(0.5f, 0.5f, -0.5f, 1.f, 0.f, 0.f, 1.f),    // 1�� ��
        FVertexColor(-0.5f, -0.5f, -0.5f, 1.f, 0.f, 0.f, 1.f),  // 2�� ��
        FVertexColor(0.5f, -0.5f, -0.5f, 1.f, 0.f, 0.f, 1.f),   // 3�� ��

        FVertexColor(-0.5f, 0.5f, 0.5f, 1.f, 0.f, 0.f, 1.f),   // 4�� ��
        FVertexColor(0.5f, 0.5f, 0.5f, 0.f, 0.f, 0.f, 1.f),    // 5�� ��
        FVertexColor(-0.5f, -0.5f, 0.5f, 1.f, 0.f,  0.f, 1.f),  // 6�� ��
        FVertexColor(0.5f, -0.5f, 0.5f, 1.f, 0.f, 0.f, 1.f),   // 7�� ��
    };

    // 2byte�� �� 65000���� vertex ������ �����ϴ�.
    // vertex 3���� �ﰢ���� �����,
    // vertex 4���� �簢���� ���� �� �ִ�.
    // �簢�� �ϳ��� ��������ؼ� �ﰢ�� 2���� �ʿ��ϰ�,
    // �ﰢ�� 2���� ���� 3���� Index�� �ʿ��ϹǷ�,
    // �簢�� = �ﰢ�� 2�� = vertex 4�� = Index 6��
    // �� ���� �� �ִ�.
    // ���������� : 3D Box (BoxVertex 8�� BoxIndex 36��)
    unsigned short BoxIndex[36] =
    {
        0, 1, 3, 0, 3, 2,
        1, 5, 7, 1, 7, 3,
        5, 4, 6, 5, 6, 7,
        4, 0, 2, 4, 2, 6,
        4, 5, 1, 4, 1, 0,
        2, 3, 7, 2, 7, 6
    };

    if (!CreateMesh("Box", BoxVertex, sizeof(FVertexColor), 8, D3D11_USAGE_DEFAULT,
        D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
        BoxIndex, sizeof(unsigned short), 36,
        DXGI_FORMAT_R16_UINT))
        return false;


    FVertexColor CenterRect[4] =
    {
        FVertexColor(-0.5f, 0.5f, 0.f, 1.f, 0.f, 0.f, 1.f),   // 0�� ��
        FVertexColor(0.5f, 0.5f, 0.f, 0.f, 1.f, 0.f, 1.f),    // 1�� ��
        FVertexColor(-0.5f, -0.5f, 0.f, 0.f, 0.f, 1.f, 1.f),  // 2�� ��
        FVertexColor(0.5f, -0.5f, 0.f, 1.f, 1.f, 0.f, 1.f),   // 3�� ��
    };

    //���� ������ : 2D Rect (CenterRect 4�� RectIndex 6��)
    unsigned short RectIndex[6] = { 0, 1, 3, 0, 3, 2 };
    
    if (!CreateMesh("CenterRect", CenterRect, sizeof(FVertexColor), 
        4, D3D11_USAGE_DEFAULT, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
        RectIndex, sizeof(unsigned short), 6,
        DXGI_FORMAT_R16_UINT))
        return false;

    return true;


    /*
        1. �����ϳ� �ϳ��� Vertex Shader�� ��ģ��.
            (�簢���� ���� 4���̹Ƿ�, Shader�� �� 4�� �����Ѵ�)
        2. Vertex Shader��
            World -> View Space -> Projection ��ȯ�� �����Ѵ�.
            - View Space ��ȯ
                - ȭ�鿡 ǥ���� ������ ǥ��
                - 0, 0��ǥ�� �̵�.
                - ������ ��� ������Ʈ�鵵 View Space��
                    �̵��Ѹ�ŭ �̵�
                - ��, �ķ� �̷�����ִ�.
        3. Hall Shader : �׽����̼� Fector���� ����� ��ġ����
                        �󸶳� �������ϰ� �ɰ����� ���� ����� �Ѱ��ִ� ����

        4. �׽����̼� : ī�޶󿡼� �ָ� ������ �ﰢ���� �ٿ��� �����ϰ� �׸���.
                        (������ �ٿ��� ����ȭ �Ѵ�. (LOD���)
            �� Option Setting�� ���� ����

        5. Domain Shader : �׽����̼� �ܰ��� ��
                        �������ϰ� �ɰ��� Vertex���� ���������� ����ϴ� �ܰ�

        6. Geometry Shader : ���� ������ ���ϴ� ������� �����Ͽ� �ﰢ�� ���·� �����.

        7. Compute Shader : ���������� �̷���� Shader (���������� �̷����� �ʴ´�.)
                        GPU Multi Thread�� ���۽�ų �� �ִ�.
                - GPU Thread ����
                    1. ����� ������ ����� �� �ִ�.
                    2. ��� �� C++�ڵ忡 ����� ���� �� �ִ�.
                        ���� ����� �ʿ��Ҷ� ���� ���δ�.

        8. Resterise Shader : ���� ����ϱ� ���� �ܰ�
                - ����ó�� (���̳� ���� �ﰢ������ ����)
                - View Port �������� ��ȯ
                - Clipping (�þ߹����� ���� �κ� ����)
                - ȭ�� ���� ����
                - ���������� Pixel�� �ν��ϰ�, Progment �����͸� ����
                - Multi Sampling ����
           �� Device �ܰ迡�� Option Setting ���� ����

        9. Pixel Shader : ���� �����ϴ� �ܰ�

        10. ��� ���б� �ܰ踦 ���� ���������� ȭ�鿡 ���

        - Vertex Shader & Pixel Shader�����ε� ȭ�� ��� ����
    */

} 

bool CMeshManager::CreateMesh(const std::string& Name,
    void* VertexData, int Size, int Count,
    D3D11_USAGE VertexUsage,
    D3D11_PRIMITIVE_TOPOLOGY Primitive,
    void* IndexData, int IndexSize,
    int IndexCount, DXGI_FORMAT Format,
    D3D11_USAGE IndexUsage)
{
    // �̸����� �޽� �޾ƿ���
    CMesh* Mesh = FindMesh(Name);

    // �޽��� �̹� �ִٸ�, ���� �ߴ�
    if (Mesh)
        return true;

    Mesh = new CStaticMesh;

    if(!Mesh->CreateMesh(VertexData, Size, Count, VertexUsage,
        Primitive, IndexData, IndexSize, IndexCount, Format,
        IndexUsage))
    {
        SAFE_DELETE(Mesh);
        return false;
    }

    mMeshMap.insert(std::make_pair(Name, Mesh));
 
    return true;
}

CMesh* CMeshManager::FindMesh(const std::string& Name)
{
    std::unordered_map<std::string, CSharedPointer<CMesh>>::iterator 
        iter = mMeshMap.find(Name);

    if (iter == mMeshMap.end())
        return nullptr;

    return (CMesh*)iter->second.Get();
}
