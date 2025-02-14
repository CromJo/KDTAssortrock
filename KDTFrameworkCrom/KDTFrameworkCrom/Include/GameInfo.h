#pragma once

#include <Windows.h>
#include <list>
#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"

#include <unordered_map>
#include <vector>

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

struct FResulution
{
	unsigned int Width = 0;
	unsigned int Height = 0;
};