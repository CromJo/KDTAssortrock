#include "RenderManager.h"
#include "RenderStateManager.h"
#include "RenderState.h"
#include "../Component/SceneComponent.h"
#include "../Device.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneManager.h"
#include "../Scene/SceneUIManager.h"
#include "../UI/UserWidget/MouseWidget.h"

DEFINITION_SINGLE(CRenderManager)

CRenderManager::CRenderManager()
{
}

/// <summary>
/// 메모리 해제
/// </summary>
CRenderManager::~CRenderManager()
{
	auto	iter = mLayerList.begin();
	auto	iterEnd = mLayerList.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}

	SAFE_RELEASE(mSampler);
	SAFE_DELETE(mStateManager);
}

/// <summary>
/// 출력할 목록 추가 기능
/// 1. 출력할 레이어를 받아온다.
/// 2. 있다면 출력할 레이어를 목록에 추가해준다.
/// </summary>
/// <param name="Component"></param>
void CRenderManager::AddRenderList(CSceneComponent* Component)
{
	FRenderLayer* Layer = FindLayer(Component->GetRenderLayerName());

	if (!Layer)
		return;

	mRenderModified = true;

	Layer->RenderList.emplace_back(Component);
}

/// <summary>
/// 렌더 목록 초기화 기능
/// 1. 목록들을 지운다.
///		- 다만 SharedPointer로 되어있으므로,
///			메모리 해제가 되진 않는다. (맞나? 체크해보셈)
/// </summary>
void CRenderManager::ClearRenderList()
{
	auto	iter = mLayerList.begin();
	auto	iterEnd = mLayerList.end();

	for (; iter != iterEnd; ++iter)
	{
		iter->second->RenderList.clear();
	}
}

/// <summary>
/// 마우스 이미지 설정 함수
/// </summary>
/// <param name="Widget"></param>
void CRenderManager::SetMouseWidget(CWidget* Widget)
{
	mMouseWidget = Widget;

	if (mMouseWidget)
		ShowCursor(FALSE);

	else
		ShowCursor(TRUE);
}

bool CRenderManager::Init()
{
	CreateRenderLayer("BackGround", INT_MIN);
	CreateRenderLayer("Object", 0);
	CreateRenderLayer("Enemy", 1);
	CreateRenderLayer("GaugeBar", 50);
	CreateRenderLayer("Collider", INT_MAX);

	mStateManager = new CRenderStateManager;

	mStateManager->Init();

	D3D11_SAMPLER_DESC	Desc = {};

	Desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	Desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	Desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	Desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	Desc.MipLODBias = 0.f;
	Desc.MaxAnisotropy = 1;
	Desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	Desc.MinLOD = -FLT_MAX;
	Desc.MaxLOD = FLT_MAX;

	if (FAILED(CDevice::GetInst()->GetDevice()->CreateSamplerState(
		&Desc, &mSampler)))
		return false;

	mAlphaBlend = mStateManager->FindState("AlphaBlend");

	mDepthDisable = mStateManager->FindState("DepthDisable");

	// 여기서 마우스 아이콘 설정을 해주는 부분이다. 
	// 이름을 바꾸든 파일을 바꾸든 둘중하나 택1
	mMouseWidget = CSceneUIManager::CreateWidgetStatic<CMouseWidget>("Mouse");

	// 마우스 위젯 출력 구문
	//ShowCursor(FALSE);

	return true;
}

void CRenderManager::Update(float DeltaTime)
{
	if (mMouseWidget)
		mMouseWidget->Update(DeltaTime);

	//refreshLayer
	RefreshLayer();
}

// 출력 기능
void CRenderManager::Render()
{
	CDevice::GetInst()->GetContext()->PSSetSamplers(0,
		1, &mSampler);

	mAlphaBlend->SetState();

	mDepthDisable->SetState();

	auto	iter = mLayerList.begin();
	auto	iterEnd = mLayerList.end();

	for (; iter != iterEnd; ++iter)
	{
		FRenderLayer* Layer = iter->second;

		switch (mRenderSortType)
		{
		case ERenderSortType::None:
			break;
		case ERenderSortType::Y:
			if (Layer->RenderList.size() > 1)
				Layer->RenderList.sort(CRenderManager::SortY);
			break;
		case ERenderSortType::Alpha:
			if (Layer->RenderList.size() > 1)
				Layer->RenderList.sort(CRenderManager::SortAlpha);
			break;
		}

		auto	iter1 = Layer->RenderList.begin();
		auto	iter1End = Layer->RenderList.end();

		for (; iter1 != iter1End;)
		{
			if (!(*iter1)->IsActive())
			{
				iter1 = Layer->RenderList.erase(iter1);
				iter1End = Layer->RenderList.end();
				continue;
			}

			else if (!(*iter1)->IsEnable())
			{
				++iter1;
				continue;
			}

			(*iter1)->PreRender();

			(*iter1)->Render();

			(*iter1)->PostRender();

			++iter1;
		}
	}

	// UI 출력
	CSceneManager::GetInst()->RenderUI();


	// 마우스 출력
	if (mMouseWidget)
		mMouseWidget->Render();

	mDepthDisable->ResetState();

	mAlphaBlend->ResetState();
}

