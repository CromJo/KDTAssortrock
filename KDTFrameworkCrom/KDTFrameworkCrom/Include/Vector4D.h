#pragma once

#include <math.h>
#include "EngineMath.h"

// 구조체 형식
struct FVector4D
{
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
	float w = 0.f;

	// 기본 생성자
	FVector4D()
	{
	}

	// 매개변수 값을 받아 값을 지정해주는 생성자
	FVector4D(float _x, float _y, float _z, float _w) :
		x(_x),
		y(_y),
		z(_z),
		w(_w)
	{

	}

	// 얕은 복사
	FVector4D(const FVector4D& v) :
		x(v.x),
		y(v.y),
		z(v.z),
		w(v.w)
	{

	}

	// 이동 생성자
	FVector4D(FVector4D&& v) :
		x(v.x),
		y(v.y),
		z(v.z),
		w(v.w)
	{
	}

#pragma region 대입연산자
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

#pragma endregion 대입연산자
#pragma region 증가연산자
	// const를 붙인이유 :
	// 0에서 멤버변수의 값을 변경할 이유 없고,
	// const도 덧셈을 지원하기 위함이다.
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

	// 자기 자신의 값이 변경해야한다.
	// 고로 오른쪽에 const를 사용하면 안된다.
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

#pragma endregion 증가연산자
#pragma region 감소연산자

	// const를 붙인이유 :
	// 0에서 멤버변수의 값을 변경할 이유 없고,
	// const값도 뺄셈을 지원하기 위함이다.
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

	// 자기 자신의 값이 변경해야한다.
	// 고로 오른쪽에 const를 사용하면 안된다.
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


#pragma endregion 감소연산자

#pragma region 곱셈연산자

	// const를 붙인이유 :
	// 0에서 멤버변수의 값을 변경할 이유 없고,
	// const값도 뺄셈을 지원하기 위함이다.
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

	// 자기 자신의 값이 변경해야한다.
	// 고로 오른쪽에 const를 사용하면 안된다.
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

#pragma endregion 곱셈연산자


#pragma region 나누기연산자

	// const를 붙인이유 :
	// 0에서 멤버변수의 값을 변경할 이유 없고,
	// const값도 나누기를 지원하기 위함이다.
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

	// 자기 자신의 값이 변경해야한다.
	// 고로 오른쪽에 const를 사용하면 안된다.
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

#pragma endregion 나누기연산자

	// 인덱스 접근자
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