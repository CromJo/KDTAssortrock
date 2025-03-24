#include "SceneMain.h"
#include "../Object/PlayerObject.h"
#include "../Object/GunnerMonster.h"
#include "../Object/NearingMonster.h"
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
    mAssetManager->CreateMaterial("Monster1");

    CMaterial* Material =
        mAssetManager->FindMaterial("Monster1");

    Material->SetPixelShader("DefaultMaterialShader");
    Material->SetSamplerType(ETextureSamplerType::Linear);
    Material->AddTexture("Monster1", TEXT("Texture/block_wall.png"),
        0);

    mAssetManager->LoadSound("Hit", "Effect", false, "Sound/Fire1.wav");

    return true;
}

bool CSceneMain::InitObject()
{
    // 파일 경로를 저장해줄 데이터 생성
    TCHAR	FullPath[MAX_PATH] = {};

    // 배경 이미지 세팅
    CBackgroundObject* Background = CreateObj<CBackgroundObject>("BackGround");

    // 플레이어 오브젝트 생성
    CPlayerObject* Player = CreateObj<CPlayerObject>("Player");

    CObjectSpawnPoint* MonsterPoint =
        CreateObj<CObjectSpawnPoint>("Monster1");

    MonsterPoint->SetSpawnType(EObjectSpawnType::GunnerMonster);
    MonsterPoint->SetSpawnLoopType(EObjectSpawnLoopType::Once);
    MonsterPoint->SetSpawnCountType(EObjectSpawnCountType::Loop);
    MonsterPoint->SetSpawnTime(3.f);
    MonsterPoint->SetImmediateSpawn(true);
    MonsterPoint->SetWorldPos(400.f, 300.f);

    MonsterPoint =
        CreateObj<CObjectSpawnPoint>("Monster2");

    MonsterPoint->SetSpawnType(EObjectSpawnType::GunnerMonster);
    MonsterPoint->SetSpawnLoopType(EObjectSpawnLoopType::Once);
    MonsterPoint->SetSpawnCountType(EObjectSpawnCountType::Loop);
    MonsterPoint->SetSpawnTime(3.f);
    MonsterPoint->SetImmediateSpawn(true);
    MonsterPoint->SetWorldPos(-400.f, 300.f);

    MonsterPoint =
        CreateObj<CObjectSpawnPoint>("Monster3");

    MonsterPoint->SetSpawnType(EObjectSpawnType::GunnerMonster);
    MonsterPoint->SetSpawnLoopType(EObjectSpawnLoopType::Once);
    MonsterPoint->SetSpawnCountType(EObjectSpawnCountType::OnceDestroy);
    MonsterPoint->SetSpawnTime(3.f);
    MonsterPoint->SetImmediateSpawn(true);
    MonsterPoint->SetWorldPos(400.f, -300.f);

    MonsterPoint =
        CreateObj<CObjectSpawnPoint>("Monster3");

    MonsterPoint->SetSpawnType(EObjectSpawnType::GunnerMonster);
    MonsterPoint->SetSpawnLoopType(EObjectSpawnLoopType::Once);
    MonsterPoint->SetSpawnCountType(EObjectSpawnCountType::CountDestroy);
    MonsterPoint->SetDestroySpawnCount(3);
    MonsterPoint->SetSpawnTime(3.f);
    MonsterPoint->SetImmediateSpawn(true);
    MonsterPoint->SetWorldPos(-400.f, -300.f);

    CEnemyObject* Monster = CreateObj<CGunnerMonster>("Monster");

    Monster->SetWorldPos(400.f, 250.f);

    Monster = CreateObj<CNearingMonster>("Monster");

    Monster->SetTarget(Player);

    Monster->SetWorldPos(-200.f, 0.f);

    return true;
}

bool CSceneMain::InitWidget()
{
    //CMainWidget* Widget = mUIManager->CreateWidget<CMainWidget>("Main");

    //mUIManager->AddToViewport(Widget);

    return true;
}
