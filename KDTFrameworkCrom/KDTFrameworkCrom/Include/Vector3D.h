#pragma once

#include <math.h>
#include "EngineMath.h"

// 구조체 형식
struct FVector3D
{
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;

	// 기본 생성자
	FVector3D()
	{
	}

	// 매개변수 값을 받아 값을 지정해주는 생성자
	FVector3D(float _x, float _y, float _z) :
		x(_x),
		y(_y),
		z(_z)
	{

	}

	// 얕은 복사
	FVector3D(const FVector3D& v) :
		x(v.x),
		y(v.y),
		z(v.z)
	{

	}

	// 이동 생성자
	FVector3D(FVector3D&& v) :
		x(v.x),
		y(v.y),
		z(v.z)
	{
	}

#pragma region 대입연산자
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

#pragma endregion 대입연산자
#pragma region 증가연산자
	// const를 붙인이유 :
	// 0에서 멤버변수의 값을 변경할 이유 없고,
	// const도 덧셈을 지원하기 위함이다.
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

	// 자기 자신의 값이 변경해야한다.
	// 고로 오른쪽에 const를 사용하면 안된다.
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

#pragma endregion 증가연산자
#pragma region 감소연산자

	// const를 붙인이유 :
	// 0에서 멤버변수의 값을 변경할 이유 없고,
	// const값도 뺄셈을 지원하기 위함이다.
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

	// 자기 자신의 값이 변경해야한다.
	// 고로 오른쪽에 const를 사용하면 안된다.
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


#pragma endregion 감소연산자

#pragma region 곱셈연산자

	// const를 붙인이유 :
	// 0에서 멤버변수의 값을 변경할 이유 없고,
	// const값도 뺄셈을 지원하기 위함이다.
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

	// 자기 자신의 값이 변경해야한다.
	// 고로 오른쪽에 const를 사용하면 안된다.
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

#pragma endregion 곱셈연산자


#pragma region 나누기연산자

	// const를 붙인이유 :
	// 0에서 멤버변수의 값을 변경할 이유 없고,
	// const값도 나누기를 지원하기 위함이다.
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

	// 자기 자신의 값이 변경해야한다.
	// 고로 오른쪽에 const를 사용하면 안된다.
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

#pragma endregion 나누기연산자

	float Length() const
	{
		//sqrtf: 루트값 구해주는 함수
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

	// 다른 녀석과 내적을 구해주는 함수
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