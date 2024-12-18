#include "Monster.h"

CMonster::CMonster()
{
}

CMonster::CMonster(const CMonster& Obj) :
	CCharacter(Obj)
{
}

CMonster::~CMonster()
{
}

bool CMonster::Init()
{
    CCharacter::Init();

    while (true)
    {
        std::cout << "1. 쉬움" << std::endl;
        std::cout << "2. 보통" << std::endl;
        std::cout << "3. 어려움" << std::endl;
        std::cout << "난이도를 선택하세요 : ";
        int Input;
        std::cin >> Input;

        if (Input < 1 || Input > 3)
            continue;

        mBattleType = (EBattleType)(Input - 1);
        break;
    }

    return true;
}

bool CMonster::Init(FILE* File)
{
    CCharacter::Init(File);

    return true;
}

void CMonster::Save(FILE* File)
{
    CCharacter::Save(File);
}

void CMonster::Output()
{
    CCharacter::Output();
}

CMonster* CMonster::Clone()
{
    return new CMonster(*this);
}
