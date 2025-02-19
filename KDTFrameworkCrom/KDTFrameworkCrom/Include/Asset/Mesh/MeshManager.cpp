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
    // 3D 공간의 8개의 점이있어야 3D 박스 한개 생성가능
    FVertexColor BoxVertex[8] =
    {
        FVertexColor(-0.5f, 0.5f, -0.5f, 1.f, 0.f, 0.f, 1.f),   // 0번 점
        FVertexColor(0.5f, 0.5f, -0.5f, 1.f, 0.f, 0.f, 1.f),    // 1번 점
        FVertexColor(-0.5f, -0.5f, -0.5f, 1.f, 0.f, 0.f, 1.f),  // 2번 점
        FVertexColor(0.5f, -0.5f, -0.5f, 1.f, 0.f, 0.f, 1.f),   // 3번 점

        FVertexColor(-0.5f, 0.5f, 0.5f, 1.f, 0.f, 0.f, 1.f),   // 4번 점
        FVertexColor(0.5f, 0.5f, 0.5f, 0.f, 0.f, 0.f, 1.f),    // 5번 점
        FVertexColor(-0.5f, -0.5f, 0.5f, 1.f, 0.f,  0.f, 1.f),  // 6번 점
        FVertexColor(0.5f, -0.5f, 0.5f, 1.f, 0.f, 0.f, 1.f),   // 7번 점
    };

    // 2byte는 약 65000개의 vertex 저장이 가능하다.
    // vertex 3개로 삼각형을 만들고,
    // vertex 4개로 사각형을 만들 수 있다.
    // 사각형 하나를 만들기위해서 삼각형 2개가 필요하고,
    // 삼각형 2개는 개당 3개의 Index가 필요하므로,
    // 사각형 = 삼각형 2개 = vertex 4개 = Index 6개
    // 로 말할 수 있다.
    // 최종생성물 : 3D Box (BoxVertex 8개 BoxIndex 36개)
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
        FVertexColor(-0.5f, 0.5f, 0.f, 1.f, 0.f, 0.f, 1.f),   // 0번 점
        FVertexColor(0.5f, 0.5f, 0.f, 0.f, 1.f, 0.f, 1.f),    // 1번 점
        FVertexColor(-0.5f, -0.5f, 0.f, 0.f, 0.f, 1.f, 1.f),  // 2번 점
        FVertexColor(0.5f, -0.5f, 0.f, 1.f, 1.f, 0.f, 1.f),   // 3번 점
    };

    //최종 생성물 : 2D Rect (CenterRect 4개 RectIndex 6개)
    unsigned short RectIndex[6] = { 0, 1, 3, 0, 3, 2 };
    
    if (!CreateMesh("CenterRect", CenterRect, sizeof(FVertexColor), 
        4, D3D11_USAGE_DEFAULT, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
        RectIndex, sizeof(unsigned short), 6,
        DXGI_FORMAT_R16_UINT))
        return false;

    return true;


    /*
        1. 정점하나 하나를 Vertex Shader를 거친다.
            (사각형은 정점 4개이므로, Shader가 총 4번 동작한다)
        2. Vertex Shader는
            World -> View Space -> Projection 변환을 실행한다.
            - View Space 변환
                - 화면에 표시할 영역을 표시
                - 0, 0좌표로 이동.
                - 나머지 모든 오브젝트들도 View Space가
                    이동한만큼 이동
                - 행, 렬로 이루어져있다.
        3. Hall Shader : 테슬레이션 Fector들을 만들어 패치들을
                        얼마나 디테일하게 쪼갤지에 대한 계수를 넘겨주는 역할

        4. 테슬레이션 : 카메라에서 멀리 있으면 삼각형을 줄여서 뭉뚝하게 그린다.
                        (연산을 줄여서 최적화 한다. (LOD방식)
            ※ Option Setting을 통해 개입

        5. Domain Shader : 테슬레이션 단계의 끝
                        디테일하게 쪼개진 Vertex들을 최종적으로 계산하는 단계

        6. Geometry Shader : 계산된 점들을 원하는 방식으로 조립하여 삼각형 형태로 만든다.

        7. Compute Shader : 독립적으로 이루어진 Shader (순차적으로 이뤄지지 않는다.)
                        GPU Multi Thread를 동작시킬 수 있다.
                - GPU Thread 장점
                    1. 행렬을 빠르게 계산할 수 있다.
                    2. 계산 후 C++코드에 결과를 받을 수 있다.
                        입자 계산이 필요할때 자주 쓰인다.

        8. Resterise Shader : 색을 출력하기 위한 단계
                - 도형처리 (점이나 선을 삼각형으로 조립)
                - View Port 공간으로 변환
                - Clipping (시야밖으로 나간 부분 제거)
                - 화면 공간 생성
                - 최종적으로 Pixel을 인식하고, Progment 데이터를 만듦
                - Multi Sampling 적용
           ※ Device 단계에서 Option Setting 통해 개입

        9. Pixel Shader : 색을 결정하는 단계

        10. 출력 변압기 단계를 통해 최종적으로 화면에 출력

        - Vertex Shader & Pixel Shader만으로도 화면 출력 가능
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
    // 이름으로 메쉬 받아오기
    CMesh* Mesh = FindMesh(Name);

    // 메쉬가 이미 있다면, 생성 중단
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
