#include "SpriteEffect.h"
#include "../Component/SpriteComponent.h"
#include "../Component/AudioComponent.h"
#include "../Animation/Animation2D.h"

CSpriteEffect::CSpriteEffect()
{
}

CSpriteEffect::CSpriteEffect(const CSpriteEffect& Obj)  :
    CSceneObject(Obj)
{
}

CSpriteEffect::CSpriteEffect(CSpriteEffect&& Obj) :
    CSceneObject(Obj)
{
}

CSpriteEffect::~CSpriteEffect()
{
}

/// <summary>
/// 스프라이트 이펙트 초기화
/// </summary>
/// <returns></returns>
bool CSpriteEffect::Init()
{
    CSceneObject::Init();

    // 스프라이트 및 오디오 최상위 객체 생성
    mRoot = CreateComponent<CSpriteComponent>();
    mAudio = CreateComponent<CAudioComponent>();
    // 최상위 객체 설정
    SetRootComponent(mRoot);

    // 최상위 객체의 중심점 설정
    mRoot->SetPivot(0.5f, 0.5f);

    // 최상위 객체의 자식으로 오디오 기능 추가
    mRoot->AddChild(mAudio);

    // 히트 사운드를 넣어준다.
    mAudio->SetSound("Hit");

    // 최상위 객체의 2D애니메이션을 생성시켜서 대입해준다.
    mAnimation = mRoot->CreateAnimation2D<CAnimation2D>();

    return true;
}

void CSpriteEffect::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);
}

void CSpriteEffect::SetAnimation(const std::string& Name, float PlayTime,
    float PlayRate, bool Loop, bool Reverse)
{
    mLoop = Loop;

    mAnimation->AddSequence(Name, PlayTime, PlayRate, Loop, Reverse);

    mAnimation->SetEndFunction<CSpriteEffect>(Name, this,
        &CSpriteEffect::AnimationEnd);
}

void CSpriteEffect::AnimationEnd()
{
    if (!mLoop)
        Destroy();
}
