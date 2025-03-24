#include "Animation2DManager.h"
#include "Animation2DData.h"
#include "../../Animation/Animation2D.h"

CAnimation2DManager::CAnimation2DManager()
{
}

CAnimation2DManager::~CAnimation2DManager()
{
    CAnimation2D::DestroyCBuffer();
}

bool CAnimation2DManager::Init()
{
    CAnimation2D::CreateCBuffer();
    
    // 파일 경로에 있는 이미지를 받아올 데이터
    TCHAR   Path[89][MAX_PATH] = {};
    // 첫시작은 Idle부터 시작해서 Idle로 설정
    // 애니메이션마다 사이즈 조절 해줘야함.
    int ImageSize = 60;

    std::vector<const TCHAR*>   FileNames;

#pragma region Player 애니메이션 모음
#pragma region Idle 애니메이션
    CreateAnimation("PlayerIdle");
    SetAnimationTextureType("PlayerIdle",
        EAnimationTextureType::Frame);

    FileNames.clear();
    

    for (int i = 0; i < ImageSize; ++i)
    {
        wsprintf(Path[i], TEXT("Texture\\Player\\Novel_Cover_Idle\\Nikke_%d.png"), i);
        FileNames.emplace_back(Path[i]);
    }

    SetTexture("PlayerIdle", "PlayerIdle", FileNames);
    AddFrameCount("PlayerIdle", ImageSize, 0.f, 0.f, 1.f, 1.f);
#pragma endregion

#pragma region Reloading 애니메이션
    CreateAnimation("PlayerReloading");
    SetAnimationTextureType("PlayerReloading",
        EAnimationTextureType::Frame);
    
    FileNames.clear();
    
    ImageSize = 37;

    for (int i = 0; i < ImageSize; ++i)
    {
        wsprintf(Path[i], TEXT("Texture\\Player\\Novel_Cover_Reloading\\Nikke_%d.png"), i);
        FileNames.emplace_back(Path[i]);
    }
    
    SetTexture("PlayerReloading", "PlayerReloading", FileNames);
    AddFrameCount("PlayerReloading", ImageSize, 0.f, 0.f, 1.f, 1.f);
#pragma endregion

#pragma region Attack 애니메이션
    CreateAnimation("PlayerAttack");
    SetAnimationTextureType("PlayerAttack",
        EAnimationTextureType::Frame);

    FileNames.clear();

    ImageSize = 4;
    for (int i = 0; i < ImageSize; ++i)
    {
        wsprintf(Path[i], TEXT("Texture\\Player\\Novel_Stance_Fire\\Nikke_%d.png"), i);
        FileNames.emplace_back(Path[i]);
    }

    SetTexture("PlayerAttack", "PlayerAttack", FileNames);
    AddFrameCount("PlayerAttack", ImageSize, 0.f, 0.f, 1.f, 1.f);
#pragma endregion

#pragma region 피격애니메이션
    CreateAnimation("Explosion");
    SetAnimationTextureType("Explosion",
        EAnimationTextureType::Frame);

    FileNames.clear();

    ImageSize = 89;
    for (int i = 1; i <= ImageSize; ++i)
    {
        wsprintf(Path[i - 1], TEXT("Texture\\Explosion\\Explosion%d.png"), i);
        FileNames.emplace_back(Path[i - 1]);
    }

    SetTexture("Explosion", "Explosion", FileNames);
    AddFrameCount("Explosion", ImageSize, 0.f, 0.f, 1.f, 1.f);
#pragma endregion

#pragma region 발사 이펙트
    CreateAnimation("HitScan");
    SetAnimationTextureType("HitScan", EAnimationTextureType::Frame);

    // 히트마커 이미지 추가
    FileNames.clear();
    FileNames.emplace_back(TEXT("Texture\\HitMarker.png"));

    SetTexture("HitScan", "HitScan", FileNames);
    AddFrameCount("HitScan", 1, 0.f, 0.f, 1.f, 1.f);
#pragma endregion
#pragma endregion

#pragma region Enemy1 애니메이션 모음

#pragma region Idle 애니메이션
    CreateAnimation("EnemyIdle");
    SetAnimationTextureType("EnemyIdle",
        EAnimationTextureType::SpriteSheet);

    SetTexture("EnemyIdle", "EnemySprite",
        TEXT("Texture\\Enemy\\Enemy1&2.png"));

    AddFrame("EnemyIdle", 0.f, 0.f, 150.f, 170.f);
#pragma endregion

#pragma region Move1 애니메이션
    // 몬스터 이동 애니메이션 설정
    CreateAnimation("EnemyMove1");
    SetAnimationTextureType("EnemyMove1",
        EAnimationTextureType::SpriteSheet);
    SetTexture("EnemyMove1", "EnemySprite");
    
    // 0번째 사진 제외하고 1,2,3사진 이미지 추가
    for (int i = 1; i < 4; ++i)
    {
        AddFrame("EnemyMove1", i * 150.f, 0.f,
            150.f, 170.f);
    }
#pragma endregion

#pragma region Attack 애니메이션
    CreateAnimation("EnemyAttack");
    SetAnimationTextureType("EnemyAttack",
        EAnimationTextureType::SpriteSheet);
    SetTexture("EnemyAttack", "EnemySprite");
    
    AddFrame("EnemyAttack", 0.f, 0.f, 150.f, 170.f);
#pragma endregion

#pragma endregion

    return true;
}

