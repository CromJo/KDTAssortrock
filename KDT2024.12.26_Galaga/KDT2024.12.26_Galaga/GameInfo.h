#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <conio.h>
#include <Windows.h>
// �Ѿ�, �������� �ǽð����� �����Ǿ�� �Ѵ�.
// �߰�, ����, ������ ������ ���� list�� ���.
#include <list>

#define   SAFE_DELETE(p)   if(p)   { delete p; p = nullptr;}

#define   DECLARE_SINGLE(Type)   \
private:\
   Type();\
   ~Type();\
private:\
   static Type*   mInst;\
public:\
   static Type* GetInst()\
   {\
      if(nullptr == mInst)\
         mInst = new Type;\
      return mInst;\
   }\
   static void DestroyInst()\
   {\
      SAFE_DELETE(mInst);\
   }

#define   DEFINITION_SINGLE(Type) Type* Type::mInst = nullptr;

enum class EObjectType
{
    EnemyEasy,
    EnemyNormal,
    EnemyHard,
    Boss
};

namespace EKey
{
    enum Type
    {
        MoveKey = 224,
        Up = 72,
        Down = 80,
        Left = 75,
        Right = 77
    };
}