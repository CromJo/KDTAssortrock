#pragma once

#include <math.h>

// ����ü ����
struct FVector3D
{
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;

	// �⺻ ������
	FVector3D()
	{
	}

	// �Ű����� ���� �޾� ���� �������ִ� ������
	FVector3D(float _x, float _y, float _z) :
		x(_x),
		y(_y),
		z(_z)
	{

	}

	// ���� ����
	FVector3D(const FVector3D& v) :
		x(v.x),
		y(v.y),
		z(v.z)
	{

	}

	// �̵� ������
	FVector3D(FVector3D&& v) :
		x(v.x),
		y(v.y),
		z(v.z)
	{
	}

#pragma region ���Կ�����
	const FVector3D& operator = (const FVector3D& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	const FVector3D& operator = (float value)
	{
		x = value;
		y = value;
		z = value;
		return *this;
	}

	const FVector3D& operator = (double value)
	{
		x = (float)value;
		y = (float)value;
		z = (float)value;
		return *this;
	}

	const FVector3D& operator = (int value)
	{
		x = (float)value;
		y = (float)value;
		z = (float)value;
		return *this;
	}

#pragma endregion ���Կ�����
#pragma region ����������
	// const�� �������� :
	// 0���� ��������� ���� ������ ���� ����,
	// const�� ������ �����ϱ� �����̴�.
	FVector3D operator + (const FVector3D& v) const
	{
		FVector3D result;
		result.x = x + v.x;
		result.y = y + v.y;
		result.z = z + v.z;
		return result;
	}

	FVector3D operator + (float value) const
	{
		FVector3D result;
		result.x = x + value;
		result.y = y + value;
		result.z = z + value;
		return result;
	}

	FVector3D operator + (double value) const
	{
		FVector3D result;
		result.x = x + (float)value;
		result.y = y + (float)value;
		result.z = z + (float)value;
		return result;
	}

	FVector3D operator + (int value) const
	{
		FVector3D result;
		result.x = x + (float)value;
		result.y = y + (float)value;
		result.z = z + (float)value;
		return result;
	}

	// �ڱ� �ڽ��� ���� �����ؾ��Ѵ�.
	// ��� �����ʿ� const�� ����ϸ� �ȵȴ�.
	const FVector3D& operator += (const FVector3D& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	const FVector3D& operator += (float value)
	{
		x += (float)value;
		y += (float)value;
		z += (float)value;
		return *this;
	}
	const FVector3D& operator += (double value)
	{
		x += (float)value;
		y += (float)value;
		z += (float)value;
		return *this;
	}
	const FVector3D& operator += (int value)
	{
		x += (float)value;
		y += (float)value;
		z += (float)value;
		return *this;
	}

	const FVector3D& operator ++()
	{
		x += 1.f;
		y += 1.f;
		z += 1.f;
		return *this;
	}
	const FVector3D& operator ++(int)
	{
		x += 1.f;
		y += 1.f;
		z += 1.f;
		return *this;
	}

#pragma endregion ����������
#pragma region ���ҿ�����

	// const�� �������� :
	// 0���� ��������� ���� ������ ���� ����,
	// const���� ������ �����ϱ� �����̴�.
	FVector3D operator - (const FVector3D& v) const
	{
		FVector3D result;
		result.x = x - v.x;
		result.y = y - v.y;
		result.z = z - v.z;
		return result;
	}

	FVector3D operator - (float value) const
	{
		FVector3D result;
		result.x = x - value;
		result.y = y - value;
		result.z = z - value;
		return result;
	}

	FVector3D operator - (double value) const
	{
		FVector3D result;
		result.x = x - (float)value;
		result.y = y - (float)value;
		result.z = z - (float)value;
		return result;
	}

	FVector3D operator - (int value) const
	{
		FVector3D result;
		result.x = x - (float)value;
		result.y = y - (float)value;
		result.z = z - (float)value;
		return result;
	}

	// �ڱ� �ڽ��� ���� �����ؾ��Ѵ�.
	// ��� �����ʿ� const�� ����ϸ� �ȵȴ�.
	const FVector3D& operator -= (const FVector3D& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
	const FVector3D& operator -= (float value)
	{
		x -= (float)value;
		y -= (float)value;
		z -= (float)value;
		return *this;
	}
	const FVector3D& operator -= (double value)
	{
		x -= (float)value;
		y -= (float)value;
		z -= (float)value;
		return *this;
	}
	const FVector3D& operator -= (int value)
	{
		x -= (float)value;
		y -= (float)value;
		z -= (float)value;
		return *this;
	}

	const FVector3D& operator --()
	{
		x -= 1.f;
		y -= 1.f;
		z -= 1.f;
		return *this;
	}
	const FVector3D& operator --(int)
	{
		x -= 1.f;
		y -= 1.f;
		z -= 1.f;
		return *this;
	}


#pragma endregion ���ҿ�����

#pragma region ����������

	// const�� �������� :
	// 0���� ��������� ���� ������ ���� ����,
	// const���� ������ �����ϱ� �����̴�.
	FVector3D operator * (const FVector3D& v) const
	{
		FVector3D result;
		result.x = x * v.x;
		result.y = y * v.y;
		result.z = z * v.z;
		return result;
	}

	FVector3D operator * (float value) const
	{
		FVector3D result;
		result.x = x * value;
		result.y = y * value;
		result.z = z * value;
		return result;
	}

	FVector3D operator * (double value) const
	{
		FVector3D result;
		result.x = x * (float)value;
		result.y = y * (float)value;
		result.z = z * (float)value;
		return result;
	}

	FVector3D operator * (int value) const
	{
		FVector3D result;
		result.x = x * (float)value;
		result.y = y * (float)value;
		result.z = z * (float)value;
		return result;
	}

	// �ڱ� �ڽ��� ���� �����ؾ��Ѵ�.
	// ��� �����ʿ� const�� ����ϸ� �ȵȴ�.
	const FVector3D& operator *= (const FVector3D& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}
	const FVector3D& operator *= (float value)
	{
		x *= (float)value;
		y *= (float)value;
		z *= (float)value;
		return *this;
	}
	const FVector3D& operator *= (double value)
	{
		x *= (float)value;
		y *= (float)value;
		z *= (float)value;
		return *this;
	}
	const FVector3D& operator *= (int value)
	{
		x *= (float)value;
		y *= (float)value;
		z *= (float)value;
		return *this;
	}

#pragma endregion ����������


#pragma region �����⿬����

	// const�� �������� :
	// 0���� ��������� ���� ������ ���� ����,
	// const���� �����⸦ �����ϱ� �����̴�.
	FVector3D operator / (const FVector3D& v) const
	{
		FVector3D result;
		result.x = x / v.x;
		result.y = y / v.y;
		result.z = z / v.z;
		return result;
	}

	FVector3D operator / (float value) const
	{
		FVector3D result;
		result.x = x / value;
		result.y = y / value;
		result.z = z / value;
		return result;
	}

	FVector3D operator / (double value) const
	{
		FVector3D result;
		result.x = x / (float)value;
		result.y = y / (float)value;
		result.z = z / (float)value;
		return result;
	}

	FVector3D operator / (int value) const
	{
		FVector3D result;
		result.x = x / (float)value;
		result.y = y / (float)value;
		result.z = z / (float)value;
		return result;
	}

	// �ڱ� �ڽ��� ���� �����ؾ��Ѵ�.
	// ��� �����ʿ� const�� ����ϸ� �ȵȴ�.
	const FVector3D& operator /= (const FVector3D& v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}
	const FVector3D& operator /= (float value)
	{
		x /= (float)value;
		y /= (float)value;
		z /= (float)value;
		return *this;
	}
	const FVector3D& operator /= (double value)
	{
		x /= (float)value;
		y /= (float)value;
		z /= (float)value;
		return *this;
	}
	const FVector3D& operator /= (int value)
	{
		x /= (float)value;
		y /= (float)value;
		z /= (float)value;
		return *this;
	}

#pragma endregion �����⿬����

	float Length() const
	{
		//sqrtf: ��Ʈ�� �����ִ� �Լ�
		return sqrtf(x * x + y * y + z * z);
	}

	void Normalize()
	{
		float Size = Length();

		if (Size == 0.f)
			return;

		x /= Size;
		y /= Size;
		z /= Size;
	}

	static FVector3D Normalize(const FVector3D& v)
	{
		FVector3D result;
		float Size = v.Length();

		if (Size == 0.f)
			return result;

		result.x = v.x / Size;
		result.y = v.y / Size;
		result.z = v.z / Size;
		return result;
	}

	// �ٸ� �༮�� ������ �����ִ� �Լ�
	float Dot(const FVector3D& v)	const
	{
		return x * v.x + y * v.y + z * v.z;
	}

	const FVector3D& Cross(const FVector3D& v) const
	{
		FVector3D result;
		// x = A.Y * B.Z - A.Z * B.Y
		result.x = y * v.z - z * v.y;
		result.y = z * v.x - x * v.z;
		result.z = x * v.y - y * v.x;
	}

	float Distance(const FVector3D& v) const
	{
		FVector3D v1 = *this - v;

		return v1.Length();
	}

};