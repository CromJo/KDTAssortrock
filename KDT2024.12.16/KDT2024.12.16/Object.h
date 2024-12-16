#pragma once
#include "GameInfo.h"

enum class EObjectType : unsigned char
{
	Character,
	Item,
};

class CObject
{
public:
	CObject();
	CObject(const CObject& Obj);
	virtual ~CObject();

protected:
	EObjectType mType;
	char	mName[32] = {};

public:
	void SetName(const char* Name)
	{
		strcpy_s(mName, Name);
	}

public:
	virtual bool Init();
	virtual void Output();
	virtual void CharacterExclusive();
	virtual void OverrideTest();
	/*
		abstract(순사가상함수 만드는 방법)
		1. 함수 뒤에 = 0 을 붙여주면 순수가상함수가 된다.
		순수 가상함수가 하나라도 가지고 있는 클래스를 추상클래스라고 한다.
		추상 클래스는 객체 생성이 불가능하다.
		또한 추상클래스는 abstract 키워드를 이용하여 만들 수도 있다.
		순수가상함수는 자식 클래스에 반드시 재정의 해줘야 한다.
		자식의 재정의가 안될 경우 자식 클래스 또한 "추상 클래스"로 취급된다.
	*/
	virtual void VirtualPure() = 0;				// 1 : 함수에 "= 0"을 넣어 추상화하는 방법
	virtual void VirtualPure1() abstract;		// 2 : abstract 키워드를 넣어 추상화하는 방법
	virtual void VirtualPure2() abstract = 0;	// 3 : 
	virtual CObject* Clone() = 0;
};

