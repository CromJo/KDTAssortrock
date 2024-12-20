#include "ItemHP.h"

CItemHP::CItemHP()
{
}

CItemHP::~CItemHP()
{
}

bool CItemHP::Init()
{
    return false;
}

void CItemHP::Update()
{
}

void CItemHP::Output(char* OutBuffer, int CountX)
{
    int Index = mPos.Y * CountX + mPos.X;

    OutBuffer[Index] = '!';
}
