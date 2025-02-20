#pragma once

#include "Vector4D.h"

// union
//  - 메모리 주소를 공유하는 기능
//      Ex) float a와 int b를 선언시 
//      sizeof로 확인하면 4byte가 나온다.
//  - 공유체라고도 부른다
// __declspec(align(n))
//  - 행렬은 16byte 연산이 가능해야하기에 선언
//      안하면 DirectX 지원 행렬 함수가 크러쉬 남 .
//  
//union FMatrix
__declspec(align(16)) union FMatrix
{
    // XMMATRIX
    //  - 매크로 : XM_ALIGNED_STRUCT(16)이 선언되어있다. 
    //  - 매크로안 : __declspec(align(x)) struct가 
    //      선언되어있다.
    //  - 즉 __declspec(align(16))을 선언한 
    //      구조체 XMMATRIX이다.
    //  - 메모리 정렬을 16byte 정렬로 만든다.
    //  - simd 2 register를 이용한 16byte 연산을
    //      사용할 수 있게 만들어준다. 
    DirectX::XMMATRIX m;

    // 나뉘어져있을 뿐 64byte를 의미한다.
    struct
    {
        float _11, _12, _13, _14;
        float _21, _22, _23, _24;
        float _31, _32, _33, _34;
        float _41, _42, _43, _44;
    };

    // Index접근이 되니까 몇번 Vector인지를
    //  return하는 오퍼레이터를 만들어놓으면
    //  2차원 배열 형태로 접근 가능해진다.
    FVector4D v[4];

    FMatrix()
    {
        // XMMatrixIdentity : 항등 행렬을 만들어주는 함수.
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

    // 인덱스 접근 오퍼레이터
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
    행렬
    1. 교환법칙이 성립 안된다.
        - 연산 : 곱셈
        - A열과 B행이 같을 때만 연산이 된다.
        - A행과 B열이 결과로 나온다.
    2. 단위행렬 : 4x4 크기로 대각선(\)방향으로 1이 나오는 수
            - 항등행렬이라고도 한다.
            - 행렬에서의 1과 같은 역할
            - A행렬 * 단위행렬 = A행렬
            - 행렬 중 유일하게 교환법칙이 성립함.
            - A행렬 * 역행렬 = 단위행렬 이다.
*/