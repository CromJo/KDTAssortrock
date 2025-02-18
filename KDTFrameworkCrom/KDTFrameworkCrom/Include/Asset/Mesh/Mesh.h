#pragma once

#include "../Asset.h"

// Index Buffer와 Material 
struct FMeshSlot
{
    FIndexBuffer IndexBuffer;
};


// 상속받는 static mesh class를 이용해서 작업하기 위해
// 추상 클래스로 만듦
class CMesh abstract :
    public CAsset
{
public:
    CMesh();
    virtual ~CMesh();

protected:
    FVertexBuffer mVertexBuffer;
    std::vector<FMeshSlot*> mMeshSlot;
    D3D11_PRIMITIVE_TOPOLOGY mPrimitive;

public:
    /*
        외부로부터 Vertex 및 Index Buffer를
        무엇이든 가져오기 위해 void*으로 선언 (역참조 불가)
        D3D11_USAGE
            - Default   : 비디오 메모리에 만든다. 
                (Lock 건 후 데이터 수정후 Unlock))
            - Immutable : 비디오 메모리에 만든다.
                (Lock을 걸어버린다. (렌더링 효율이 좋다))
            - Dynamic   : 비디오 메모리에 만들고 저장한다.
                1. (시스템 메모리에 복사하여 만든다.)
                2. (데이터 갱신 시 시스템 메모리의 데이터를 갱신.)
                (빈번한 데이터 갱신 필요 Buffer에 효율성 좋음)
            - Staging   : 시스템 메모리에만 만든다.
                (갱신 전용 Buffer)
                (출력 용이 아니다.)
    
        D3D_PRIMITIVE_TOPOLOGY
            - PointList : 그려내는 도형 지정.
                1. Vertex 100개 시 점 100개 생성
            - LineList  : 시작과 끝을 지정하여 그린다.
            - LineStrip : 선을 이어서 그린다.
            - TriangleList  : 점 3개씩 이어서 삼각형 출력.
            - TriangleStrip : 남은 점에 추가적으로 삼각형 도형을 만든다.
    */
    virtual bool CreateMesh(void* VertexData, int Size,
        int Count, D3D11_USAGE VertexUsage,
        D3D11_PRIMITIVE_TOPOLOGY Primitive,
        void* IndexData = nullptr, int IndexSize = 0,
        int IndexCount = 0, DXGI_FORMAT Format = DXGI_FORMAT_UNKNOWN,
        D3D11_USAGE IndexUsage = D3D11_USAGE_DEFAULT);

    bool CreateBuffer(ID3D11Buffer** Buffer,
        D3D11_BIND_FLAG Flag, void* Data,
        int Size, int Count, D3D11_USAGE Usage);

};