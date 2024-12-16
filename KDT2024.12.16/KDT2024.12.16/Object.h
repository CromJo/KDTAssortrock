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
		abstract(���簡���Լ� ����� ���)
		1. �Լ� �ڿ� = 0 �� �ٿ��ָ� ���������Լ��� �ȴ�.
		���� �����Լ��� �ϳ��� ������ �ִ� Ŭ������ �߻�Ŭ������� �Ѵ�.
		�߻� Ŭ������ ��ü ������ �Ұ����ϴ�.
		���� �߻�Ŭ������ abstract Ű���带 �̿��Ͽ� ���� ���� �ִ�.
		���������Լ��� �ڽ� Ŭ������ �ݵ�� ������ ����� �Ѵ�.
		�ڽ��� �����ǰ� �ȵ� ��� �ڽ� Ŭ���� ���� "�߻� Ŭ����"�� ��޵ȴ�.
	*/
	virtual void VirtualPure() = 0;				// 1 : �Լ��� "= 0"�� �־� �߻�ȭ�ϴ� ���
	virtual void VirtualPure1() abstract;		// 2 : abstract Ű���带 �־� �߻�ȭ�ϴ� ���
	virtual void VirtualPure2() abstract = 0;	// 3 : 
	virtual CObject* Clone() = 0;
};

