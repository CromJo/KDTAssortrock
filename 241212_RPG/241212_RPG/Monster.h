#pragma once
#include "GameInfo.h"

// 오브젝트 매니저로 관리 할 것.
// 복사 생성자로 처리함.
class CMonster
{
	friend class CObjectManager;
	friend class CBattle;

private:
	CMonster();
	~CMonster();

private :
	char mName[32] = {};
	int mAttack = 0;
	int mDefense = 0;
	int mHP = 0;
	int mHPMax = 0;
	int mMP = 0;
	int mMPMax = 0;
	int mLevel = 0;
	int mExp = 0;
	int mGold = 10000;

public:
	bool Init(FILE* File);
	void Output();

	// 자신을 복제한 새로운 몬스터를 만든다.
	CMonster* Clone();

// 선생님께서 만드는 전투에 쓰이는 함수
public:
	int GetAttack();
	int GetDefense();
	bool Damage(int Dmg)
	{
		mHP -= Dmg;

		if (mHP <= 0)
			return true;

		return false;
	}

	int GetExp()
	{
		return mExp;
	}
	int GetGold()
	{
		return mGold;
	}
	void AddExp(int Exp)
	{
		mExp += Exp;
	}
	void AddGold(int Gold)
	{
		mGold += Gold;
	}
};

