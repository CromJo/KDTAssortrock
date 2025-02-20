#pragma once

#include <math.h>
#include "EngineMath.h"

// ����ü ����
struct FVector2D
{
	float x = 0.f;
	float y = 0.f;

	// �⺻ ������
	FVector2D()
	{
	}

	// �Ű����� ���� �޾� ���� �������ִ� ������
	FVector2D(float _x, float _y) :
		x(_x),
		y(_y)
	{

	}

	// ���� ����
	FVector2D(const FVector2D& v) :
		x(v.x),
		y(v.y)
	{

	}

	// �̵� ������
	FVector2D(FVector2D&& v) :
		x(v.x),
		y(v.y)
	{
	}

#pragma region ���Կ�����
	const FVector2D& operator = (const FVector2D& v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}
	
	const FVector2D& operator = (float value)
	{
		x = value;
		y = value;
		return *this;
	}

	const FVector2D& operator = (double value)
	{
		x = (float)value;
		y = (float)value;
		return *this;
	}

	const FVector2D& operator = (int value)
	{
		x = (float)value;
		y = (float)value;
		return *this;
	}

#pragma endregion ���Կ�����
#pragma region ����������
	// const�� �������� :
	// 0���� ��������� ���� ������ ���� ����,
	// const�� ������ �����ϱ� �����̴�.
	FVector2D operator + (const FVector2D& v) const
	{
		FVector2D result;
		result.x = x + v.x;
		result.y = y + v.y;
		return result;
	}
	
	FVector2D operator + (float value) const
	{
		FVector2D result;
		result.x = x + value;
		result.y = y + value;
		return result;
	}
	
	FVector2D operator + (double value) const
	{
		FVector2D result;
		result.x = x + (float)value;
		result.y = y + (float)value;
		return result;
	}
	
	FVector2D operator + (int value) const
	{
		FVector2D result;
		result.x = x + (float)value;
		result.y = y + (float)value;
		return result;
	}
	

	// �ڱ� �ڽ��� ���� �����ؾ��Ѵ�.
	// ��� �����ʿ� const�� ����ϸ� �ȵȴ�.
	const FVector2D& operator += (const FVector2D& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}
	const FVector2D& operator += (float value)
	{
		x += (float)value;
		y += (float)value;
		return *this;
	}
	const FVector2D& operator += (double value)
	{
		x += (float)value;
		y += (float)value;
		return *this;
	}
	const FVector2D& operator += (int value)
	{
		x += (float)value;
		y += (float)value;
		return *this;
	}

	const FVector2D& operator ++()
	{
		x += 1.f;
		y += 1.f;
		return *this;
	}
	const FVector2D& operator ++(int)
	{
		x += 1.f;
		y += 1.f;
		return *this;
	}

#pragma endregion ����������
#pragma region ���ҿ�����

	// const�� �������� :
	// 0���� ��������� ���� ������ ���� ����,
	// const���� ������ �����ϱ� �����̴�.
	FVector2D operator - (const FVector2D& v) const
	{
		FVector2D result;
		result.x = x - v.x;
		result.y = y - v.y;
		return result;
	}

	FVector2D operator - (float value) const
	{
		FVector2D result;
		result.x = x - value;
		result.y = y - value;
		return result;
	}

	FVector2D operator - (double value) const
	{
		FVector2D result;
		result.x = x - (float)value;
		result.y = y - (float)value;
		return result;
	}

	FVector2D operator - (int value) const
	{
		FVector2D result;
		result.x = x - (float)value;
		result.y = y - (float)value;
		return result;
	}

	// �ڱ� �ڽ��� ���� �����ؾ��Ѵ�.
	// ��� �����ʿ� const�� ����ϸ� �ȵȴ�.
	const FVector2D& operator -= (const FVector2D& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}
	const FVector2D& operator -= (float value)
	{
		x -= (float)value;
		y -= (float)value;
		return *this;
	}
	const FVector2D& operator -= (double value)
	{
		x -= (float)value;
		y -= (float)value;
		return *this;
	}
	const FVector2D& operator -= (int value)
	{
		x -= (float)value;
		y -= (float)value;
		return *this;
	}

