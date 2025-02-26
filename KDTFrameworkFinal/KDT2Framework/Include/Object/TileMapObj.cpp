#include "TileMapObj.h"
#include "../Scene/Scene.h"
#include "../Scene/Input.h"

CTileMapObj::CTileMapObj()
{
}

CTileMapObj::CTileMapObj(const CTileMapObj& Obj)    :
    CSceneObject(Obj)
{
}

CTileMapObj::CTileMapObj(CTileMapObj&& Obj) :
    CSceneObject(Obj)
{
}

CTileMapObj::~CTileMapObj()
{
}

void CTileMapObj::AddTileType()
{
    mEditTileType = (ETileType)((int)mEditTileType + 1);

    if (mEditTileType == ETileType::End)
        mEditTileType = ETileType::Normal;
}

bool CTileMapObj::Init()
{
    CSceneObject::Init();

    mTileMapRenderer = CreateComponent<CTileMapRendererComponent>();
    mTileMap = CreateComponent<CTileMapComponent>();
    
    // 타일맵 외곽선출력 세팅
    mTileMap->SetTileOutLineRender(true);

    mTileMapRenderer->SetBackTexture("TileMapBack",
        TEXT("Texture\\MapBackGround.png"));

    SetRootComponent(mTileMapRenderer);

    // 타일맵 초기 생성 64x64크기 가로세로 100칸씩
    mTileMap->CreateTile(ETileShape::Rect,
        50, 50, FVector2D(64.f, 64.f));

    return true;
}

void CTileMapObj::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);

    const FVector2D& MousePos =
        mScene->GetInput()->GetMouseWorldPos2D();

    if (mScene->GetInput()->GetMouseHold(EMouseButtonType::LButton))
    {
        mOnMousePrevTileType = mEditTileType;
        mTileMap->ChangeTileType(mEditTileType, MousePos);
    }
    
    else if (!mScene->GetInput()->GetMouseDown(EMouseButtonType::LButton))
    {
        int Index = mTileMap->GetTileIndex(MousePos);

        if (Index != mOnMousePrevIndex)
        {
            ETileType PrevType =
                mTileMap->ChangeTileType(ETileType::MouseOver, MousePos);

            if (PrevType != ETileType::None)
            {
                if (mOnMousePrevIndex != -1)
                {
                    mTileMap->ChangeTileType(mOnMousePrevTileType,
                        mOnMousePrevIndex);
                }

                mOnMousePrevIndex = mTileMap->GetTileIndex(MousePos);
                mOnMousePrevTileType = PrevType;
            }

            else
            {
                mTileMap->ChangeTileType(mOnMousePrevTileType,
                    mOnMousePrevIndex);
                mOnMousePrevTileType = ETileType::None;
                mOnMousePrevIndex = -1;
            }
        }
    }
}
