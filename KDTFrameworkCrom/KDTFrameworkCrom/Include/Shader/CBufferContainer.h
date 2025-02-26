#pragma once

#include "../Vector2D.h"
#include "../Vector3D.h"
#include "../Vector4D.h"
#include "../Matrix.h"

// 16바이트 단위로 맞춰서 사용해야한다
struct FTransformCBufferInfo
{
	FMatrix matrixWorld;
	FMatrix matrixView;
	FMatrix matrixProjection;
	FMatrix matrixWV;
	FMatrix matrixWVP;
	
	// 만약 16바이트 단위가 아니라면
	// 16byte가 되도록 빈데이터를 넣어서 사용해야한다.
	// FVector3D test;
	// float empty1;
};