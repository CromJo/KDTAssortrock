#include "Enemy.h"

CEnemy::CEnemy()
{
}

CEnemy::~CEnemy()
{
}

bool CEnemy::Init()
{
    return true;
}

void CEnemy::Update(float DeltaTime)
{
    mMoveY += DeltaTime;
    
    if (mMoveY >= 1.f)
    {
        mMoveY -= 1.f;

        mPos.Y++;
    }
}

void CEnemy::Output()
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mPos);

    std::cout << "กๅ";
    //std::cout << "ขอ";
}
