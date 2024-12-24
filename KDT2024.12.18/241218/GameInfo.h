#pragma once

#include <iostream>
#include <vector>
#include <Windows.h>
#include <conio.h>
#include <time.h>

#define	SAFE_DELETE(p)	if(p)	{ delete p; p = nullptr;}

#define	DECLARE_SINGLE(Type)	\
private:\
	Type();\
	~Type();\
private:\
	static Type*	mInst;\
public:\
	static Type* GetInst()\
	{\
		if(nullptr == mInst)\
			mInst = new Type;\
		return mInst;\
	}\
	static void DestroyInst()\
	{\
		SAFE_DELETE(mInst);\
	}

#define	DEFINITION_SINGLE(Type) Type* Type::mInst = nullptr;

enum class ETileType : unsigned char
{
	Road,
	Wall,
	Start,
	Goal,
	Item,
	Trap,
	HP
};

namespace EKey
{
	enum type
	{
		MoveKey = 224,
		Up = 72,
		Down = 80,
		Left = 75,
		Right = 77
	};
}

struct FScore
{
	int Score;	// 상위 5위권 점수판
	__int64 Time;		// 상위 5위권 점수판

};