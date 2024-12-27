#include "Player.h"
#include "StageManager.h"
#include "Stage.h"
#include "Bullet.h"
#include "ObjectManager.h"
#include "Item.h"

CPlayer::CPlayer()
{
    mType = EObjectType::Player;
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
        else if (Key == EKey::Fire)
        {
            // 플레이어 총알 생성
            CBullet* Bullet = CObjectManager::GetInst()->CreateObj<CBullet>();

            Bullet->SetPos(mPos.X, mPos.Y - 1);
            Bullet->SetMoveDir(0.f, -1.f);
            Bullet->SetType(EObjectType::PlayerBullet);
        }
    }
}

void CPlayer::Output(char* OutputBuffer)
{
	//SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mPos);
    //std::cout << "★";

    int CountX = CStageManager::GetInst()->GetStage()->GetStageCountX();
    OutputBuffer[mPos.Y * (CountX + 1) + mPos.X] = '^';
}

ECollisionType CPlayer::CollisionEnable(CObject* Dest)
{
    switch (Dest->GetType())
    {
    case EObjectType::Enemy:
    case EObjectType::EnemyBullet:
        return ECollisionType::Damage;
    case EObjectType::Item:
        return ((CItem*)Dest)->GetCollisionType();
    
}

    return ECollisionType::None;
}

bool CPlayer::Damage(int Damage)
{
    mHP -= Damage;

    if (mHP <= 0)
        return true;

    return false;
}
