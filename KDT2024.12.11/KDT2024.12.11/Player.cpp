#include "Player.h"
/*
	1. AI 추가.
*/
CPlayer::CPlayer()
{

}

CPlayer::~CPlayer()
{
}

bool CPlayer::ChangeNumber(int Input)
{
	for (int i = 0; i < 25; i++)
	{
		if (mNumber[i] == Input)
		{
			mNumber[i] = INT_MAX;
			
			return false;
		}
	}
}

void CPlayer::CheckLine()
{
	int Check1 = 0, Check2 = 0;

	mLineCount = 0;

	for (int i = 0; i < 5; i++)
	{
		Check1 = 0;
		Check2 = 0;

		for (int j = 0; j < 5; j++)
		{
			if (mNumber[i * 5 + j] == INT_MAX)
			{
				Check1++;
			}
			if (mNumber[j * 5 + i] == INT_MAX)
			{
				Check2++;
			}
		}

		if (Check1 == 5)
		{
			mLineCount++;
		}
		if (Check2 == 5)
		{
			mLineCount++;
		}
	}

	Check1 = 0;

	for (int i = 4; i <= 20; i += 4)
	{
		if (mNumber[i] == INT_MAX)
			Check1++;
	}

	if (Check1 == 5)
	{
		mLineCount++;
	}

	Check1 = 0;

	for (int i = 0; i <= 25; i += 6)
	{
		if (mNumber[i] == INT_MAX)
			Check1++;
	}

	if (Check1 == 5)
	{
		mLineCount++;
	}
}

bool CPlayer::Init()
{
	for (int i = 0; i < 25; ++i)
	{
		mNumber[i] = i + 1;
	}

	for (int i = 0; i < 100; ++i)
	{
		int	Index1 = rand() % 25;
		int	Index2 = rand() % 25;

		int Temp = mNumber[Index1];
		mNumber[Index1] = mNumber[Index2];
		mNumber[Index2] = Temp;
	}

	return true;
}

void CPlayer::Output()
{
	std::cout << "=============플레이어==============" << std::endl;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (mNumber[i * 5 + j] == INT_MAX)
				std::cout << "*\t";
			else
				std::cout << mNumber[i * 5 + j] << "\t";
		}

		std::cout << std::endl;
	}
}