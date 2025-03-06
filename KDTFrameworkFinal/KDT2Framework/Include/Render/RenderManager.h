#pragma once

#include "../GameInfo.h"

// 구조체
struct FRenderLayer
{
	std::list<CSharedPtr<class CSceneComponent>>	RenderList;
	int			ZOrder = 0;
};

class CRenderManager
{
private:
	class CRenderStateManager* mStateManager = nullptr;
	// 키와 값으로 이루어진 데이터
	std::map<int, FRenderLayer*>			mLayerList;
	// 키와 값인데
	std::unordered_map<std::string, int>	mLayerNameList;
	ERenderSortType	mRenderSortType = ERenderSortType::Alpha;
	ID3D11SamplerState* mSampler = nullptr;
	class CRenderState* mAlphaBlend = nullptr;
	class CRenderState* mDepthDisable = nullptr;		// 픽셀의 깊이 (물체의 깊이가 아님)
	CSharedPtr<class CWidget>	mMouseWidget;
	bool mRenderModified = false;

public:
	class CRenderStateManager* GetStateManager()
	{
		return mStateManager;
	}

	void SetSortType(ERenderSortType Type)
	{
		mRenderSortType = Type;
	}

	void AddRenderList(class CSceneComponent* Component);
	void ClearRenderList();
	void SetMouseWidget(class CWidget* Widget);

public:
	bool Init();
	void Update(float DeltaTime);
	void Render();
	void RefreshLayer();
	void SetRenderModified(bool modified);

public:
	bool CreateRenderLayer(const std::string& Name,
		int ZOrder);

private:
	FRenderLayer* FindLayer(const std::string& Name);

private:
	static bool SortY(const CSharedPtr<class CSceneComponent>& Src,
		const CSharedPtr<class CSceneComponent>& Dest);

	static bool SortAlpha(const CSharedPtr<class CSceneComponent>& Src,
		const CSharedPtr<class CSceneComponent>& Dest);

	DECLARE_SINGLE(CRenderManager)
};

