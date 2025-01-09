#include "Board.h"

bool CBoard::Init(char* FileName)
{
	char* Line = FileName;

	char* Context = nullptr;
	char* Result = strtok_s(Line, ", ", &Context);

	mMapSizeX = atoi(Result);		// 15
	mMapSizeY = atoi(Context);		// 20

	mOutputBuffer = new char[(mMapSizeX + 1) * mMapSizeY + 1];
	
	memset(mOutputBuffer, 0, sizeof(char) * ((mMapSizeX + 1) * mMapSizeY + 1));

	for (int i = 0; i < mMapSizeY; i++)
	{
		for (int j = 0; j < mMapSizeX; j++)
		{
			char Number[2] = {};
			Number[0] = Line[j];
			m
		}
	}
}

bool CBoard::FileRead(const char* FileName)
{
	return false;
}
