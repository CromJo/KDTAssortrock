#include "UserWidget.h"

CUserWidget::CUserWidget()
{
}

CUserWidget::~CUserWidget()
{
}

bool CUserWidget::Init()
{
    CWidget::Init();

    return true;
}

void CUserWidget::Update(float DeltaTime)
{
    CWidget::Update(DeltaTime);

    // 위젯 목록의 시작과 끝을 추가.
    auto    iter = mWidgetList.begin();
    auto    iterEnd = mWidgetList.end();

    // 위젯목록의 end까지 도달하지 못했다면 반복
    for (; iter != iterEnd;)
    {
        // N번째 오브젝트 활성화가 안되어있다면
        if (!(*iter)->IsActive())
        {
            // 위젯목록에서 지우고
            iter = mWidgetList.erase(iter);
            // end 새로고침 해주고 (위에서 1개 지웠으니)
            iterEnd = mWidgetList.end();
            // 다시 돌려
            continue;
        }

        // N번째 오브젝트가 활성화는 되어있는데 보이지 않는 상태면
        else if (!(*iter)->IsEnable())
        {
            // 다음거 계산하기 위해 빠른 for문으로 return
            ++iter;
            continue;
        }

        // 활성화가 전체적으로 되어있다면 
        // N번째 오브젝트 업데이트 돌려줌
        (*iter)->Update(DeltaTime);
        ++iter;
    }
}

void CUserWidget::Render()
{
    CWidget::Render();

    if (mWidgetList.size() >= 2)
    {
        std::sort(mWidgetList.begin(), mWidgetList.end(),
            CUserWidget::SortRender);
    }

    auto    iter = mWidgetList.begin();
    auto    iterEnd = mWidgetList.end();

    for (; iter != iterEnd;)
    {
        if (!(*iter)->IsActive())
        {
            iter = mWidgetList.erase(iter);
            iterEnd = mWidgetList.end();
            continue;
        }

        else if (!(*iter)->IsEnable())
        {
            ++iter;
            continue;
        }

        (*iter)->Render();
        ++iter;
    }
}

void CUserWidget::Render(const FVector3D& Pos)
{
    CWidget::Render(Pos);

    if (mWidgetList.size() >= 2)
    {
        std::sort(mWidgetList.begin(), mWidgetList.end(),
            CUserWidget::SortRender);
    }

    auto    iter = mWidgetList.begin();
    auto    iterEnd = mWidgetList.end();

    for (; iter != iterEnd;)
    {
        if (!(*iter)->IsActive())
        {
            iter = mWidgetList.erase(iter);
            iterEnd = mWidgetList.end();
            continue;
        }

        else if (!(*iter)->IsEnable())
        {
            ++iter;
            continue;
        }

        (*iter)->Render(Pos);
        ++iter;
    }
}

bool CUserWidget::CollisionMouse(CWidget** Result, const FVector2D& MousePos)
{
    if (mWidgetList.size() >= 2)
    {
        std::sort(mWidgetList.begin(), mWidgetList.end(),
            CUserWidget::SortCollision);
    }

    auto    iter = mWidgetList.begin();
    auto    iterEnd = mWidgetList.end();

    for (; iter != iterEnd;)
    {
        if (!(*iter)->IsActive())
        {
            iter = mWidgetList.erase(iter);
            iterEnd = mWidgetList.end();
            continue;
        }
        ++iter;
    }

    auto    riter = mWidgetList.rbegin();
    auto    riterEnd = mWidgetList.rend();

    for (; riter != riterEnd;)
    {
        if (!(*riter)->IsEnable())
        {
            ++riter;
            continue;
        }

        if ((*riter)->CollisionMouse(Result, MousePos))
        {
            return true;
        }
        ++riter;
    }

    return false;
}

bool CUserWidget::SortCollision(const CSharedPtr<CWidget>& Src,
    const CSharedPtr<CWidget>& Dest)
{
    return Src->GetZOrder() < Dest->GetZOrder();
}

bool CUserWidget::SortRender(const CSharedPtr<CWidget>& Src, 
    const CSharedPtr<CWidget>& Dest)
{
    return Src->GetZOrder() < Dest->GetZOrder();
}