/// <summary>
/// 애니메이션 생성 함수
/// </summary>
/// <param name="Name"></param>
/// <returns></returns>
bool CAnimation2DManager::CreateAnimation(
    const std::string& Name)
{
    // 불러오려는 애니메이션이 있는지 체크 (없으면 종료)
    if (FindAnimation(Name))
        return false;

    // 애니메이션이 존재하면 생성
    CAnimation2DData* Animation = new CAnimation2DData;
    // 이름 설정
    Animation->SetName(Name);
    // 애니메이션 목록에 삽입
    mAnimationMap.insert(std::make_pair(Name, Animation));

    return true;
}

bool CAnimation2DManager::SetAnimationTextureType(
    const std::string& Name, EAnimationTextureType Type)
{
    // 애니메이션 데이터가 존재하는지 찾는다.
    CAnimation2DData* Animation = FindAnimation(Name);

    // 없으면 종료
    if (!Animation)
        return false;

    // 텍스쳐 타입을 설정해준다.
    Animation->SetAnimationTextureType(Type);

    return true;
}

bool CAnimation2DManager::SetTexture(
    const std::string& Name, 
    CTexture* Texture)
{
    CAnimation2DData* Animation = FindAnimation(Name);

    if (!Animation)
        return false;

    Animation->SetTexture(Texture);

    return true;
}

bool CAnimation2DManager::SetTexture(const std::string& Name, 
    const std::string& TextureName)
{
    CAnimation2DData* Animation = FindAnimation(Name);

    if (!Animation)
        return false;

    Animation->SetTexture(TextureName);

    return true;
}

bool CAnimation2DManager::SetTexture(
    const std::string& Name, 
    const std::string& TextureName, const TCHAR* FileName)
{
    CAnimation2DData* Animation = FindAnimation(Name);

    if (!Animation)
        return false;

    Animation->SetTexture(TextureName, FileName);

    return true;
}

bool CAnimation2DManager::SetTexture(
    const std::string& Name,
    const std::string& TextureName,
    std::vector<const TCHAR*> FileName)
{
    CAnimation2DData* Animation = FindAnimation(Name);

    if (!Animation)
        return false;

    Animation->SetTexture(TextureName, FileName);

    return true;
}

bool CAnimation2DManager::SetTexture(
    const std::string& Name, 
    const std::string& TextureName, const TCHAR* FileName,
    const TCHAR* Ext, int Count)
{
    CAnimation2DData* Animation = FindAnimation(Name);

    if (!Animation)
        return false;

    Animation->SetTexture(TextureName, FileName,
        Ext, Count);

    return true;
}

bool CAnimation2DManager::SetTextureFullPath(
    const std::string& Name, 
    const std::string& TextureName, const TCHAR* FullPath)
{
    CAnimation2DData* Animation = FindAnimation(Name);

    if (!Animation)
        return false;

    Animation->SetTextureFullPath(TextureName, FullPath);

    return true;
}

bool CAnimation2DManager::SetTextureFullPath(
    const std::string& Name, 
    const std::string& TextureName,
    std::vector<const TCHAR*> FullPath)
{
    CAnimation2DData* Animation = FindAnimation(Name);

    if (!Animation)
        return false;

    Animation->SetTextureFullPath(TextureName, FullPath);

    return true;
}

bool CAnimation2DManager::AddFrame(const std::string& Name,
    const FVector2D& Start, const FVector2D& Size)
{
    CAnimation2DData* Animation = FindAnimation(Name);

    if (!Animation)
        return false;

    Animation->AddFrame(Start, Size);

    return true;
}

bool CAnimation2DManager::AddFrame(const std::string& Name,
    float StartX, float StartY, float SizeX, float SizeY)
{
    CAnimation2DData* Animation = FindAnimation(Name);

    if (!Animation)
        return false;

    Animation->AddFrame(StartX, StartY, SizeX, SizeY);

    return true;
}

bool CAnimation2DManager::AddFrameCount(
    const std::string& Name, int Count, 
    const FVector2D& Start, const FVector2D& Size)
{
    CAnimation2DData* Animation = FindAnimation(Name);

    if (!Animation)
        return false;

    Animation->AddFrameCount(Count, Start, Size);

    return true;
}

bool CAnimation2DManager::AddFrameCount(
    const std::string& Name, int Count,
    float StartX, float StartY, float SizeX, float SizeY)
{
    CAnimation2DData* Animation = FindAnimation(Name);

    if (!Animation)
        return false;

    Animation->AddFrameCount(Count,
        StartX, StartY, SizeX, SizeY);

    return true;
}

/// <summary>
/// 애니메이션맵에서 애니메이션을 찾는 함수
/// </summary>
/// <param name="Name"></param>
/// <returns></returns>
CAnimation2DData* CAnimation2DManager::FindAnimation(
    const std::string& Name)
{
    // 애니메이션 맵에서 키 찾기
    auto    iter = mAnimationMap.find(Name);

    // 키 없으면 종료
    if (iter == mAnimationMap.end())
        return nullptr;

    // 키 있으면 값 반환
    return iter->second;
}

/// <summary>
/// 애니메이션 해제 함수
/// </summary>
/// <param name="Animation"></param>
void CAnimation2DManager::ReleaseAnimation(
    CAsset* Animation)
{
    auto    iter = mAnimationMap.find(Animation->GetName());

    if (iter != mAnimationMap.end())
    {
        // 다른곳에서 가지고 있는게 없기 때문에 제거한다.
        if (iter->second->GetRefCount() == 1)
        {
            mAnimationMap.erase(iter);
        }
    }
}
