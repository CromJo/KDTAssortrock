#pragma once
#include <math.h>
#include "EngineMath.h"

struct FVector3D
{
	float x = 0.f;	
	float y = 0.f;
	float z = 0.f;

#pragma region »ý¼ºÀÚ/¼Ò¸êÀÚ
	FVector3D();
	FVector3D(float _x, float _y, float _z);
	FVector3D(const FVector3D& v);
	FVector3D(const FVector3D&& v);

	FVector3D(const DirectX::XMVECTOR& v);
#pragma endregion
#pragma region ÀÌÄ÷
	const FVector3D& operator = (const FVector3D& v);
	const FVector3D& operator = (const DirectX::XMVECTOR& v);
	const FVector3D& operator = (float Value);
	const FVector3D& operator = (double Value);
	const FVector3D& operator = (int Value);
#pragma endregion
#pragma region µ¡¼À 
	FVector3D operator + (const FVector3D& v)	const;
	FVector3D operator + (double v)	const;
	FVector3D operator + (float v)	const;
	FVector3D operator + (int v)	const;

	const FVector3D& operator += (const FVector3D& v);
	const FVector3D& operator += (double Value);
	const FVector3D& operator += (int Value);
	const FVector3D& operator += (float Value);
	const FVector3D& operator ++ ();
	const FVector3D& operator ++ (int);
#pragma endregion
#pragma region »¬¼À
	FVector3D operator - (const FVector3D& v)	const;
	FVector3D operator - (double v)	const;
	FVector3D operator - (float v)	const;
	FVector3D operator - (int v)	const;

	const FVector3D& operator -= (const FVector3D& v);
	const FVector3D& operator -= (double Value);
	const FVector3D& operator -= (int Value);
	const FVector3D& operator -= (float Value);
	const FVector3D& operator -- ();
	const FVector3D& operator -- (int);
#pragma endregion
#pragma region °ö¼À 
	FVector3D operator * (const FVector3D& v)	const;
	FVector3D operator * (double v)	const;
	FVector3D operator * (float v)	const;
	FVector3D operator * (int v)	const;

	const FVector3D& operator *= (const FVector3D& v);
	const FVector3D& operator *= (double Value);
	const FVector3D& operator *= (int Value);
	const FVector3D& operator *= (float Value);
#pragma endregion
#pragma region ³ª´°¼À 
	FVector3D operator / (const FVector3D& v)	const;
	FVector3D operator / (double v)	const;
	FVector3D operator / (float v)	const;
	FVector3D operator / (int v)	const;

	const FVector3D& operator /= (const FVector3D& v);
	const FVector3D& operator /= (double Value);
	const FVector3D& operator /= (int Value);
	const FVector3D& operator /= (float Value);
#pragma endregion

	float Length() const;

	void Normalize();
	static FVector3D Normalize(const FVector3D& v);

	float Dot(const FVector3D& v)	const;

	FVector3D Cross(const FVector3D& v) const;

	float Distance(const FVector3D& v) const;

	DirectX::XMVECTOR Convert() const;

	FVector3D TransformNormal(union FMatrix& Matrix) const;

	FVector3D TransformCoord(union FMatrix& Matrix)	const;

	FVector3D GetRotation(const FVector3D& Rotation) const;
};
