﻿#pragma once

#include "../Vector2D.h"
#include "../Vector3D.h"
#include "../Vector4D.h"
#include "../Matrix.h"

struct FTransformCBufferInfo
{
    FMatrix matWorld;
    FMatrix matView;
    FMatrix matProj;
    FMatrix matWV;
    FMatrix matWVP;
    FVector3D   Pivot;
    //FVector3D   Scale;
    float       Empty;
    //float       Empty2;
};

struct FMaterialCBufferInfo
{
    FVector4D BaseColor;
    float Opacity;
    int TextureWidth;
    int TextureHeight;
    float Empty;
};

struct FColliderCBufferInfo
{
    FVector4D   Color;
};

struct FSpriteCBufferInfo
{
    FVector4D   Tint;
    FVector4D   IgnoreColor;
};

struct FAnimation2DCBufferInfo
{
    FVector2D   LTUV;
    FVector2D   RBUV;
    int         AnimEnable;
    int         AnimReverseX;
    FVector2D   Empty;
};

struct FUICBufferInfo
{
    FVector4D   BrushTint;
    FVector4D   Color = FVector4D::White;
    FVector2D   LTUV;
    FVector2D   RBUV;
    int         BrushAnimEnable;
    int         BrushTextureEnable;
    FVector2D   BrushEmpty;
};

struct FTileMapCBufferInfo
{
    FVector2D   LTUV;
    FVector2D   RBUV;
};