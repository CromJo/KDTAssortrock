#pragma once
#include <Windows.h>
#include <list>
#include <time.h>
#include <math.h>
#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"

#define   SAFE_DELETE(p)   if(p)   { delete p; p = nullptr;}

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
}\

#define DEFINITION_SINGLE(Type) Type* Type::mInstance = nullptr;

struct FRect
{
	float Left = 0.f;
	float Top = 0.f;
	float Right = 0.f;
	float Bottom = 0.f;
};

enum class EBulletOption
{
	Normal,
	Bounce
};

struct FBullet
{
	FVector2D Pos;
	FVector2D Size;
	FVector2D MoveDirect;

	float Distance = 500.f;
	EBulletOption Option = EBulletOption::Normal;
};