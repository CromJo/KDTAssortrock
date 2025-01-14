#pragma once
#include <math.h>

struct FVector2D
{
	float x = 0.f;
	float y = 0.f;

#pragma region ±¸Á¶Ã¼
	FVector2D() {}
	FVector2D(float _x, float _y) : x(_x), y(_y) {}
	FVector2D(const FVector2D& v) : x(v.x), y(v.y) {}
#pragma endregion

#pragma region ±¸ÇÏ±â (Equal)
	const FVector2D& operator = (const FVector2D& v)
	{
		x = v.x;
		y = v.y;

		return *this;
	}

	const FVector2D& operator = (float Value)
	{
		x = Value;
		y = Value;
		
		return *this;
	}

	const FVector2D& operator = (double Value)
	{
		x = (float)Value;
		y = (float)Value;

		return *this;
	}

	const FVector2D& operator = (int Value)
	{
		x = (float)Value;
		y = (float)Value;

		return *this;
	}
#pragma endregion

#pragma region µ¡¼À 
	FVector2D operator + (const FVector2D& v)	const
	{
		FVector2D result;
		result.x = x + v.x;
		result.y = y + v.y;

		return result;
	}

	FVector2D operator + (double v)	const
	{
		FVector2D result;
		result.x = x + (float)v;
		result.y = y + (float)v;

		return result;
	}

	FVector2D operator + (float v)	const
	{
		FVector2D result;
		result.x = x + v;
		result.y = y + v;

		return result;
	}

	FVector2D operator + (int v)	const
	{
		FVector2D result;
		result.x = x + (float)v;
		result.y = y + (float)v;

		return result;
	}

	const FVector2D& operator += (const FVector2D& v)
	{
		x += v.x;
		y += v.y;

		return *this;
	}

	const FVector2D& operator += (double Value)
	{
		x += (float)Value;
		y += (float)Value;

		return *this;
	}
	const FVector2D& operator += (int Value)
	{
		x += (float)Value;
		y += (float)Value;

		return *this;
	}
	const FVector2D& operator += (float Value)
	{
		x += Value;
		y += Value;

		return *this;
	}

	const FVector2D& operator ++ ()
	{
		x += 1.f;
		y += 1.f;

		return *this;
	}

	const FVector2D& operator ++ (int)
	{
		x += 1.f;
		y += 1.f;

		return *this;
	}
#pragma endregion

#pragma region »¬¼À
	FVector2D operator - (const FVector2D& v)	const
	{
		FVector2D result;
		result.x = x - v.x;
		result.y = y - v.y;

		return result;
	}

	FVector2D operator - (double v)	const
	{
		FVector2D result;
		result.x = x - (float)v;
		result.y = y - (float)v;

		return result;
	}

	FVector2D operator - (float v)	const
	{
		FVector2D result;
		result.x = x - v;
		result.y = y - v;

		return result;
	}

	FVector2D operator - (int v)	const
	{
		FVector2D result;
		result.x = x - (float)v;
		result.y = y - (float)v;

		return result;
	}

	const FVector2D& operator -= (const FVector2D& v)
	{
		x -= v.x;
		y -= v.y;

		return *this;
	}

	const FVector2D& operator -= (double Value)
	{
		x -= (float)Value;
		y -= (float)Value;

		return *this;
	}
	const FVector2D& operator -= (int Value)
	{
		x -= (float)Value;
		y -= (float)Value;

		return *this;
	}
	const FVector2D& operator -= (float Value)
	{
		x -= Value;
		y -= Value;

		return *this;
	}
	const FVector2D& operator -- ()
	{
		x -= 1.f;
		y -= 1.f;

		return *this;
	}

	const FVector2D& operator -- (int)
	{
		x -= 1.f;
		y -= 1.f;

		return *this;
	}
#pragma endregion

#pragma region °ö¼À 
	FVector2D operator * (const FVector2D& v)	const
	{
		FVector2D result;
		result.x = x * v.x;
		result.y = y * v.y;

		return result;
	}

	FVector2D operator * (double v)	const
	{
		FVector2D result;
		result.x = x * (float)v;
		result.y = y * (float)v;

		return result;
	}

	FVector2D operator * (float v)	const
	{
		FVector2D result;
		result.x = x * v;
		result.y = y * v;

		return result;
	}

	FVector2D operator * (int v)	const
	{
		FVector2D result;
		result.x = x * (float)v;
		result.y = y * (float)v;

		return result;
	}

	const FVector2D& operator *= (const FVector2D& v)
	{
		x *= v.x;
		y *= v.y;

		return *this;
	}

	const FVector2D& operator *= (double Value)
	{
		x *= (float)Value;
		y *= (float)Value;

		return *this;
	}
	const FVector2D& operator *= (int Value)
	{
		x *= (float)Value;
		y *= (float)Value;

		return *this;
	}
	const FVector2D& operator *= (float Value)
	{
		x *= Value;
		y *= Value;

		return *this;
	}
#pragma endregion

#pragma region ³ª´°¼À 
	FVector2D operator / (const FVector2D& v)	const
	{
		FVector2D result;
		result.x = x / v.x;
		result.y = y / v.y;

		return result;
	}

	FVector2D operator / (double v)	const
	{
		FVector2D result;
		result.x = x / (float)v;
		result.y = y / (float)v;

		return result;
	}

	FVector2D operator / (float v)	const
	{
		FVector2D result;
		result.x = x / v;
		result.y = y / v;

		return result;
	}

	FVector2D operator / (int v)	const
	{
		FVector2D result;
		result.x = x / (float)v;
		result.y = y / (float)v;

		return result;
	}

	const FVector2D& operator /= (const FVector2D& v)
	{
		x /= v.x;
		y /= v.y;

		return *this;
	}

	const FVector2D& operator /= (double Value)
	{
		x /= (float)Value;
		y /= (float)Value;

		return *this;
	}
	const FVector2D& operator /= (int Value)
	{
		x /= (float)Value;
		y /= (float)Value;

		return *this;
	}
	const FVector2D& operator /= (float Value)
	{
		x /= Value;
		y /= Value;

		return *this;
	}
#pragma endregion

#pragma region º¤ÅÍ ÇÔ¼ö
	float Length() const
	{
		// sqrtf : ·çÆ®°ª ±¸ÇØÁÖ´Â ±â´É.
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
	
	float Dot(const FVector2D& v)	const
	{
		return x * v.x + y * v.y;
	}

	float Distance(const FVector2D& v)
	{
		FVector2D v1 = *this - v;

		return v1.Length();
	}
#pragma endregion


};

