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

enum class ESpawnType
{
    EnemyEasy,
    EnemyNormal,
    EnemyHard,
    Boss,
    ItemScore,
    ItemHeal,
    ItemPower,
    
};

enum class EObjectType
{
    Enemy,
    Player,
    PlayerBullet,
    EnemyBullet,
    Item
};

namespace EItemType
{
    enum Type
    {
        Score,
        Heal,
        Power,
        End
    };
}

enum class ECollisionType
{
    None,       // �浹����
    Damage,     // �ǰ�����
    Heal,       // ġ������
    Power,       // �Ŀ����
    Score
};

namespace EKey
{
    enum Type
    {
        MoveKey = 224,
        Up = 72,
        Down = 80,
        Left = 75,
        Right = 77,
        Fire = 32
    };
}