void CRenderManager::RefreshLayer()
{
	if (!mRenderModified)
		return;

	std::map<int, FRenderLayer*>::iterator it = mLayerList.begin();
	std::map<int, FRenderLayer*>::iterator itEnd = mLayerList.end();

	// mLayerList가 마지막 순서가 될 때까지 실행
	while (it != itEnd)
	{
		// mLayerList의 값을 받아온다.
		FRenderLayer* itVal = it->second;
		
		// mLayerList값의 RenderList값을 넣어준다.
		std::list<CSharedPtr<class CSceneComponent>>::iterator subIt = itVal->RenderList.begin();
		std::list<CSharedPtr<class CSceneComponent>>::iterator subItEnd = itVal->RenderList.end();

		// RenderList가 마지막 순서가 될때까지 실행
		//for (;subIt != subItEnd; )
		while (subIt != subItEnd)
		{
			// 현재 subIt의 Object 데이터를 넣어준다.
			CSharedPtr<CSceneComponent> subItVal = subIt->Get();
			if (subItVal->GetScene() == nullptr)
				return;

			// Object Data의 레이어명칭을 받아온다.
			FRenderLayer* foundLayer = FindLayer(subItVal->GetRenderLayerName());

			// 레이어명칭이 없다면
			if (foundLayer == nullptr)
			{
				// 다음 Object로 넘겨준다.
				subIt++;
				continue;
			}

			// 레이어값이 레이어목록과 일치한다면
			if (foundLayer->ZOrder == it->first)
			{
				// 다음 Object로 넘겨준다.
				subIt++;
				continue;
			}

			// 레이어의 값이 존재하고 일치하지 않으면
			//======================
			// 렌더목록에 레이어목록의 값을 추가
			foundLayer->RenderList.emplace_back(subItVal); 
			subIt = itVal->RenderList.erase(subIt);

			//======================
			continue;
		}

		it++;
	}

	mRenderModified = false;
}

void CRenderManager::SetRenderModified(bool modified)
{
	mRenderModified = modified;
}

// 레이어번호를 생성하는 함수
bool CRenderManager::CreateRenderLayer(const std::string& Name, 
	int ZOrder)
{
	// 현재 레이어의 키값을 받아온다
	FRenderLayer* Layer = FindLayer(Name);

	// 있으면 종료
	if (Layer)
		return false;

	// 없으면 렌더레이어를 생성해주고
	Layer = new FRenderLayer;

	// ZOrder값을 설정할 값으로 변경
	Layer->ZOrder = ZOrder;

	// 레이어목록에 ZOrder값이 설정된 Layer의 값을 추가해준다.
	mLayerList.insert(std::make_pair(ZOrder, Layer));
	// 레이어 키값의 배열안에 ZOrder값을 넣어준다.
	mLayerNameList[Name] = ZOrder;

	return true;
}

// 레이어 찾는 함수
FRenderLayer* CRenderManager::FindLayer(const std::string& Name)
{
	// 찾을 레이어 네임을 넣어주는데
	auto	iter1 = mLayerNameList.find(Name);

	// 있고, 마지막배열이라면 null주소 반환
	if (iter1 == mLayerNameList.end())
		return nullptr;

	// 없다면 찾은 레이어의 값으로 ZOrder값을 설정 
	int	ZOrder = iter1->second;

	// 레이어목록의 번호를 찾고
	auto	iter = mLayerList.find(ZOrder);

	// 값 반환
	return iter->second;
}

bool CRenderManager::SortY(
	const CSharedPtr<class CSceneComponent>& Src, 
	const CSharedPtr<class CSceneComponent>& Dest)
{
	float SrcY = Src->GetWorldPosition().y -
		Src->GetWorldScale().y * Src->GetPivot().y;

	float DestY = Dest->GetWorldPosition().y -
		Dest->GetWorldScale().y * Dest->GetPivot().y;

	return SrcY > DestY;
}

bool CRenderManager::SortAlpha(
	const CSharedPtr<class CSceneComponent>& Src, 
	const CSharedPtr<class CSceneComponent>& Dest)
{
	return false;
}
