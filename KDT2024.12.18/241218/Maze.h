#pragma once
#include "GameInfo.h"

class CMaze
{
public:
	CMaze();
	~CMaze();

private:
	char mName[32] = {};
	char* mOutputBuffer;
	ETileType** mMazeArray = nullptr;
	
	COORD mStartPos;
	COORD mGoalPos;
	int mCountX = 0;
	int mCountY = 0;
	
	int mScore = 0;

	char mPrevPlayerOutput;
	int mPrevPlayerIndex = 0;

	// 오브젝트 주소를 저장하는 포인터 가변 배열을 만들어준다.
	class CObject** mObjectList = nullptr;
	int mObjectCount = 0;
	int mObjectCapacity = 4;

	__int64 mTime = 0;

public:
	int GetScore() const
	{
		return mScore;
	}

	__int64 GetTime() const
	{
		return mTime;
	}

	const char* GetName() const
	{
		return mName;
	}

	ETileType GetTile(int x, int y) const
	{
		if (x < 0 || x >= mCountX || y < 0 || y >= mCountY)
			return ETileType::Wall;

		return mMazeArray[y][x];
	}

public:
	bool Init(const char* FileName);
	void Run();
	void Reset();
	void Output();
};

