#include "AI.h"

CAI::CAI()
{
}

CAI::~CAI()
{
}

bool CAI::Init()
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

void CAI::Output()
{
	std::cout << "=============인공지능==============" << std::endl;

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

bool CAI::ChangeNumber(int Input)
{
	for (int i = 0; i < 25; i++)
	{
		if (mNumber[i] == Input)
		{
			mNumber[i] = INT_MAX;

			return false;
		}
	}

	return true;
}

void CAI::CheckLine()
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
		std::cout << "여기 들어오는 이유가 있어? : " << Check1 << std::endl;
		mLineCount++;
	}
}
