#include "Vector3D.h"
#include "Matrix.h"

#pragma region 생성자/소멸자
FVector3D::FVector3D() {}
FVector3D::FVector3D(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
FVector3D::FVector3D(const FVector3D& v) : x(v.x), y(v.y), z(v.z) {}
FVector3D::FVector3D(const FVector3D&& v) : x(v.x), y(v.y), z(v.z) {}

FVector3D::FVector3D(const DirectX::XMVECTOR& v)
{
	// XMVECTOR를 XMFLOAT3로 만들어준다.
	DirectX::XMStoreFloat3((DirectX::XMFLOAT3*)this, v);
}
#pragma endregion
#pragma region 이퀄
const FVector3D& FVector3D::FVector3D::operator = (const FVector3D& v)
{
	x = v.x;
	y = v.y;
	z = v.z;

	return *this;
}

const FVector3D& FVector3D::FVector3D::operator = (const DirectX::XMVECTOR& v)
{
	DirectX::XMStoreFloat3((DirectX::XMFLOAT3*)this, v);

	return *this;
}

const FVector3D& FVector3D::FVector3D::operator = (float Value)
{
	x = Value;
	y = Value;
	z = Value;

	return *this;
}

const FVector3D& FVector3D::FVector3D::operator = (double Value)
{
	x = (float)Value;
	y = (float)Value;
	z = (float)Value;

	return *this;
}

const FVector3D& FVector3D::FVector3D::operator = (int Value)
{
	x = (float)Value;
	y = (float)Value;
	z = (float)Value;

	return *this;
}
#pragma endregion
#pragma region 덧셈 
FVector3D FVector3D::FVector3D::operator + (const FVector3D& v)	const
{
	FVector3D result;
	result.x = x + v.x;
	result.y = y + v.y;
	result.z = z + v.z;

	return result;
}

FVector3D FVector3D::FVector3D::operator + (double v)	const
{
	FVector3D result;
	result.x = x + (float)v;
	result.y = y + (float)v;
	result.z = z + (float)v;

	return result;
}

FVector3D FVector3D::FVector3D::operator + (float v)	const
{
	FVector3D result;
	result.x = x + v;
	result.y = y + v;
	result.z = z + v;

	return result;
}

FVector3D FVector3D::FVector3D::operator + (int v)	const
{
	FVector3D result;
	result.x = x + (float)v;
	result.y = y + (float)v;
	result.z = z + (float)v;

	return result;
}

const FVector3D& FVector3D::FVector3D::operator += (const FVector3D& v)
{
	x += v.x;
	y += v.y;
	z += v.z;

	return *this;
}

const FVector3D& FVector3D::FVector3D::operator += (double Value)
{
	x += (float)Value;
	y += (float)Value;
	z += (float)Value;

	return *this;
}
const FVector3D& FVector3D::FVector3D::operator += (int Value)
{
	x += (float)Value;
	y += (float)Value;
	z += (float)Value;

	return *this;
}
const FVector3D& FVector3D::FVector3D::operator += (float Value)
{
	x += Value;
	y += Value;
	z += Value;

	return *this;
}

const FVector3D& FVector3D::operator ++ ()
{
	x += 1.f;
	y += 1.f;
	z += 1.f;

	return *this;
}

const FVector3D& FVector3D::operator ++ (int)
{
	x += 1.f;
	y += 1.f;
	z += 1.f;

	return *this;
}
#pragma endregion
#pragma region 뺄셈
FVector3D FVector3D::operator - (const FVector3D& v)	const
{
	FVector3D result;
	result.x = x - v.x;
	result.y = y - v.y;
	result.z = z - v.z;

	return result;
}

FVector3D FVector3D::operator - (double v)	const
{
	FVector3D result;
	result.x = x - (float)v;
	result.y = y - (float)v;
	result.z = z - (float)v;

	return result;
}

FVector3D FVector3D::operator - (float v)	const
{
	FVector3D result;
	result.x = x - v;
	result.y = y - v;
	result.z = z - v;

	return result;
}

FVector3D FVector3D::operator - (int v)	const
{
	FVector3D result;
	result.x = x - (float)v;
	result.y = y - (float)v;
	result.z = z - (float)v;

	return result;
}

const FVector3D& FVector3D::operator -= (const FVector3D& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;

	return *this;
}

const FVector3D& FVector3D::operator -= (double Value)
{
	x -= (float)Value;
	y -= (float)Value;
	z -= (float)Value;

	return *this;
}
const FVector3D& FVector3D::operator -= (int Value)
{
	x -= (float)Value;
	y -= (float)Value;
	z -= (float)Value;

	return *this;
}
const FVector3D& FVector3D::operator -= (float Value)
{
	x -= Value;
	y -= Value;
	z -= Value;

	return *this;
}
const FVector3D& FVector3D::operator -- ()
{
	x -= 1.f;
	y -= 1.f;
	z -= 1.f;

	return *this;
}

const FVector3D& FVector3D::operator -- (int)
{
	x -= 1.f;
	y -= 1.f;
	z -= 1.f;

	return *this;
}
#pragma endregion
#pragma region 곱셈 
FVector3D FVector3D::operator * (const FVector3D& v)	const
{
	FVector3D result;
	result.x = x * v.x;
	result.y = y * v.y;
	result.z = z * v.z;

	return result;
}

FVector3D FVector3D::operator * (double v)	const
{
	FVector3D result;
	result.x = x * (float)v;
	result.y = y * (float)v;
	result.z = z * (float)v;

	return result;
}

FVector3D FVector3D::operator * (float v)	const
{
	FVector3D result;
	result.x = x * v;
	result.y = y * v;
	result.z = z * v;

	return result;
}

FVector3D FVector3D::operator * (int v)	const
{
	FVector3D result;
	result.x = x * (float)v;
	result.y = y * (float)v;
	result.z = z * (float)v;

	return result;
}

const FVector3D& FVector3D::operator *= (const FVector3D& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;

	return *this;
}

const FVector3D& FVector3D::operator *= (double Value)
{
	x *= (float)Value;
	y *= (float)Value;
	z *= (float)Value;

	return *this;
}
const FVector3D& FVector3D::operator *= (int Value)
{
	x *= (float)Value;
	y *= (float)Value;
	z *= (float)Value;

	return *this;
}
const FVector3D& FVector3D::operator *= (float Value)
{
	x *= Value;
	y *= Value;
	z *= Value;

	return *this;
}
#pragma endregion
#pragma region 나눗셈 
FVector3D FVector3D::operator / (const FVector3D& v)	const
{
	FVector3D result;
	result.x = x / v.x;
	result.y = y / v.y;
	result.z = z / v.z;

	return result;
}

FVector3D FVector3D::operator / (double v)	const
{
	FVector3D result;
	result.x = x / (float)v;
	result.y = y / (float)v;
	result.z = z / (float)v;

	return result;
}

FVector3D FVector3D::operator / (float v)	const
{
	FVector3D result;
	result.x = x / v;
	result.y = y / v;
	result.z = z / v;

	return result;
}

FVector3D FVector3D::operator / (int v)	const
{
	FVector3D result;
	result.x = x / (float)v;
	result.y = y / (float)v;
	result.z = z / (float)v;

	return result;
}

const FVector3D& FVector3D::operator /= (const FVector3D& v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;

	return *this;
}

const FVector3D& FVector3D::operator /= (double Value)
{
	x /= (float)Value;
	y /= (float)Value;
	z /= (float)Value;

	return *this;
}
const FVector3D& FVector3D::operator /= (int Value)
{
	x /= (float)Value;
	y /= (float)Value;
	z /= (float)Value;

	return *this;
}
const FVector3D& FVector3D::operator /= (float Value)
{
	x /= Value;
	y /= Value;
	z /= Value;

	return *this;
}
#pragma endregion

float FVector3D::Length() const
{
	// sqrtf : 루트값 구해주는 기능.
	return sqrtf((x * x) + (y * y) + (z * z));
}

void FVector3D::Normalize()
{
	float Size = Length();

	if (Size == 0.f)
		return;

	x /= Size;
	y /= Size;
	z /= Size;
}

FVector3D FVector3D::Normalize(const FVector3D& v)
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

float FVector3D::Dot(const FVector3D& v)	const
{
	return (x * v.x) + (y * v.y) + (z * v.z);
}

FVector3D FVector3D::Cross(const FVector3D& v) const
{
	FVector3D result;
	result.x = (y * v.z) - (z * v.y);
	result.y = (z * v.x) - (x * v.z);
	result.x = (x * v.y) - (y * v.x);
	return result;
}

float FVector3D::Distance(const FVector3D& v) const
{
	FVector3D v1 = *this - v;

	return v1.Length();
}

DirectX::XMVECTOR FVector3D::Convert() const
{
	return DirectX::XMLoadFloat3((DirectX::XMFLOAT3*)this);
}

FVector3D FVector3D::TransformNormal(FMatrix& Matrix)	const
{
	// XMVector3TransformNormal : 
	// w를 0으로 하여 4x4행렬과 곱한 값을 반환
	DirectX::XMVECTOR result =
		DirectX::XMVector3TransformNormal(Convert(), Matrix.m);

	return result;
}

FVector3D FVector3D::TransformCoord(FMatrix& Matrix)	const
{
	// XMVector3TransformCoord : 
	// w를 1로 하여 4x4 행렬과 곱한 값을 반환
	DirectX::XMVECTOR result = DirectX::XMVector3TransformCoord(Convert(), Matrix.m);

	return result;
}

FVector3D FVector3D::GetRotation(const FVector3D& Rotation) const
{
	// 3개의 행렬을 만들기
	FMatrix matrixRotation;

	matrixRotation.Rotation(Rotation);

	return TransformNormal(matrixRotation);
}