#pragma once

#include "Vector4D.h"
#include "Vector3D.h"
#include "Vector2D.h"
#include <string>


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
        m = _m.m;
        return *this;
    }
    
    const FMatrix& operator = (const DirectX::XMMATRIX& _m)
    {
        m = _m;
        return *this;
    }
    
    const FMatrix& operator = (const FVector4D _v[4])
    {
        memcpy(v, _v, sizeof(FVector4D) * 4);
        return *this;
    }

    FMatrix operator * (const FMatrix& _m) const
    {
        return FMatrix(m * _m.m);
    }
    
    FMatrix operator * (const DirectX::XMMATRIX& _m) const
    {
        return FMatrix(m * _m);
    }
    // 단위 행렬로 만들어주는 기능
    void Identity()
    {
        m = DirectX::XMMatrixIdentity();
    }

    // 어떤 행렬의 전치행렬을 구해주는 기능. 
    void Transpose()
    {
        m = DirectX::XMMatrixTranspose(m);
    }

    // 역행렬을 구해주는 기능.
    void Inverse()
    {
        DirectX::XMVECTOR det = DirectX::XMMatrixDeterminant(m);
        m = DirectX::XMMatrixInverse(&det, m);
    }

    void Scaling(const FVector3D& _v)
    {
        m = DirectX::XMMatrixScaling(_v.x, _v.y, _v.z);
    }

    void Scaling(float x, float y, float z)
    {
        m = DirectX::XMMatrixScaling(x, y, z);
    }

    void Scaling(const FVector2D& _v)
    {
        m = DirectX::XMMatrixScaling(_v.x, _v.y, 1.f);
    }

    void Scaling(float x, float y)
    {
        m = DirectX::XMMatrixScaling(x, y, 1.f);
    }

    // 회전에 대한 값을 받아서 넣어주는 기능
    void Rotation(const FVector3D& _v)
    {
        // 라디안으로 파이는 180도를 의미
        // 각도 = Radian * 180 / Pi
        // 라디안 = Angle * Pi / 180

        float x = DirectX::XMConvertToDegrees(_v.x);
        float y = DirectX::XMConvertToRadians(_v.y);
        float z = DirectX::XMConvertToRadians(_v.z);
    
        // x, y, z 회전값을 이용해 사원수를 구한다.
        DirectX::XMVECTOR Quaternion =
            DirectX::XMQuaternionRotationRollPitchYaw(x, y, z);
        
        // 위에서 구해준 사원수를 이용해 회전행렬을 만든다.
        m = DirectX::XMMatrixRotationQuaternion(Quaternion);

        
    }

    void Rotation(float _x, float _y, float _z)
    {
        float x = DirectX::XMConvertToDegrees(_x);
        float y = DirectX::XMConvertToRadians(_y);
        float z = DirectX::XMConvertToRadians(_z);

        // x, y, z 회전값을 이용해 사원수를 구한다.
        DirectX::XMVECTOR Quaternion =
            DirectX::XMQuaternionRotationRollPitchYaw(x, y, z);

        // 위에서 구해준 사원수를 이용해 회전행렬을 만든다.
        m = DirectX::XMMatrixRotationQuaternion(Quaternion);

    }

    void RotationX(float _x)
    {
        float x = DirectX::XMConvertToRadians(_x);

        m = DirectX::XMMatrixRotationX(x);
    }

    void RotationY(float _y)
    {
        float y = DirectX::XMConvertToRadians(_y);

        m = DirectX::XMMatrixRotationX(y);
    }

    void RotationZ(float _z)
    {
        float z = DirectX::XMConvertToRadians(_z);

        m = DirectX::XMMatrixRotationX(z);
    }

    void RotationAxis(const FVector3D& Axis, float Angle)
    {
        float _Angle = DirectX::XMConvertToRadians(Angle);
        
        // XMFLOAT3는 기능이 부실하다.
        DirectX::XMVECTOR _Axis = 
            DirectX::XMLoadFloat3((DirectX::XMFLOAT3*)&Axis);

        m = DirectX::XMMatrixRotationAxis(_Axis, _Angle);
    }

    void Translation(const FVector3D& _v)
    {
        m = DirectX::XMMatrixTranslation(_v.x, _v.y, _v.z);
    }

    void Translation(float x, float y, float z)
    {
        m = DirectX::XMMatrixTranslation(x, y, z);
    }

    void Translation(const FVector2D& _v)
    {
        m = DirectX::XMMatrixTranslation(_v.x, _v.y, 0.f);
    }

    void Translation(float x, float y)
    {
        m = DirectX::XMMatrixTranslation(x, y, 0.f);
    }

    static FMatrix StaticIdentity()
    {
        return DirectX::XMMatrixIdentity();
    }

    static FMatrix StaticTranspose(const FMatrix& _m)
    {
        return DirectX::XMMatrixTranspose(_m.m);
    }
    
    static FMatrix StaticInverse(const FMatrix& _m)
    {
        DirectX::XMVECTOR det = DirectX::XMMatrixDeterminant(_m.m);
        
        return DirectX::XMMatrixInverse(&det, _m.m);
    }


    static FMatrix StaticScaling(const FVector3D& _v)
    {
        return  DirectX::XMMatrixScaling(_v.x, _v.y, _v.z);
    }

    static FMatrix StaticScaling(float x, float y, float z)
    {
        return  DirectX::XMMatrixScaling(x, y, z);
    }

    static FMatrix StaticScaling(const FVector2D& _v)
    {
        return  DirectX::XMMatrixScaling(_v.x, _v.y, 1.f);
    }

    static FMatrix StaticScaling(float x, float y)
    {
        return  DirectX::XMMatrixScaling(x, y, 1.f);
    }

    // 회전에 대한 값을 받아서 넣어주는 기능
    static FMatrix StaticRotation(const FVector3D& _v)
    {
        // 라디안으로 파이는 180도를 의미
        // 각도 = Radian * 180 / Pi
        // 라디안 = Angle * Pi / 180

        float x = DirectX::XMConvertToDegrees(_v.x);
        float y = DirectX::XMConvertToRadians(_v.y);
        float z = DirectX::XMConvertToRadians(_v.z);

        // x, y, z 회전값을 이용해 사원수를 구한다.
        DirectX::XMVECTOR Quaternion =
            DirectX::XMQuaternionRotationRollPitchYaw(x, y, z);

        // 위에서 구해준 사원수를 이용해 회전행렬을 만든다.
        return DirectX::XMMatrixRotationQuaternion(Quaternion);
    }

    static FMatrix StaticRotation(float _x, float _y, float _z)
    {
        float x = DirectX::XMConvertToDegrees(_x);
        float y = DirectX::XMConvertToRadians(_y);
        float z = DirectX::XMConvertToRadians(_z);

        // x, y, z 회전값을 이용해 사원수를 구한다.
        DirectX::XMVECTOR Quaternion =
            DirectX::XMQuaternionRotationRollPitchYaw(x, y, z);

        // 위에서 구해준 사원수를 이용해 회전행렬을 만든다.
        return DirectX::XMMatrixRotationQuaternion(Quaternion);

    }

    static FMatrix StaticRotationX(float _x)
    {
        float x = DirectX::XMConvertToRadians(_x);

        return DirectX::XMMatrixRotationX(x);
    }

    static FMatrix StaticRotationY(float _y)
    {
        float y = DirectX::XMConvertToRadians(_y);

        return DirectX::XMMatrixRotationX(y);
    }

    static FMatrix StaticRotationZ(float _z)
    {
        float z = DirectX::XMConvertToRadians(_z);

        return DirectX::XMMatrixRotationX(z);
    }

    static FMatrix StaticRotationAxis(const FVector3D& Axis, float Angle)
    {
        float _Angle = DirectX::XMConvertToRadians(Angle);

        // XMFLOAT3는 기능이 부실하다.
        DirectX::XMVECTOR _Axis =
            DirectX::XMLoadFloat3((DirectX::XMFLOAT3*)&Axis);

        return DirectX::XMMatrixRotationAxis(_Axis, _Angle);
    }

    static FMatrix StaticTranslation(const FVector3D& _v)
    {
        return DirectX::XMMatrixTranslation(_v.x, _v.y, _v.z);
    }

    static FMatrix StaticTranslation(float x, float y, float z)
    {
        return DirectX::XMMatrixTranslation(x, y, z);
    }

    static FMatrix StaticTranslation(const FVector2D& _v)
    {
        return DirectX::XMMatrixTranslation(_v.x, _v.y, 0.f);
    }

    static FMatrix StaticTranslation(float x, float y)
    {
        return DirectX::XMMatrixTranslation(x, y, 0.f);
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

    3. 전치행렬 : 행과 열을 바꿔준다.
        1 2 3 4     1 5 9 3
        5 6 7 8 ->  2 6 0 4
        9 0 1 2     3 7 1 5
        3 4 5 6     4 8 2 6

    4. 월드 행렬 구성요소
    크기, 자전, 위치(이동), 공전, 부모
    월드행렬 = 크기행렬 * 자전행렬 * 
                이동행렬 * 공전행렬 * 부모행렬
    
    x 0 0 0
    0 y 0 0
    0 0 z 0
    0 0 0 1

    x  y   z  w (w는 강제로 1로 대입함)
    1, 1 , 0, 1 * 100   0   0   0   = 100, 100, 0
                  0     100 0   0    
                  0     0   100 0
                  0     0   0   1

   -1, 1 , 0, 1 * 100   0   0   0   = -100, 100, 0
                  0     100 0   0    
                  0     0   100 0
                  0     0   0   1

    X축 회전 키워드 검색 ㄱ
        - 2D 회전 행렬
        - 3D 회전 행렬

    Y축 회전

    최종 회전행렬 = X축 * Y축 * Z축 (회전행렬들)

*/