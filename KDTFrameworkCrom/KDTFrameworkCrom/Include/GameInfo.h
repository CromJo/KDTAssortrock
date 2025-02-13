#pragma once

#include <Windows.h>
#include <list>
#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"

#define SAFE_DELETE(p) if(p) { delete p; p = nullptr; }

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

struct FBullet
{
	FVector2D Pos;			// 위치
	FVector2D Size;			// 크기
	FVector2D MoveDirect;	// 방향
};