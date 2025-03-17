#include "Animation2D.h"
#include "../Asset/Animation/Animation2DData.h"
#include "../Asset/Animation/Animation2DManager.h"
#include "../Asset/AssetManager.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneAssetManager.h"
#include "../Component/SpriteComponent.h"
#include "../Asset/Texture/Texture.h"

CAnimation2DCBuffer* CAnimation2D::mAnimCBuffer = nullptr;

void CAnimation2D::CreateCBuffer()
{
	mAnimCBuffer = new CAnimation2DCBuffer;

	mAnimCBuffer->Init();
}

void CAnimation2D::DestroyCBuffer()
{
	SAFE_DELETE(mAnimCBuffer);
}

void CAnimation2D::DisableAnimation()
{
	mAnimCBuffer->SetAnimation2DEnable(false);

	mAnimCBuffer->UpdateBuffer();
}

CAnimation2D::CAnimation2D()
{
}

CAnimation2D::CAnimation2D(const CAnimation2D& Anim)
{
	*this = Anim;
}

CAnimation2D::~CAnimation2D()
{
	auto	iter = mSequenceMap.begin();
	auto	iterEnd = mSequenceMap.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
}

bool CAnimation2D::Init()
{
	return true;
}

void CAnimation2D::Update(float DeltaTime)
{
	mCurrentSequence->Update(DeltaTime);
}

/// <summary>
/// Name으로 애니메이션 시퀀스 추가
/// </summary>
/// <param name="Name"></param>
/// <param name="PlayTime : 동작 시간 설정"></param>
/// <param name="PlayRate : 재생 속도 배율"></param>
/// <param name="Loop : 반복 설정"></param>
/// <param name="Reverse : 역재생 설정"></param>
/// <returns></returns>
bool CAnimation2D::AddSequence(const std::string& Name, 
	float PlayTime, float PlayRate, bool Loop, bool Reverse)
{
	// 시퀀스 찾아서 대입
	CAnimation2DSequence* Sequence = FindSequence(Name);

	// 시퀀스 존재 시 종료 (이미 추가되어있기 때문)
	if (Sequence)
		return false;

	// 시퀀스가 없다면 데이터 저장 변수 추가
	CAnimation2DData* Data = nullptr;

	// 씬이 존재하면
	// 이름으로 애니메이션 찾아와 대입
	if (mScene)
		Data = mScene->GetAssetManager()->FindAnimation(Name);
	// 씬이 존재하지 않는다면
	// 없는대로 이름으로 애니메이션 찾아와 대입
	else
		Data = CAssetManager::GetInst()->GetAnimationManager()->FindAnimation(Name);

	// 그럼에도 데이터를 제대로 못 넣으면 종료
	if (!Data)
		return false;

	// 데이터가 들어갔다면
	// 시퀀스를 생성 (기존에 nullptr 이였음)
	Sequence = new CAnimation2DSequence;
	// 자기자신 넣어주고 (자기자신 : Animation2D)
	Sequence->mOwner = this;
	// 초기 설정 한번 해줌
	Sequence->SetAsset(Data);			// 보여줄 애니메이션 이미지
	Sequence->SetPlayTime(PlayTime);	// 동작 시간 설정
	Sequence->SetPlayRate(PlayRate);	// 재생 속도 설정
	Sequence->SetLoop(Loop);			// 반복 유무 설정 
	Sequence->SetReverse(Reverse);		// 역재생 유무 설정

	// 처음 지정된 Sequence로 현재 Sequence를 지정해둔다.
	if (!mCurrentSequence)
	{
		// 초기설정한 시퀀스를 현재 시퀀스에 넣는다.
		mCurrentSequence = Sequence;
		// Sprite컴포넌트의 텍스쳐를 현재 시퀀스의 텍스쳐로 변경해준다.
		mOwner->SetTexture(
			mCurrentSequence->GetAnimationAsset()->GetTexture());
	}

	// 시퀀스 목록에 추가한다.
	mSequenceMap.insert(std::make_pair(Name, Sequence));

	return true;
}

/// <summary>
/// Asset으로 시퀀스 추가
/// </summary>
/// <param name="Asset"></param>
/// <param name="PlayTime"></param>
/// <param name="PlayRate"></param>
/// <param name="Loop"></param>
/// <param name="Reverse"></param>
/// <returns></returns>
bool CAnimation2D::AddSequence(CAnimation2DData* Asset,
	float PlayTime, float PlayRate, bool Loop, bool Reverse)
{
	CAnimation2DSequence* Sequence = FindSequence(Asset->GetName());
	// 시퀀스를 찾았으면 종료
	if (Sequence)
		return false;

	// 못찾았으면 생성
	Sequence = new CAnimation2DSequence;

	Sequence->mOwner = this;
	// 초기 세팅
	Sequence->SetAsset(Asset);
	Sequence->SetPlayTime(PlayTime);
	Sequence->SetPlayRate(PlayRate);
	Sequence->SetLoop(Loop);
	Sequence->SetReverse(Reverse);

	// 처음 지정된 Sequence로 현재 Sequence를 지정해둔다.
	if (!mCurrentSequence)
	{
		mCurrentSequence = Sequence;
		mOwner->SetTexture(
			mCurrentSequence->GetAnimationAsset()->GetTexture());
	}

	mSequenceMap.insert(std::make_pair(Asset->GetName(),
		Sequence));

	return true;
}

