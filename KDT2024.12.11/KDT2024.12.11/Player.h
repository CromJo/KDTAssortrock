#pragma once
#include "GameInfo.h"

class CPlayer
{
public:
	CPlayer();
	~CPlayer();

private:
	int mNumber[25] = {};
	int mLineCount = 0;

public:
	int GetLineCount()
	{
		return mLineCount;
	}
public:
	bool Init();
	void Output();
	bool ChangeNumber(int Input);
	void CheckLine();
};