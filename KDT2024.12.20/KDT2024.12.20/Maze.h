#pragma once

#include "GameInfo.h"

class CMaze
{
public:
	CMaze();
	~CMaze();

private:
	char		mName[32] = {};
	char* mOutputBuffer;
	ETileType** mMazeArray = nullptr;
	COORD		mStartPos;
	COORD		mGoalPos;
	// 플레이어의 이전 프레임의 인덱스를 구한다
	int	mPrevPlayerIndex = 0;
	char	mPrevPlayerOutput;

	// 오브젝트 주소를 저장하는 포인터 가변 배열을 만들어
	// 준다.
	class CObject** mObjectList = nullptr;
	int		mObjectCount = 0;
	int		mObjectCapacity = 4;

	int	mCountX = 0;
	int	mCountY = 0;

	int	mScore = 0;

	__int64	mTime = 0;

public:
	void SetOutputBuffer(int Index, char value)
	{
		mOutputBuffer[Index] = value;
	}

	void SetStartPosition(int X, int Y)
	{
		mStartPos.X = X;
		mStartPos.Y = Y;
	}

	void SetGoalPosition(int X, int Y)
	{
		mGoalPos.X = X;
		mGoalPos.Y = Y;
	}

	int GetScore()	const
	{
		return mScore;
	}

	__int64 GetTime()	const
	{
		return mTime;
	}

	const char* GetName()	const
	{
		return mName;
	}

	ETileType GetTile(int x, int y)	const
	{
		if (x < 0 || x >= mCountX ||
			y < 0 || y >= mCountY)
			return ETileType::Wall;

		return mMazeArray[y][x];
	}

public:
	bool FileRead(const char* FileName);
	bool Init(const char* FileName);
	void Reset();
	void Run();
	void Output(class CPlayer* Player);

private:
	void AddObject(class CObject* Obj);
	void Update(class CPlayer* Player);
};

