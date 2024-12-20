#include "Player.h"
#include "Maze.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Init()
{
	return true;
}

void CPlayer::Update()
{
	if (_kbhit() > 0)
	{
		int Key = _getch();

		if (Key == EKey::MoveKey)
		{
			Key = _getch();

			switch (Key)
			{
			case EKey::Up:
				mPos.Y--;

				if (mMaze->GetTile(mPos.X, mPos.Y) == ETileType::Wall)
				{
					mPos.Y++;
				}
				break;
			case EKey::Down:
				mPos.Y++;

				if (mMaze->GetTile(mPos.X, mPos.Y) == ETileType::Wall)
				{
					mPos.Y--;
				}
				break;

			case EKey::Left:
				mPos.X--;

				if (mMaze->GetTile(mPos.X, mPos.Y) == ETileType::Wall)
				{
					mPos.X++;
				}

				break;
			case EKey::Right:
				mPos.X++;

				if (mMaze->GetTile(mPos.X, mPos.Y) == ETileType::Wall)
				{
					mPos.X--;
				}

				break;
			}
		}
	}
}

void CPlayer::Output(char* OutBuffer, int CountX)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mPos);
	std::cout << "¢¾";
}
