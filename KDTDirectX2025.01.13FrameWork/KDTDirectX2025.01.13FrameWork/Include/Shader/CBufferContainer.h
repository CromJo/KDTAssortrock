#pragma once
#include "../Vector2D.h"
#include "../Vector3D.h"
#include "../Vector4D.h"
#include "../Matrix.h"

// ����Ʈ �е��� 16byte������ ���ߴ°� ����.
struct FTransformCBufferInfo
{
	FMatrix matWorld;
	FMatrix matView;
	FMatrix matProj;
	FMatrix matWV;
	FMatrix matWVP;
};