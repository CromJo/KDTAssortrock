#pragma once

#include <math.h>
#include "EngineMath.h"

// ����ü ����
struct FVector4D
{
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
	float w = 0.f;

	// �⺻ ������
	FVector4D()
	{
	}

	// �Ű����� ���� �޾� ���� �������ִ� ������
	FVector4D(float _x, float _y, float _z, float _w) :
		x(_x),
		y(_y),
		z(_z),
		w(_w)
	{

	}

	// ���� ����
	FVector4D(const FVector4D& v) :
		x(v.x),
		y(v.y),
		z(v.z),
		w(v.w)
	{

	}

	// �̵� ������
	FVector4D(FVector4D&& v) :
		x(v.x),
		y(v.y),
		z(v.z),
		w(v.w)
	{
	}

#pragma region ���Կ�����
	const FVector4D& operator = (const FVector4D& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
		return *this;
	}

	const FVector4D& operator = (float value)
	{
		x = value;
		y = value;
		z = value;
		w = value;
		return *this;
	}

	const FVector4D& operator = (double value)
	{
		x = (float)value;
		y = (float)value;
		z = (float)value; 
		w = (float)value;
		return *this;
	}

	const FVector4D& operator = (int value)
	{
		x = (float)value;
		y = (float)value;
		z = (float)value; 
		w = (float)value;
		return *this;
	}

#pragma endregion ���Կ�����
#pragma region ����������
	// const�� �������� :
	// 0���� ��������� ���� ������ ���� ����,
	// const�� ������ �����ϱ� �����̴�.
	FVector4D operator + (const FVector4D& v) const
	{
		FVector4D result;
		result.x = x + v.x;
		result.y = y + v.y;
		result.z = z + v.z; 
		result.w = w + v.w;
		return result;
	}

	FVector4D operator + (float value) const
	{
		FVector4D result;
		result.x = x + value;
		result.y = y + value;
		result.z = z + value; 
		result.w = w + value;
		return result;
	}

	FVector4D operator + (double value) const
	{
		FVector4D result;
		result.x = x + (float)value;
		result.y = y + (float)value;
		result.z = z + (float)value; 
		result.w = w + (float)value;
		return result;
	}

	FVector4D operator + (int value) const
	{
		FVector4D result;
		result.x = x + (float)value;
		result.y = y + (float)value;
		result.z = z + (float)value; 
		result.w = w + (float)value;
		return result;
	}

	// �ڱ� �ڽ��� ���� �����ؾ��Ѵ�.
	// ��� �����ʿ� const�� ����ϸ� �ȵȴ�.
	const FVector4D& operator += (const FVector4D& v)
	{
		x += v.x;
		y += v.y;
		z += v.z; 
		w += v.w;
		return *this;
	}
	const FVector4D& operator += (float value)
	{
		x += (float)value;
		y += (float)value;
		z += (float)value; 
		w += (float)value;
		return *this;
	}
	const FVector4D& operator += (double value)
	{
		x += (float)value;
		y += (float)value;
		z += (float)value; 
		w += (float)value;
		return *this;
	}
	const FVector4D& operator += (int value)
	{
		x += (float)value;
		y += (float)value;
		z += (float)value; 
		w += (float)value;
		return *this;
	}

	const FVector4D& operator ++()
	{
		x += 1.f;
		y += 1.f;
		z += 1.f; 
		w += 1.f;
		return *this;
	}
	const FVector4D& operator ++(int)
	{
		x += 1.f;
		y += 1.f;
		z += 1.f; 
		w += 1.f;
		return *this;
	}

#pragma endregion ����������
#pragma region ���ҿ�����

	// const�� �������� :
	// 0���� ��������� ���� ������ ���� ����,
	// const���� ������ �����ϱ� �����̴�.
	FVector4D operator - (const FVector4D& v) const
	{
		FVector4D result;
		result.x = x - v.x;
		result.y = y - v.y;
		result.z = z - v.z; result.w = w - v.w;
		return result;
	}

	FVector4D operator - (float value) const
	{
		FVector4D result;
		result.x = x - value;
		result.y = y - value;
		result.z = z - value;
		return result;
	}

	FVector4D operator - (double value) const
	{
		FVector4D result;
		result.x = x - (float)value;
		result.y = y - (float)value;
		result.z = z - (float)value;
		return result;
	}

	FVector4D operator - (int value) const
	{
		FVector4D result;
		result.x = x - (float)value;
		result.y = y - (float)value;
		result.z = z - (float)value;
		return result;
	}

