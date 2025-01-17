#pragma once
#include "../Vector2D.h"
#include "../Vector3D.h"
#include "../Vector4D.h"
#include "../Matrix.h"

// 바이트 패딩을 16byte단위로 맞추는게 좋다.
struct FTransformCBufferInfo
{
	FMatrix matWorld;
	FMatrix matView;
	FMatrix matProj;
	FMatrix matWV;
	FMatrix matWVP;
};