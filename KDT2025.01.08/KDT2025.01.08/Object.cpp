#include "Object.h"

CObject::CObject()
{
}

CObject::~CObject()
{
}

bool CObject::GameOver(bool isTrigger)
{
    // Y�� 0�̸� ����ü�� ������ �ǹ���
    if (!mBoard.Y)
        return false;

    // ���� ���� ��� �����
    //if(mBoard.Y >=)

    return true;
}
