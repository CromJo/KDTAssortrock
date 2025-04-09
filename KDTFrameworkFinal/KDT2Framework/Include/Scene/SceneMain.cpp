﻿#include "SceneMain.h"
#include "../Object/PlayerObject.h"
#include "../Object/NormalEnemy.h"
#include "../Object/NearingEnemy.h"
#include "../Object/ObjectSpawnPoint.h"
#include "../Component/StaticMeshComponent.h"
#include "SceneAssetManager.h"
#include "../Asset/Material/Material.h"
#include "../UI/UserWidget/MainWidget.h"
#include "SceneUIManager.h"
#include "../Object/TileMapObj.h"
#include "../UI/Common/Image.h"
#include "../Device.h"
#include "../Component/SpriteComponent.h"
#include "../Object/SceneObject.h"
#include "../Object/BackgroundObject.h"

CSceneMain::CSceneMain()
{
}

CSceneMain::~CSceneMain()
{
}

/// <summary>
/// 에셋관련한 기능을 메인씬에서 초기세팅 해주는 기능
/// 1. 마테리얼, 쉐이더, 텍스쳐, 사운드 등
///     Asset관련한 기능을 초기화 시켜줍니다.
/// </summary>
/// <returns></returns>
bool CSceneMain::InitAsset()
{
    mAssetManager->CreateMaterial("Enemy1");

    CMaterial* Material =
        mAssetManager->FindMaterial("Enemy1");

    Material->SetPixelShader("DefaultMaterialShader");
    Material->SetSamplerType(ETextureSamplerType::Linear);
    Material->AddTexture("Enemy1", TEXT("Texture/block_wall.png"),
        0);

    mAssetManager->LoadSound("Hit", "Effect", false, "Sound/Fire1.wav");

    return true;
}

