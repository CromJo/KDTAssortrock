﻿#pragma once

#include "SceneObject.h"
#include "../Component/TileMapComponent.h"
#include "../Component/TileMapRendererComponent.h"

class CTileMapObj :
    public CSceneObject
{
    friend class CScene;

protected:
    CTileMapObj();
    CTileMapObj(const CTileMapObj& Obj);
    CTileMapObj(CTileMapObj&& Obj);
    virtual ~CTileMapObj();

private:
    CSharedPtr<CTileMapRendererComponent>   mTileMapRenderer;
    CSharedPtr<CTileMapComponent>   mTileMap;

public:
    CTileMapComponent* GetTileMap() const
    {
        return mTileMap;
    }

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

public:
    void Save(const TCHAR* FullPath);
    void Load(const TCHAR* FullPath);
};

