#include "SceneMain.h"
#include "../Object/PlayerObject.h"
#include "../Object/NormalBrick.h"
#include "../Object/ItemBrick.h"
#include "../Object/ObjectSpawnPoint.h"
#include "../Component/StaticMeshComponent.h"
#include "../Object/WallObject.h"

CSceneMain::CSceneMain()
{
}

CSceneMain::~CSceneMain()
{
}

bool CSceneMain::Init()
{
    if (!CScene::Init())
        return false;

    CPlayerObject* Player = CreateObj<CPlayerObject>("Player");

    CObjectSpawnPoint* MonsterPoint =
        CreateObj<CObjectSpawnPoint>("Monster1");

    MonsterPoint->SetSpawnType(EObjectSpawnType::NormalBrick);
    MonsterPoint->SetSpawnLoopType(EObjectSpawnLoopType::Once);
    MonsterPoint->SetSpawnCountType(EObjectSpawnCountType::Loop);
    MonsterPoint->SetSpawnTime(3.f);
    MonsterPoint->SetImmediateSpawn(true);
    MonsterPoint->SetWorldPos(400.f, 300.f);

    CObjectSpawnPoint* WallPoint = CreateObj<CObjectSpawnPoint>("Wall");
    
    RECT rect;
    HWND hWnd = GetConsoleWindow();
    
    GetClientRect(hWnd, &rect);
    
    WallPoint->SetSpawnType(EObjectSpawnType::Wall);
    WallPoint->SetSpawnLoopType(EObjectSpawnLoopType::Once);
    WallPoint->SetSpawnCountType(EObjectSpawnCountType::Loop);
    WallPoint->SetSpawnTime(3.f);
    WallPoint->SetImmediateSpawn(true);
    WallPoint->SetWorldPos(rect.left, rect.top);
    
    WallPoint = CreateObj<CObjectSpawnPoint>("Wall2");
    
    WallPoint->SetSpawnType(EObjectSpawnType::Wall);
    WallPoint->SetSpawnLoopType(EObjectSpawnLoopType::Once);
    WallPoint->SetSpawnCountType(EObjectSpawnCountType::Loop);
    WallPoint->SetSpawnTime(3.f);
    WallPoint->SetImmediateSpawn(true);
    WallPoint->SetWorldPos(rect.right, rect.top);
    
    WallPoint = CreateObj<CObjectSpawnPoint>("Wall3");
    
    WallPoint->SetSpawnType(EObjectSpawnType::Wall);
    WallPoint->SetSpawnLoopType(EObjectSpawnLoopType::Once);
    WallPoint->SetSpawnCountType(EObjectSpawnCountType::Loop);
    WallPoint->SetSpawnTime(3.f);
    WallPoint->SetImmediateSpawn(true);
    WallPoint->SetWorldPos(rect.left, rect.bottom);
    
    WallPoint = CreateObj<CObjectSpawnPoint>("Wall4");
    
    WallPoint->SetSpawnType(EObjectSpawnType::Wall);
    WallPoint->SetSpawnLoopType(EObjectSpawnLoopType::Once);
    WallPoint->SetSpawnCountType(EObjectSpawnCountType::Loop);
    WallPoint->SetSpawnTime(3.f);
    WallPoint->SetImmediateSpawn(true);
    WallPoint->SetWorldPos(rect.right, rect.bottom);


    return true;
}
