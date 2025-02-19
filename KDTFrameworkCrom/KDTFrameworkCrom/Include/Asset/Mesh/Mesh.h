#pragma once

#include "../Asset.h"

// Index Buffer�� Material 
struct FMeshSlot
{
    FIndexBuffer IndexBuffer;
};


// ��ӹ޴� static mesh class�� �̿��ؼ� �۾��ϱ� ����
// �߻� Ŭ������ ����
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
        �ܺηκ��� Vertex �� Index Buffer��
        �����̵� �������� ���� void*���� ���� (������ �Ұ�)
        D3D11_USAGE
            - Default   : ���� �޸𸮿� �����. 
                (Lock �� �� ������ ������ Unlock))
            - Immutable : ���� �޸𸮿� �����.
                (Lock�� �ɾ������. (������ ȿ���� ����))
            - Dynamic   : ���� �޸𸮿� ����� �����Ѵ�.
                1. (�ý��� �޸𸮿� �����Ͽ� �����.)
                2. (������ ���� �� �ý��� �޸��� �����͸� ����.)
                (����� ������ ���� �ʿ� Buffer�� ȿ���� ����)
            - Staging   : �ý��� �޸𸮿��� �����.
                (���� ���� Buffer)
                (��� ���� �ƴϴ�.)
    
        D3D_PRIMITIVE_TOPOLOGY
            - PointList : �׷����� ���� ����.
                1. Vertex 100�� �� �� 100�� ����
            - LineList  : ���۰� ���� �����Ͽ� �׸���.
            - LineStrip : ���� �̾ �׸���.
            - TriangleList  : �� 3���� �̾ �ﰢ�� ���.
            - TriangleStrip : ���� ���� �߰������� �ﰢ�� ������ �����.
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

public:
    void Render();

};