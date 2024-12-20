#pragma once

#include "Object.h"

class CPlayer :
	public CObject
{
public:
	CPlayer();
	virtual ~CPlayer();

private:
	class CMaze* mMaze = nullptr;
	int			mHP = 5;

public:
	int GetHP()	const
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

	void SetMaze(class CMaze* Maze)
	{
		mMaze = Maze;
	}

public:
	virtual bool Init();
	virtual void Update();
	virtual void Output(char* OutBuffer, int CountX);
	virtual void OutputHP();
};

