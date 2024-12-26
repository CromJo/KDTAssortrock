#include "Player.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Init()
{
	mPos.Y = 13;
	mPos.X = 7;

	return true;
}

void CPlayer::Update(float DeltaTime)
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
                //--mPos.Y;
                break;
            case EKey::Down:
                //++mPos.Y;
                break;
            case EKey::Left:
                mPos.X--;

                if (mPos.X < 1)
                {
                    mPos.X = 1;
                }
                break;
            case EKey::Right:
                mPos.X++;
                
                if (mPos.X > 13)
                {
                    mPos.X = 13;
                }
                break;
            }
        }
    }
}

void CPlayer::Output()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mPos);
    
    std::cout << "¡Ú";
}
