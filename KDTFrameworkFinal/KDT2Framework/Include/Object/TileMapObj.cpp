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

bool CTileMapObj::Init()
{
    CSceneObject::Init();

    mTileMapRenderer = CreateComponent<CTileMapRendererComponent>();
    mTileMap = CreateComponent<CTileMapComponent>();

    // 외곽선 그려주도록 설정
    mTileMap->SetTileOutLineRender(true);
    
    //mTileMapRenderer->SetBackTexture("TileMapBack",
    //    TEXT("Texture\\Background\\Nikke_Background.png"));

    mTileMapRenderer->SetTileTexture("Tile",
        TEXT("Texture\\Floors.png"));
   /* mTileMapRenderer->SetTileTexture("Tile",
        TEXT("Texture\\Diablos_Lair_Floor_TRS\\Diablos_Lair_Floor.png"));*/

    /*for (int i = 0; i < 76; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            mTileMap->AddTileTextureFrame(j * 160.f, 
                i * 80.f,
                160.f, 80.f);
        }
    }*/

    // Floor 텍스쳐 자른 것 추가 해주는? 그런 기능인 느낌
    mTileMap->AddTileTextureFrame(0.f, 0.f, 64.f, 64.f);
    mTileMap->AddTileTextureFrame(0.f, 64.f, 64.f, 64.f);
    mTileMap->AddTileTextureFrame(0.f, 128.f, 64.f, 64.f);
    mTileMap->AddTileTextureFrame(0.f, 192.f, 64.f, 64.f);
    mTileMap->AddTileTextureFrame(0.f, 256.f, 64.f, 64.f);

    SetRootComponent(mTileMapRenderer);

    mTileMap->CreateTile(ETileShape::Rect,
        100, 100, FVector2D(64.f, 64.f), -1);
    /*mTileMap->CreateTile(ETileShape::Isometric,
        100, 100, FVector2D(160.f, 80.f), 3);*/

    return true;
}

void CTileMapObj::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);
}

void CTileMapObj::Save(const TCHAR* FullPath)
{
    mTileMap->Save(FullPath);
}

void CTileMapObj::Load(const TCHAR* FullPath)
{
    mTileMap->Load(FullPath);
}
