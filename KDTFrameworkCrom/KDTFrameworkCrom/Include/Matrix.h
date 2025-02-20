#pragma once

#include "Vector4D.h"

// union
//  - �޸� �ּҸ� �����ϴ� ���
//      Ex) float a�� int b�� ����� 
//      sizeof�� Ȯ���ϸ� 4byte�� ���´�.
//  - ����ü��� �θ���
// __declspec(align(n))
//  - ����� 16byte ������ �����ؾ��ϱ⿡ ����
//      ���ϸ� DirectX ���� ��� �Լ��� ũ���� �� .
//  
//union FMatrix
__declspec(align(16)) union FMatrix
{
    // XMMATRIX
    //  - ��ũ�� : XM_ALIGNED_STRUCT(16)�� ����Ǿ��ִ�. 
    //  - ��ũ�ξ� : __declspec(align(x)) struct�� 
    //      ����Ǿ��ִ�.
    //  - �� __declspec(align(16))�� ������ 
    //      ����ü XMMATRIX�̴�.
    //  - �޸� ������ 16byte ���ķ� �����.
    //  - simd 2 register�� �̿��� 16byte ������
    //      ����� �� �ְ� ������ش�. 
    DirectX::XMMATRIX m;

    // ������������ �� 64byte�� �ǹ��Ѵ�.
    struct
    {
        float _11, _12, _13, _14;
        float _21, _22, _23, _24;
        float _31, _32, _33, _34;
        float _41, _42, _43, _44;
    };

    // Index������ �Ǵϱ� ��� Vector������
    //  return�ϴ� ���۷����͸� ����������
    //  2���� �迭 ���·� ���� ����������.
    FVector4D v[4];

    FMatrix()
    {
        // XMMatrixIdentity : �׵� ����� ������ִ� �Լ�.
        m = DirectX::XMMatrixIdentity();
    }

    FMatrix(const FMatrix& _m)
    {
        m = _m.m;
    }

    FMatrix(FMatrix&& _m)
    {
        m = _m.m;
    }

    FMatrix(const DirectX::XMMATRIX& _m)
    {
        m = _m;
    }

    FMatrix(const FVector4D _v[4])
    { 
        memcpy(v, _v, sizeof(FVector4D) * 4);
    }

    // �ε��� ���� ���۷�����
    FVector4D& operator [] (int Index)
    {
        assert(0 <= Index && Index <= 3);

        return v[Index];
    }

    const FMatrix& operator = (const FMatrix& _m)
    {

    }

};

/*
    ���
    1. ��ȯ��Ģ�� ���� �ȵȴ�.
        - ���� : ����
        - A���� B���� ���� ���� ������ �ȴ�.
        - A��� B���� ����� ���´�.
    2. ������� : 4x4 ũ��� �밢��(\)�������� 1�� ������ ��
            - �׵�����̶�� �Ѵ�.
            - ��Ŀ����� 1�� ���� ����
            - A��� * ������� = A���
            - ��� �� �����ϰ� ��ȯ��Ģ�� ������.
            - A��� * ����� = ������� �̴�.
*/