#include "Maze.h"

CMaze::CMaze()
{
}

CMaze::~CMaze()
{
}

bool CMaze::Init(const char* FileName)
{
	FILE* File = nullptr;

	fopen_s(&File, FileName, "rt");

	if (!File)
		return false;

	char Line[128] = {};

	fgets(Line, 128, File);

	char* Context = nullptr;
	char* Result = strtok_s(Line, ", ", &Context);

	mCountX = atoi(Result);
	mCountY = atoi(Context);

	mMazeArray = new ETileType* [mCountY];
	
	for (int i = 0; i < mCountY; i++)
	{
		mMazeArray[i] = new ETileType[mCountX];

		fgets(Line, 128, File);

		for (int j = 0; j < mCountX; j++)
		{
			char Number[2] = {};
			Number[0] = Line[j];
			mMazeArray[i][j] = (ETileType)atoi(&Line[j]);
		}
	}

	fclose(File);

	return true;
}

void CMaze::Output()
{
	for (int i = 0; i < mCountY; i++)
	{
		for (int j = 0; j < mCountX; j++)
		{
			switch (mMazeArray[i][j])
			{
			case ETileType::Road:
				std::cout << "a";
				break;
			case ETileType::Wall:
				std::cout << "●";
				break;
			case ETileType::Start:
				std::cout << "◇";
			case ETileType::Goal:
				std::cout << "◆";
			}
		}

		std::cout << std::endl;
	}
}