bool CSceneMain::InitObject()
{
    // 현재 화면 크기를 불러온다.
    const FResolution& RS = CDevice::GetInst()->GetResolution();
    float Width = RS.Width / 2.f;
    float Height = RS.Height / 2.f;

    // 파일 경로를 저장해줄 데이터 생성
    TCHAR	FullPath[MAX_PATH] = {};

    // 배경 이미지 세팅
    CBackgroundObject* Background = CreateObj<CBackgroundObject>("BackGround");
    //Background->SetWorldScale(1280.f, 720.f);

    // 플레이어 오브젝트 생성
    CPlayerObject* Player = CreateObj<CPlayerObject>("Player");

    return true;

    CObjectSpawnPoint* EnemyPoint =
        CreateObj<CObjectSpawnPoint>("Enemy1");

    EnemyPoint->SetSpawnType(EObjectSpawnType::NormalEnemy);
    EnemyPoint->SetSpawnLoopType(EObjectSpawnLoopType::Once);
    EnemyPoint->SetSpawnCountType(EObjectSpawnCountType::Loop);
    EnemyPoint->SetSpawnTime(3.f);
    EnemyPoint->SetImmediateSpawn(true);
#ifdef _DEBUG
    EnemyPoint->SetWorldPos(0.f, 330.f);
#endif
#ifdef _RELEASE
    EnemyPoint->SetWorldPos(Width + 30.f, 330.f);
#endif


    EnemyPoint =
        CreateObj<CObjectSpawnPoint>("Enemy2");

    EnemyPoint->SetSpawnType(EObjectSpawnType::NormalEnemy);
    EnemyPoint->SetSpawnLoopType(EObjectSpawnLoopType::Once);
    EnemyPoint->SetSpawnCountType(EObjectSpawnCountType::Loop);
    EnemyPoint->SetSpawnTime(3.f);
    EnemyPoint->SetImmediateSpawn(true);
#ifdef _DEBUG
    EnemyPoint->SetWorldPos(0.f, 300.f);
#endif
#ifdef _RELEASE
    EnemyPoint->SetWorldPos(Width - 30.f, 300.f);
#endif
    EnemyPoint =
        CreateObj<CObjectSpawnPoint>("Enemy3");

    EnemyPoint->SetSpawnType(EObjectSpawnType::NormalEnemy);
    EnemyPoint->SetSpawnLoopType(EObjectSpawnLoopType::Once);
    EnemyPoint->SetSpawnCountType(EObjectSpawnCountType::Loop);
    EnemyPoint->SetSpawnTime(3.f);
    EnemyPoint->SetImmediateSpawn(true);
#ifdef _DEBUG
    EnemyPoint->SetWorldPos(0.f, 270.f);
#endif
#ifdef _RELEASE
    EnemyPoint->SetWorldPos(Width + 50.f, 270.f);
#endif
    EnemyPoint =
        CreateObj<CObjectSpawnPoint>("Enemy4");

    EnemyPoint->SetSpawnType(EObjectSpawnType::NormalEnemy);
    EnemyPoint->SetSpawnLoopType(EObjectSpawnLoopType::Once);
    EnemyPoint->SetSpawnCountType(EObjectSpawnCountType::Loop);
    EnemyPoint->SetSpawnTime(3.f);
    EnemyPoint->SetImmediateSpawn(true);
#ifdef _DEBUG
    EnemyPoint->SetWorldPos(0.f, 220.f);
#endif
#ifdef _RELEASE
    EnemyPoint->SetWorldPos(Width + 40.f, 220.f);
#endif
    EnemyPoint =
        CreateObj<CObjectSpawnPoint>("Enemy5");

    EnemyPoint->SetSpawnType(EObjectSpawnType::NormalEnemy);
    EnemyPoint->SetSpawnLoopType(EObjectSpawnLoopType::Once);
    EnemyPoint->SetSpawnCountType(EObjectSpawnCountType::Loop);
    EnemyPoint->SetSpawnTime(3.f);
    EnemyPoint->SetImmediateSpawn(true);
#ifdef _DEBUG
    EnemyPoint->SetWorldPos(0.f, 180.f);
#endif
#ifdef _RELEASE
    EnemyPoint->SetWorldPos(Width - 50.f, 180.f);
#endif

    EnemyPoint =
        CreateObj<CObjectSpawnPoint>("Enemy6");

    EnemyPoint->SetSpawnType(EObjectSpawnType::NormalEnemy);
    EnemyPoint->SetSpawnLoopType(EObjectSpawnLoopType::Once);
    EnemyPoint->SetSpawnCountType(EObjectSpawnCountType::Loop);
    EnemyPoint->SetSpawnTime(3.f);
    EnemyPoint->SetImmediateSpawn(true);
#ifdef _DEBUG
    EnemyPoint->SetWorldPos(0.f, 150.f);
#endif
#ifdef _RELEASE
    EnemyPoint->SetWorldPos(Width - 50.f, 150.f);
#endif
    EnemyPoint =
        CreateObj<CObjectSpawnPoint>("Enemy7");

    EnemyPoint->SetSpawnType(EObjectSpawnType::NormalEnemy);
    EnemyPoint->SetSpawnLoopType(EObjectSpawnLoopType::Once);
    EnemyPoint->SetSpawnCountType(EObjectSpawnCountType::Loop);
    EnemyPoint->SetSpawnTime(3.f);
    EnemyPoint->SetImmediateSpawn(true);
#ifdef _DEBUG
    EnemyPoint->SetWorldPos(0.f, 110.f);
#endif
#ifdef _RELEASE
    EnemyPoint->SetWorldPos(Width + 60.f, 110.f);
#endif
    
    EnemyPoint =
        CreateObj<CObjectSpawnPoint>("Enemy8");

    EnemyPoint->SetSpawnType(EObjectSpawnType::NormalEnemy);
    EnemyPoint->SetSpawnLoopType(EObjectSpawnLoopType::Once);
    EnemyPoint->SetSpawnCountType(EObjectSpawnCountType::Loop);
    EnemyPoint->SetSpawnTime(3.f);
    EnemyPoint->SetImmediateSpawn(true);    
#ifdef _DEBUG
    EnemyPoint->SetWorldPos(0.f, 60.f);
#endif
#ifdef _RELEASE
    EnemyPoint->SetWorldPos(Width - 70.f, 60.f);
#endif

    EnemyPoint =
        CreateObj<CObjectSpawnPoint>("Enemy9");

    EnemyPoint->SetSpawnType(EObjectSpawnType::NormalEnemy);
    EnemyPoint->SetSpawnLoopType(EObjectSpawnLoopType::Once);
    EnemyPoint->SetSpawnCountType(EObjectSpawnCountType::Loop);
    EnemyPoint->SetSpawnTime(3.f);
    EnemyPoint->SetImmediateSpawn(true);
    #ifdef _DEBUG
    EnemyPoint->SetWorldPos(0.f, 10.f);
#endif
#ifdef _RELEASE
    EnemyPoint->SetWorldPos(Width - 80.f, 10.f);
#endif
    /*EnemyPoint =
        CreateObj<CObjectSpawnPoint>("Enemy2");

    EnemyPoint->SetSpawnType(EObjectSpawnType::NormalEnemy);
    EnemyPoint->SetSpawnLoopType(EObjectSpawnLoopType::Once);
    EnemyPoint->SetSpawnCountType(EObjectSpawnCountType::Loop);
    EnemyPoint->SetSpawnTime(3.f);
    EnemyPoint->SetImmediateSpawn(true);
    EnemyPoint->SetWorldPos(-400.f, 300.f);

    EnemyPoint =
        CreateObj<CObjectSpawnPoint>("Enemy3");

    EnemyPoint->SetSpawnType(EObjectSpawnType::NormalEnemy);
    EnemyPoint->SetSpawnLoopType(EObjectSpawnLoopType::Once);
    EnemyPoint->SetSpawnCountType(EObjectSpawnCountType::OnceDestroy);
    EnemyPoint->SetSpawnTime(3.f);
    EnemyPoint->SetImmediateSpawn(true);
    EnemyPoint->SetWorldPos(400.f, 200.f);

    EnemyPoint =
        CreateObj<CObjectSpawnPoint>("Enemy3");

    EnemyPoint->SetSpawnType(EObjectSpawnType::NormalEnemy);
    EnemyPoint->SetSpawnLoopType(EObjectSpawnLoopType::Once);
    EnemyPoint->SetSpawnCountType(EObjectSpawnCountType::CountDestroy);
    EnemyPoint->SetDestroySpawnCount(3);
    EnemyPoint->SetSpawnTime(3.f);
    EnemyPoint->SetImmediateSpawn(true);
    EnemyPoint->SetWorldPos(-400.f, 100.f);*/

    //CEnemyObject* Enemy = CreateObj<CNormalEnemy>("Enemy");
    //Enemy->SetWorldPos(400.f, 250.f);
    //Enemy = CreateObj<CNearingEnemy>("Enemy");
    //Enemy->SetTarget(Player);
    //Enemy->SetWorldPos(-200.f, 0.f);

    return true;
}

bool CSceneMain::InitWidget()
{
    // 현재 시간으로 랜덤한 값을 설정
    srand(time(0));

    //CMainWidget* Widget = mUIManager->CreateWidget<CMainWidget>("Main");

    //mUIManager->AddToViewport(Widget);

    return true;
}
