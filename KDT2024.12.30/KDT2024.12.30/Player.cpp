#include "Player.h"
#include "StageManager.h"
#include "Stage.h"
#include "ObjectManager.h"

CPlayer::CPlayer()
{
    mType = EObjectType::Player;
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Init()
{
    mPos.Y = 7;
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
                --mPos.Y;

                if (mPos.Y < 1)
                    mPos.Y = 1;

                break;
            case EKey::Down:
                ++mPos.Y;
                if (mPos.Y > 13)
                    mPos.Y = 13;

                break;
            case EKey::Left:
                --mPos.X;

                if (mPos.X < 1)
                    mPos.X = 1;
                break;
            case EKey::Right:
                ++mPos.X;

                if (mPos.X > 13)
                    mPos.X = 13;
                break;
            }
        }
    }
}

void CPlayer::Output(char* OutputBuffer)
{
    /*SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), mPos);
    std::cout << "бр";*/
    int CountX = CStageManager::GetInst()->GetStage()->GetStageCountX();
    OutputBuffer[mPos.Y * (CountX + 1) + mPos.X] = 'P';
}

ECollisionType CPlayer::CollisionEnable(CObject* Dest)
{
    switch (Dest->GetType())
    {
    case EObjectType::Player:
        return ECollisionType::Damage;
    }

    return ECollisionType::None;
}

bool CPlayer::Damage(int Dmg)
{
    mHP -= Dmg;

    if (mHP <= 0)
        return true;

    return false;
}

int CPlayer::Score(int Score)
{
    return Score++;
}
