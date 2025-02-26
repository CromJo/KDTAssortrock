#pragma once

#include "SceneComponent.h"
#include "../UI/Widget.h"

class CWidgetComponent :
    public CSceneComponent
{
	// 위젯 컴포넌트 추가 데이터 사용가능
	friend class CScene;
	friend class CSceneObject;

protected:
	CWidgetComponent();
	CWidgetComponent(const CWidgetComponent& Com);
	CWidgetComponent(CWidgetComponent&& Com);
	virtual ~CWidgetComponent();

protected:
	CSharedPtr<CWidget>	mWidget;	

public:
	void SetWidget(CWidget* Widget)
	{
		mWidget = Widget;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render();
};

