#pragma once
#include "Object.h"

class CPlayer : public CObject
{
public:
	CPlayer();
	virtual ~CPlayer();

private:
	class CMaze* mMaze = nullptr;

public:
	void SetMaze(class CMaze* Maze)
	{
		mMaze = Maze;
	}

public :
	virtual bool Init();
	virtual void Update();
	virtual void Output(char* OutBuffer, int CountX);
};