	// �ڱ� �ڽ��� ���� �����ؾ��Ѵ�.
	// ��� �����ʿ� const�� ����ϸ� �ȵȴ�.
	const FVector4D& operator -= (const FVector4D& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}
	const FVector4D& operator -= (float value)
	{
		x -= (float)value;
		y -= (float)value;
		z -= (float)value;
		w -= (float)value;
		return *this;
	}
	const FVector4D& operator -= (double value)
	{
		x -= (float)value;
		y -= (float)value;
		z -= (float)value;
		w -= (float)value;
		return *this;
	}
	const FVector4D& operator -= (int value)
	{
		x -= (float)value;
		y -= (float)value;
		z -= (float)value;
		w -= (float)value;
		return *this;
	}

	const FVector4D& operator --()
	{
		x -= 1.f;
		y -= 1.f;
		z -= 1.f;
		w -= 1.f;
		return *this;
	}
	const FVector4D& operator --(int)
	{
		x -= 1.f;
		y -= 1.f;
		z -= 1.f;
		w -= 1.f;
		return *this;
	}


#pragma endregion ���ҿ�����

#pragma region ����������

	// const�� �������� :
	// 0���� ��������� ���� ������ ���� ����,
	// const���� ������ �����ϱ� �����̴�.
	FVector4D operator * (const FVector4D& v) const
	{
		FVector4D result;
		result.x = x * v.x;
		result.y = y * v.y;
		result.z = z * v.z;
		result.w = w * v.w;
		return result;
	}

	FVector4D operator * (float value) const
	{
		FVector4D result;
		result.x = x * value;
		result.y = y * value;
		result.z = z * value;
		result.w = w * value;
		return result;
	}

	FVector4D operator * (double value) const
	{
		FVector4D result;
		result.x = x * (float)value;
		result.y = y * (float)value;
		result.z = z * (float)value;
		result.w = w * (float)value;
		return result;
	}

	FVector4D operator * (int value) const
	{
		FVector4D result;
		result.x = x * (float)value;
		result.y = y * (float)value;
		result.z = z * (float)value;
		result.w = w * (float)value;
		return result;
	}

	// �ڱ� �ڽ��� ���� �����ؾ��Ѵ�.
	// ��� �����ʿ� const�� ����ϸ� �ȵȴ�.
	const FVector4D& operator *= (const FVector4D& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		w *= v.w;
		return *this;
	}
	const FVector4D& operator *= (float value)
	{
		x *= (float)value;
		y *= (float)value;
		z *= (float)value;
		w *= (float)value;
		return *this;
	}
	const FVector4D& operator *= (double value)
	{
		x *= (float)value;
		y *= (float)value;
		z *= (float)value;
		w *= (float)value;
		return *this;
	}
	const FVector4D& operator *= (int value)
	{
		x *= (float)value;
		y *= (float)value;
		z *= (float)value;
		w *= (float)value;
		return *this;
	}

#pragma endregion ����������


#pragma region �����⿬����

	// const�� �������� :
	// 0���� ��������� ���� ������ ���� ����,
	// const���� �����⸦ �����ϱ� �����̴�.
	FVector4D operator / (const FVector4D& v) const
	{
		FVector4D result;
		result.x = x / v.x;
		result.y = y / v.y;
		result.z = z / v.z;
		result.w = w / v.w;
		return result;
	}

	FVector4D operator / (float value) const
	{
		FVector4D result;
		result.x = x / value;
		result.y = y / value;
		result.z = z / value;
		result.w = w / value;
		return result;
	}

	FVector4D operator / (double value) const
	{
		FVector4D result;
		result.x = x / (float)value;
		result.y = y / (float)value;
		result.z = z / (float)value;
		result.w = w / (float)value;
		return result;
	}

	FVector4D operator / (int value) const
	{
		FVector4D result;
		result.x = x / (float)value;
		result.y = y / (float)value;
		result.z = z / (float)value;
		result.w = w / (float)value;
		return result;
	}

	// �ڱ� �ڽ��� ���� �����ؾ��Ѵ�.
	// ��� �����ʿ� const�� ����ϸ� �ȵȴ�.
	const FVector4D& operator /= (const FVector4D& v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		w /= v.w;
		return *this;
	}
	const FVector4D& operator /= (float value)
	{
		x /= (float)value;
		y /= (float)value;
		z /= (float)value;
		w /= (float)value;
		return *this;
	}
	const FVector4D& operator /= (double value)
	{
		x /= (float)value;
		y /= (float)value;
		z /= (float)value;
		w /= (float)value;
		return *this;
	}
	const FVector4D& operator /= (int value)
	{
		x /= (float)value;
		y /= (float)value;
		z /= (float)value;
		w /= (float)value;
		return *this;
	}

#pragma endregion �����⿬����

	// �ε��� ������
	float& operator [] (int Index)
	{
		assert(0 <= Index && Index <= 3);

		switch (Index)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		}

		return w;
	}

	static FVector4D Black;
	static FVector4D White;
	static FVector4D Red;
	static FVector4D Blue;
	static FVector4D Green;
};