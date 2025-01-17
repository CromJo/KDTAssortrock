#pragma once
#include <math.h>
#include "EngineMath.h"

struct FVector3D
{
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;

	FVector3D() {}
	FVector3D(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	FVector3D(const FVector3D& v) : x(v.x), y(v.y), z(v.z) {}
	FVector3D(const FVector3D&& v) : x(v.x), y(v.y), z(v.z) {}

	const FVector3D& operator = (const FVector3D& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;

		return *this;
	}

	const FVector3D& operator = (float Value)
	{
		x = Value;
		y = Value;
		z = Value;

		return *this;
	}

	const FVector3D& operator = (double Value)
	{
		x = (float)Value;
		y = (float)Value;
		z = (float)Value;

		return *this;
	}

	const FVector3D& operator = (int Value)
	{
		x = (float)Value;
		y = (float)Value;
		z = (float)Value;

		return *this;
	}
#pragma region µ¡¼À 
	FVector3D operator + (const FVector3D& v)	const
	{
		FVector3D result;
		result.x = x + v.x;
		result.y = y + v.y;
		result.z = z + v.z;

		return result;
	}

	FVector3D operator + (double v)	const
	{
		FVector3D result;
		result.x = x + (float)v;
		result.y = y + (float)v;
		result.z = z + (float)v;

		return result;
	}

	FVector3D operator + (float v)	const
	{
		FVector3D result;
		result.x = x + v;
		result.y = y + v;
		result.z = z + v;

		return result;
	}

	FVector3D operator + (int v)	const
	{
		FVector3D result;
		result.x = x + (float)v;
		result.y = y + (float)v;
		result.z = z + (float)v;

		return result;
	}

	const FVector3D& operator += (const FVector3D& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;

		return *this;
	}

	const FVector3D& operator += (double Value)
	{
		x += (float)Value;
		y += (float)Value;
		z += (float)Value;

		return *this;
	}
	const FVector3D& operator += (int Value)
	{
		x += (float)Value;
		y += (float)Value;
		z += (float)Value;

		return *this;
	}
	const FVector3D& operator += (float Value)
	{
		x += Value;
		y += Value;
		z += Value;

		return *this;
	}

	const FVector3D& operator ++ ()
	{
		x += 1.f;
		y += 1.f;
		z += 1.f;

		return *this;
	}

	const FVector3D& operator ++ (int)
	{
		x += 1.f;
		y += 1.f;
		z += 1.f;

		return *this;
	}
#pragma endregion
#pragma region »¬¼À
	FVector3D operator - (const FVector3D& v)	const
	{
		FVector3D result;
		result.x = x - v.x;
		result.y = y - v.y;
		result.z = z - v.z;

		return result;
	}

	FVector3D operator - (double v)	const
	{
		FVector3D result;
		result.x = x - (float)v;
		result.y = y - (float)v;
		result.z = z - (float)v;

		return result;
	}

	FVector3D operator - (float v)	const
	{
		FVector3D result;
		result.x = x - v;
		result.y = y - v;
		result.z = z - v;

		return result;
	}

	FVector3D operator - (int v)	const
	{
		FVector3D result;
		result.x = x - (float)v;
		result.y = y - (float)v;
		result.z = z - (float)v;

		return result;
	}

	const FVector3D& operator -= (const FVector3D& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return *this;
	}

	const FVector3D& operator -= (double Value)
	{
		x -= (float)Value;
		y -= (float)Value;
		z -= (float)Value;

		return *this;
	}
	const FVector3D& operator -= (int Value)
	{
		x -= (float)Value;
		y -= (float)Value;
		z -= (float)Value;

		return *this;
	}
	const FVector3D& operator -= (float Value)
	{
		x -= Value;
		y -= Value;
		z -= Value;

		return *this;
	}
	const FVector3D& operator -- ()
	{
		x -= 1.f;
		y -= 1.f;
		z -= 1.f;

		return *this;
	}

	const FVector3D& operator -- (int)
	{
		x -= 1.f;
		y -= 1.f;
		z -= 1.f;

		return *this;
	}
#pragma endregion
#pragma region °ö¼À 
	FVector3D operator * (const FVector3D& v)	const
	{
		FVector3D result;
		result.x = x * v.x;
		result.y = y * v.y;
		result.z = z * v.z;

		return result;
	}

	FVector3D operator * (double v)	const
	{
		FVector3D result;
		result.x = x * (float)v;
		result.y = y * (float)v;
		result.z = z * (float)v;

		return result;
	}

	FVector3D operator * (float v)	const
	{
		FVector3D result;
		result.x = x * v;
		result.y = y * v;
		result.z = z * v;

		return result;
	}

	FVector3D operator * (int v)	const
	{
		FVector3D result;
		result.x = x * (float)v;
		result.y = y * (float)v;
		result.z = z * (float)v;

		return result;
	}

	const FVector3D& operator *= (const FVector3D& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;

		return *this;
	}

	const FVector3D& operator *= (double Value)
	{
		x *= (float)Value;
		y *= (float)Value;
		z *= (float)Value;

		return *this;
	}
	const FVector3D& operator *= (int Value)
	{
		x *= (float)Value;
		y *= (float)Value;
		z *= (float)Value;

		return *this;
	}
	const FVector3D& operator *= (float Value)
	{
		x *= Value;
		y *= Value;
		z *= Value;

		return *this;
	}
#pragma endregion
#pragma region ³ª´°¼À 
	FVector3D operator / (const FVector3D& v)	const
	{
		FVector3D result;
		result.x = x / v.x;
		result.y = y / v.y;
		result.z = z / v.z;

		return result;
	}

	FVector3D operator / (double v)	const
	{
		FVector3D result;
		result.x = x / (float)v;
		result.y = y / (float)v;
		result.z = z / (float)v;

		return result;
	}

	FVector3D operator / (float v)	const
	{
		FVector3D result;
		result.x = x / v;
		result.y = y / v;
		result.z = z / v;

		return result;
	}

	FVector3D operator / (int v)	const
	{
		FVector3D result;
		result.x = x / (float)v;
		result.y = y / (float)v;
		result.z = z / (float)v;

		return result;
	}

	const FVector3D& operator /= (const FVector3D& v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;

		return *this;
	}

	const FVector3D& operator /= (double Value)
	{
		x /= (float)Value;
		y /= (float)Value;
		z /= (float)Value;

		return *this;
	}
	const FVector3D& operator /= (int Value)
	{
		x /= (float)Value;
		y /= (float)Value;
		z /= (float)Value;

		return *this;
	}
	const FVector3D& operator /= (float Value)
	{
		x /= Value;
		y /= Value;
		z /= Value;

		return *this;
	}
#pragma endregion

	float Length() const
	{
		// sqrtf : ·çÆ®°ª ±¸ÇØÁÖ´Â ±â´É.
		return sqrtf((x * x) + (y * y) + (z * z));
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

	float Dot(const FVector3D& v)	const
	{
		return (x * v.x) + (y * v.y) + (z * v.z);
	}

	FVector3D Cross(const FVector3D& v) const
	{
		FVector3D result;
		result.x = (y * v.z) - (z * v.y);
		result.y = (z * v.x) - (x * v.z);
		result.x = (x * v.y) - (y * v.x);
		return result;
	}

	float Distance(const FVector3D& v)
	{
		FVector3D v1 = *this - v;

		return v1.Length();
	}

};