void CAnimation2D::SetPlayTime(const std::string& Name,
	float PlayTime)
{
	CAnimation2DSequence* Sequence = FindSequence(Name);

	if (!Sequence)
		return;

	Sequence->SetPlayTime(PlayTime);
}

void CAnimation2D::SetPlayRate(const std::string& Name,
	float PlayRate)
{
	CAnimation2DSequence* Sequence = FindSequence(Name);

	if (!Sequence)
		return;

	Sequence->SetPlayRate(PlayRate);
}

void CAnimation2D::SetLoop(const std::string& Name,
	bool Loop)
{
	CAnimation2DSequence* Sequence = FindSequence(Name);

	if (!Sequence)
		return;

	Sequence->SetLoop(Loop);
}

void CAnimation2D::SetReverse(const std::string& Name,
	bool Reverse)
{
	CAnimation2DSequence* Sequence = FindSequence(Name);

	if (!Sequence)
		return;

	Sequence->SetReverse(Reverse);
}

/// <summary>
/// 현재 실행중인 애니메이션을 변경해주는 함수
/// </summary>
/// <param name="Name"></param>
void CAnimation2D::ChangeAnimation(const std::string& Name)
{
	// 변경할 애니메이션 이름이 존재하는지 체크
	if (Name.empty())
		return;

	// 현재 시퀀스가 아니면 종료 (이 부분에 대한 파악이 아직 안되었음)
	else if (!mCurrentSequence)
		return;

	// 현재 실행중인 애니메이션이 받아오려는 애니메이션이면 종료
	else if (mCurrentSequence->GetName() == Name)
		return;

	// 현재 애니메이션을 초기화해준다.
	mCurrentSequence->mFrame = 0;
	mCurrentSequence->mTime = 0.f;
	mCurrentSequence->mEndFunctionEnable = true;

	// 시퀀스 찾기 
	CAnimation2DSequence* Sequence = FindSequence(Name);

	// 시퀀스를 못찾았다면 종료
	if (!Sequence)
		return;

	// 시퀀스를 찾았다면 현재 시퀀스에 대입
	mCurrentSequence = Sequence;

	// 현재 시퀀스를 초기화 해준다.
	mCurrentSequence->mFrame = 0;
	mCurrentSequence->mTime = 0.f;

	// 현재 애니메이션 시퀀스를 텍스쳐로 설정
	mOwner->SetTexture(
		mCurrentSequence->GetAnimationAsset()->GetTexture());
}

CAnimation2D* CAnimation2D::Clone()
{
	return new CAnimation2D(*this);
}

void CAnimation2D::SetShader()
{
	// 애니메이션 정보를 Shader에 넘겨준다.
	float LTX = 0.f, LTY = 0.f, RBX = 1.f, RBY = 1.f;

	EAnimationTextureType	TexType =
		mCurrentSequence->mAsset->GetAnimationTextureType();

	CTexture* Texture = mCurrentSequence->mAsset->GetTexture();

	const FAnimationFrame& Frame = 
		mCurrentSequence->mAsset->GetFrame(mCurrentSequence->mFrame);

	switch (TexType)
	{
	case EAnimationTextureType::SpriteSheet:
		LTX = Frame.Start.x / Texture->GetTexture()->Width;
		LTY = Frame.Start.y / Texture->GetTexture()->Height;
		RBX = LTX + Frame.Size.x / Texture->GetTexture()->Width;
		RBY = LTY + Frame.Size.y / Texture->GetTexture()->Height;
		mOwner->SetTextureIndex(0);
		break;
	case EAnimationTextureType::Frame:
		mOwner->SetTextureIndex(mCurrentSequence->mFrame);
		break;
	}

	mAnimCBuffer->SetAnimation2DEnable(true);
	mAnimCBuffer->SetUV(LTX, LTY, RBX, RBY);

	mAnimCBuffer->UpdateBuffer();
}

void CAnimation2D::SetAnimationReverseX(bool Reverse)
{
	mAnimCBuffer->SetAnimation2DReverseX(Reverse);
}

/// <summary>
/// 2D 애니메이션 시퀀스 찾기
/// </summary>
/// <param name="Name"></param>
/// <returns></returns>
CAnimation2DSequence* CAnimation2D::FindSequence(
	const std::string& Name)
{
	// 받아오려는 시퀀스이름 찾아 대입
	auto	iter = mSequenceMap.find(Name);

	// 이름을 못 찾았다면 종료
	if (iter == mSequenceMap.end())
		return nullptr;

	// 이름을 찾았다면 값 반환
	return iter->second;
}
