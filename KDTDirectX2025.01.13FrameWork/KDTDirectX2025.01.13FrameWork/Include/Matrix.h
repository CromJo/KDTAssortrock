#pragma once
#include "Vector4D.h"

// union : ����ü
// �޸𸮸� �����ϴ� ����. 
// �Ʒ��� ��� int�� float�� �޸��ּҸ� �����Ͽ�
// sizeof�� �Ұ�� 4byte�� ����� ���´�.
union Test
{
	int Num;
	float Num1;
};

__declspec(align(16)) union FMatrix
{
	// XM_ALIGNED_STRUCT(x) __declspec 
	// ���� ����ü�� ������ش�.
	// 16 x 4 byte�� �̷���� 4x4����̶�,
	//	16byte���� 4�� �ɰ��� �;� union���� ������.
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
		// XMMatrixIdentity : �׵������ ������ִ� �Լ�.
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

	// ��ġ��� : ��� ���� �ٲ��ִ� ���
	void Transpose()
	{
		m = DirectX::XMMatrixTranspose(m);
	}

	void Inverse()
	{
		DirectX::XMVECTOR det = DirectX::XMMatrixDeterminant(m);

		// ��Ľ��� ����.
		// XMVECTOR ������ �Ǿ�����.
		// &det�� ������� ���ؼ� m�� �־���.
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

	// ����(����) ������ ����Ѵ�.
	void Rotation(const FVector3D& _v)
	{
		// ���� ���� ������ Degree������ ��ȯ
		//DirectX::XMConvertToDegrees();
		// Degree���� ������ Radian������ ��ȯ
		float x = DirectX::XMConvertToRadians(_v.x);
		float y = DirectX::XMConvertToRadians(_v.y);
		float z = DirectX::XMConvertToRadians(_v.z);

		// x, y, z ȸ�� ���� �̿��� ������� ���Ѵ�.
		DirectX::XMVECTOR Quaternion = DirectX::XMQuaternionRotationRollPitchYaw(x, y, z);

		// ������ ������ ������� �̿��� ȸ������� �����.
		m = DirectX::XMMatrixRotationQuaternion(Quaternion);
		
		//DirectX::XMMatrixRotationX
	}

	void Rotation(float _x, float _y, float _z)
	{
		float x = DirectX::XMConvertToRadians(_x);
		float y = DirectX::XMConvertToRadians(_y);
		float z = DirectX::XMConvertToRadians(_z);

		// x, y, z ȸ�� ���� �̿��� ������� ���Ѵ�.
		DirectX::XMVECTOR Quaternion = DirectX::XMQuaternionRotationRollPitchYaw(x, y, z);

		// ������ ������ ������� �̿��� ȸ������� �����.
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

		// x, y, z ȸ������ �̿��Ͽ� ������� ���Ѵ�.
		DirectX::XMVECTOR Quaternion = DirectX::XMQuaternionRotationRollPitchYaw(x, y, z);

		// ������ ���� �����(Quaternion)�� �̿��Ͽ� ȸ������� �����.
		return DirectX::XMMatrixRotationQuaternion(Quaternion);
	}

	static FMatrix StaticRotation(float _x, float _y, float _z)
	{
		float x = DirectX::XMConvertToRadians(_x);
		float y = DirectX::XMConvertToRadians(_y);
		float z = DirectX::XMConvertToRadians(_z);

		// x, y, z�� ȸ������ �̿��� ������� ���Ѵ�.
		DirectX::XMVECTOR Quaternion = DirectX::XMQuaternionRotationRollPitchYaw(x, y, z);

		// ������ ������ ������� �̿��Ͽ� ȸ������� ������ش�.
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

	A��Ŀ� A����� ������� ���ϸ� �׵����(�������)�� ���´�.

	��ġ��� : ��� ���� �ٲ��ش�.


	���� ��� �������
	ũ��, ����, ��ġ(�̵�), ����, �θ�
	������� = ũ�� ��� * ������� * 
				�̵���� * ������� * �θ� ���

	ũ�� ���
	x 0 0 0
	0 y 0 0
	0 0 z 0
	0 0 0 1

	�������� ��������
	���ʹϾ� ����� ����
	X�� ȸ��			(�ﰢ�Լ��� ���������� �̿��� ���.)
	1	0	0	0		
	0	cos	-sin0
	0	sin	cos	0
	0	0	0	1

	Y�� ȸ��
	cos	0	sin	0
	0	1	0	0
	-sin0	cos	0
	0	0	0	1

	Z�� ȸ��
	cos	-sin0	0
	sin	cos	0	0
	0	0	1	0
	0	0	0	1

	���� ȸ����� = X�� ȸ�� * Y�� ȸ�� * Z�� ȸ��

	100, 100, 0, 1 * 1	0	0	0 = 100,
					 0	cos	-sin0 
					 0	sin	cos	0
					 0	0	0	1

	�̵����
	1 0 0 0
	0 1 0 0
	0 0 1 0
	x y z 1

		// PI = 180��
		// Radian * 180 / PI = ����
		// ���� * PI / 180 = Radian
*/