#pragma once

#include <Windows.h>
#include <list>
#include <unordered_map>
#include <crtdbg.h>
#include <vector>
#include <string>

#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"

#include "Share/SharedPointer.h"

// 메모리릭이 발생 되었을 때, 어디서 발생되었는지
// 찾아주는 기능을 제공

// 다이렉트11 기능 불러오기
#include <d3d11.h>
// 다이렉트 컴파일러 불러오기
#include <d3dcompiler.h>

// .lib를 링크 걸어주는 기능
#pragma comment(lib, "d3d11.lib")
// 다이렉트를 이용할 때 C++을 이용해서 코딩을 하나,
// Direct11부터는 Shader를 이용해서 코드를 짜서 출력하게끔 되어있다.
// 출력을 하기위해 HLSL이라는 언어를 사용한다.
// 추가공부 요망
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")



#define SAFE_DELETE(p) if(p) { delete p; p = nullptr; }
#define SAFE_DELETE_ARRAY(p) if(p) { delete[] p; p = nullptr; }
#define SAFE_RELEASE(p) if(p) { p->Release(); p = nullptr; }


#define DECLARE_SINGLE(Type)	\
private:\
	Type();\
	~Type();\
private:\
	static Type* mInstance;\
public:\
	static Type* GetInstance()\
	{\
		if(!mInstance)\
			mInstance = new Type;\
		return mInstance;\
	}\
	static void DestroyInstance()\
	{\
		SAFE_DELETE(mInstance);\
	}

#define DEFINITION_SINGLE(Type) Type* Type::mInstance = nullptr;



struct FRect
{
	float Left	 = 0.f;
	float Top	 = 0.f;
	float Right	 = 0.f;
	float Bottom = 0.f;
};

enum class EBulletOption
{
	Normal,			// 일반 특성
	Bounce			// 튕기기 특성
};

struct FBullet
{
	FVector2D Pos;			// 위치
	FVector2D Size;			// 크기
	FVector2D MoveDirect;	// 방향
	float Distance = 800.f;	// 거리
	EBulletOption Option = EBulletOption::Normal;
};

struct FResolution
{
	unsigned int Width = 0;
	unsigned int Height = 0;
};

// IndexBuffer와 차이점은 Format의 유무차이이다.
struct FVertexBuffer
{
	ID3D11Buffer* Buffer = nullptr;
	int Size = 0;
	int Count = 0;
	void* Data = nullptr;

	FVertexBuffer()
	{
	}

	~FVertexBuffer()
	{
		SAFE_RELEASE(Buffer);
		SAFE_DELETE_ARRAY(Data);
	}
};

struct FIndexBuffer
{
	// 데이터 저장을 위한 버퍼
	ID3D11Buffer* Buffer;
	// 데이터 1개의 크기
	int Size = 0;
	// 데이터 개수
	int Count = 0;
	// 데이터 포맷
	DXGI_FORMAT Format = DXGI_FORMAT_UNKNOWN;
	void* Data = nullptr;

	FIndexBuffer()
	{
	}

	~FIndexBuffer()
	{
		SAFE_RELEASE(Buffer);
		SAFE_DELETE_ARRAY(Data);
	}
};

// 정점 정보 (Vertex Information)
struct FVertexColor
{
	// 2D & 3D : x, y, z값 전부 필요
	FVector3D Position;
	// RGB : 0 ~ 255
	// A : 0.f ~ 1.f 방식
	FVector4D Color;

	FVertexColor()
	{
	}

	FVertexColor(const FVector3D& _Pos, const FVector4D& _Color) :
		Position(_Pos),
		Color(_Color)
	{

	}

	FVertexColor(float x, float y, float z,
		float r, float g, float b, float a) :
		Position(x, y, z),
		Color(r, g, b, a)
	{

	}
};