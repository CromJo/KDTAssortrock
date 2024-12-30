#include <iostream>
#include <vector>
#include <list>>
#include <Windows.h>
#include <conio.h>
#include <string>

#pragma once
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

enum class EObjectName
{
	Player,		// �÷��̾� ĳ����
	Score,		// �����̸鼭 ����
	Item,		// �����۱���
};

enum class EObjectState
{
	Road,
	Wall,
	Tail,
	Item,
	Player
};

enum class EObjectType
{
	Player,			// �÷��̾�
	Wall,			// ��
	Tail,			// ����(��ǥ)
};

enum class ECollisionType
{
	None,
	Damage,
	//Heal,
	//Power,
	Score
};

namespace EKey
{
	enum Type
	{
		MoveKey = 224,
		Up = 72,
		Down = 80,
		Left = 75,
		Right = 77,
		Fire = 32
	};
}
