#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <conio.h>
#include <Windows.h>
// 총알, 아이템은 실시간으로 생성되어야 한다.
// 중간, 삽입, 삭제에 성능이 좋은 list를 사용.
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
    None,       // 충돌없음
    Damage,     // 피격판정
    Heal,       // 치유판정
    Power,       // 파워우업
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