#pragma once
#include "Object.h"

class CPlayer : public CObject
{
public:
	CPlayer();
	virtual ~CPlayer();

private:
	int mHP = 5;

private:
	class CMaze* mMaze = nullptr;

public:
	void SetMaze(class CMaze* Maze)
	{
		mMaze = Maze;
	}
	int GetHP() const
	{
		return mHP;
	}
	bool AddHP(int Damage)
	{
		mHP += Damage;

		if (mHP > 5)
			mHP = 5;

		return mHP <= 0;
	}


public :
	virtual bool Init();
	virtual void Update();
	virtual void Output(char* OutBuffer, int CountX);
};

