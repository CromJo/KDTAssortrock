#pragma once
#include "Vector4D.h"
#include "Vector3D.h"
#include "Vector2D.h"
#include <string>

// union : 공용체
// 메모리를 공유하는 문법. 
// 아래의 경우 int와 float의 메모리주소를 공유하여
// sizeof를 할경우 4byte의 결과만 나온다.
union Test
{
	int Num;
	float Num1;
};

__declspec(align(16)) union FMatrix
{
	// XM_ALIGNED_STRUCT(x) __declspec 
	// 래핑 구조체를 만들어준다.
	// 16 x 4 byte로 이루어진 4x4행렬이라서,
	//	16byte안의 4도 쪼개고 싶어 union으로 선언함.
	DirectX::XMMATRIX m;

	struct
	{
		float _11, _12, _13, _14;
		float _21, _22, _23, _24;
		float _31, _32, _33, _34;
		float _41, _42, _43, _44;
	};

	FVector4D v[4];

	FMatrix() 
	{
		// XMMatrixIdentity : 항등행렬을 만들어주는 함수.
		m = DirectX::XMMatrixIdentity();
	}
	FMatrix(const FMatrix& _m)
	{
		m = _m.m;
	}

	FMatrix(FMatrix&& _m) noexcept
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

	FMatrix operator * (const FMatrix& _m)	const
	{
		return FMatrix(m * _m.m);
	}

	FMatrix operator * (const DirectX::XMMATRIX& _m)	const
	{
		return FMatrix(m * _m);
	}

	void Identity()
	{
		m = DirectX::XMMatrixIdentity();
	}

	// 전치행렬 : 행과 열을 바꿔주는 기능
	void Transpose()
	{
		m = DirectX::XMMatrixTranspose(m);
	}

	void Inverse()
	{
		DirectX::XMVECTOR det = DirectX::XMMatrixDeterminant(m);

		// 행렬식이 들어간다.
		// XMVECTOR 식으로 되어있음.
		// &det의 역행렬을 구해서 m에 넣어줌.
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

	// 라디안(파이) 값으로 계산한다.
	void Rotation(const FVector3D& _v)
	{
		// 라디안 값을 넣으면 Degree값으로 변환
		//DirectX::XMConvertToDegrees();
		// Degree값을 넣으면 Radian값으로 변환
		float x = DirectX::XMConvertToRadians(_v.x);
		float y = DirectX::XMConvertToRadians(_v.y);
		float z = DirectX::XMConvertToRadians(_v.z);

		// x, y, z 회전 값을 이용해 사원수를 구한다.
		DirectX::XMVECTOR Quaternion = DirectX::XMQuaternionRotationRollPitchYaw(x, y, z);

		// 위에서 구해준 사원수를 이용해 회전행렬을 만든다.
		m = DirectX::XMMatrixRotationQuaternion(Quaternion);
		
		//DirectX::XMMatrixRotationX
	}

	void Rotation(float _x, float _y, float _z)
	{
		float x = DirectX::XMConvertToRadians(_x);
		float y = DirectX::XMConvertToRadians(_y);
		float z = DirectX::XMConvertToRadians(_z);

		// x, y, z 회전 값을 이용해 사원수를 구한다.
		DirectX::XMVECTOR Quaternion = DirectX::XMQuaternionRotationRollPitchYaw(x, y, z);

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

		m = DirectX::XMMatrixRotationY(y);
	}

	void RotationZ(float _z)
	{
		float z = DirectX::XMConvertToRadians(_z);

		m = DirectX::XMMatrixRotationZ(z);
	}

	void RotationAxis(const FVector3D& Axis, float _Angle)
	{
		float Angle = DirectX::XMConvertToRadians(_Angle);

		DirectX::XMVECTOR _Axis = DirectX::XMLoadFloat3((DirectX::XMFLOAT3*)&Axis);

		m = DirectX::XMMatrixRotationAxis(_Axis, Angle);
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

	FMatrix StaticIdentity()
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
		return DirectX::XMMatrixScaling(_v.x, _v.y, _v.z);
	}

	static FMatrix StaticScaling(float x, float y, float z)
	{
		return DirectX::XMMatrixScaling(x, y, z);
	}

	static FMatrix StaticScaling(const FVector2D& _v)
	{
		return DirectX::XMMatrixScaling(_v.x, _v.y, 1.f);
	}

	static FMatrix StaticScaling(float x, float y)
	{
		return DirectX::XMMatrixScaling(x, y, 1.f);
	}

	static FMatrix StaticRotation(const FVector3D& _v)
	{
		float x = DirectX::XMConvertToRadians(_v.x);
		float y = DirectX::XMConvertToRadians(_v.y);
		float z = DirectX::XMConvertToRadians(_v.z);

		// x, y, z 회전값을 이용하여 사원수를 구한다.
		DirectX::XMVECTOR Quaternion = DirectX::XMQuaternionRotationRollPitchYaw(x, y, z);

		// 위에서 구한 사원수(Quaternion)를 이용하여 회전행렬을 만든다.
		return DirectX::XMMatrixRotationQuaternion(Quaternion);
	}

	static FMatrix StaticRotation(float _x, float _y, float _z)
	{
		float x = DirectX::XMConvertToRadians(_x);
		float y = DirectX::XMConvertToRadians(_y);
		float z = DirectX::XMConvertToRadians(_z);

		// x, y, z의 회전값을 이용해 사원수를 구한다.
		DirectX::XMVECTOR Quaternion = DirectX::XMQuaternionRotationRollPitchYaw(x, y, z);

		// 위에서 구해준 사원수를 이용하여 회전행렬을 만들어준다.
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

		return DirectX::XMMatrixRotationY(y);
	}

	static FMatrix StaticRotationZ(float _z)
	{
		float z = DirectX::XMConvertToRadians(_z);

		return DirectX::XMMatrixRotationZ(z);
	}

	static FMatrix StaticRotationAxis(const FVector3D& _Axis, float _Angle)
	{
		float Angle = DirectX::XMConvertToRadians(_Angle);

		DirectX::XMVECTOR Axis = DirectX::XMLoadFloat3((DirectX::XMFLOAT3*)&_Axis);

		return DirectX::XMMatrixRotationAxis(Axis, Angle);
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
	4x4 * 4x4

	1x4		4x4		 
	1234	1234	= (1x1) + (2x5) + (3x9) + (4x3) = 50
			5678	= (1x2) + (2x6) + (3x0) + (4x4) = 30
			9012	= (1x3) + (2x7) + (3x1) + (4x5)	= 40
			3456	= (1x4) + (2x8) + (3x2) + (4x6) = 50 
-----------------

	1234	1234	= 
	5678 *	5678	=
	9012	9012
	3456	3456

	1000
	0100
	0010
	0001

	A행렬에 A행렬의 역행렬을 곱하면 항등행렬(단위행렬)이 나온다.

	전치행렬 : 행과 열을 바꿔준다.


	월드 행렬 구성요소
	크기, 자전, 위치(이동), 공전, 부모
	월드행렬 = 크기 행렬 * 자전행렬 * 
				이동행렬 * 공전행렬 * 부모 행렬

	크기 행렬
	x 0 0 0
	0 y 0 0
	0 0 z 0
	0 0 0 1

	짐벌락을 막기위한
	쿼터니언 방식의 개념
	X축 회전			(삼각함수의 덧셈공식을 이용해 계산.)
	1	0	0	0		
	0	cos	-sin0
	0	sin	cos	0
	0	0	0	1

	Y축 회전
	cos	0	sin	0
	0	1	0	0
	-sin0	cos	0
	0	0	0	1

	Z축 회전
	cos	-sin0	0
	sin	cos	0	0
	0	0	1	0
	0	0	0	1

	최종 회전행렬 = X축 회전 * Y축 회전 * Z축 회전

	100, 100, 0, 1 * 1	0	0	0 = 100,
					 0	cos	-sin0 
					 0	sin	cos	0
					 0	0	0	1

	이동행렬
	1 0 0 0
	0 1 0 0
	0 0 1 0
	x y z 1

		// PI = 180도
		// Radian * 180 / PI = 각도
		// 각도 * PI / 180 = Radian
*/