	const FVector2D& operator --()
	{
		x -= 1.f;
		y -= 1.f;
		return *this;
	}
	const FVector2D& operator --(int)
	{
		x -= 1.f;
		y -= 1.f;
		return *this;
	}

	
#pragma endregion ���ҿ�����

#pragma region ����������

	// const�� �������� :
	// 0���� ��������� ���� ������ ���� ����,
	// const���� ������ �����ϱ� �����̴�.
	FVector2D operator * (const FVector2D& v) const
	{
		FVector2D result;
		result.x = x * v.x;
		result.y = y * v.y;
		return result;
	}

	FVector2D operator * (float value) const
	{
		FVector2D result;
		result.x = x * value;
		result.y = y * value;
		return result;
	}

	FVector2D operator * (double value) const
	{
		FVector2D result;
		result.x = x * (float)value;
		result.y = y * (float)value;
		return result;
	}

	FVector2D operator * (int value) const
	{
		FVector2D result;
		result.x = x * (float)value;
		result.y = y * (float)value;
		return result;
	}

	// �ڱ� �ڽ��� ���� �����ؾ��Ѵ�.
	// ��� �����ʿ� const�� ����ϸ� �ȵȴ�.
	const FVector2D& operator *= (const FVector2D& v)
	{
		x *= v.x;
		y *= v.y;
		return *this;
	}
	const FVector2D& operator *= (float value)
	{
		x *= (float)value;
		y *= (float)value;
		return *this;
	}
	const FVector2D& operator *= (double value)
	{
		x *= (float)value;
		y *= (float)value;
		return *this;
	}
	const FVector2D& operator *= (int value)
	{
		x *= (float)value;
		y *= (float)value;
		return *this;
	}

#pragma endregion ����������


#pragma region �����⿬����

	// const�� �������� :
	// 0���� ��������� ���� ������ ���� ����,
	// const���� �����⸦ �����ϱ� �����̴�.
	FVector2D operator / (const FVector2D& v) const
	{
		FVector2D result;
		result.x = x / v.x;
		result.y = y / v.y;
		return result;
	}

	FVector2D operator / (float value) const
	{
		FVector2D result;
		result.x = x / value;
		result.y = y / value;
		return result;
	}

	FVector2D operator / (double value) const
	{
		FVector2D result;
		result.x = x / (float)value;
		result.y = y / (float)value;
		return result;
	}

	FVector2D operator / (int value) const
	{
		FVector2D result;
		result.x = x / (float)value;
		result.y = y / (float)value;
		return result;
	}

	// �ڱ� �ڽ��� ���� �����ؾ��Ѵ�.
	// ��� �����ʿ� const�� ����ϸ� �ȵȴ�.
	const FVector2D& operator /= (const FVector2D& v)
	{
		x /= v.x;
		y /= v.y;
		return *this;
	}
	const FVector2D& operator /= (float value)
	{
		x /= (float)value;
		y /= (float)value;
		return *this;
	}
	const FVector2D& operator /= (double value)
	{
		x /= (float)value;
		y /= (float)value;
		return *this;
	}
	const FVector2D& operator /= (int value)
	{
		x /= (float)value;
		y /= (float)value;
		return *this;
	}

#pragma endregion �����⿬����

	float Length() const
	{
		//sqrtf: ��Ʈ�� �����ִ� �Լ�
		return sqrtf(x * x + y * y);
	}

	void Normalize()
	{
		float Size = Length();

		if (Size == 0.f)
			return;

		x /= Size;
		y /= Size;
	}

	static FVector2D Normalize(const FVector2D& v)
	{
		FVector2D result;
		float Size = v.Length();

		if (Size == 0.f)
			return result;

		result.x = v.x / Size;
		result.y = v.y / Size;
		return result;
	}

	// �ٸ� �༮�� ������ �����ִ� �Լ�
	float Dot(const FVector2D& v)	const
	{
		return x * v.x + y * v.y;
	}

	float Distance(const FVector2D& v) const
	{
		FVector2D v1 = *this - v;
		
		return v1.Length();
	}

};