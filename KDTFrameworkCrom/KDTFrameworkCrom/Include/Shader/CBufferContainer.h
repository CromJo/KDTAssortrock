#pragma once

#include "../Vector2D.h"
#include "../Vector3D.h"
#include "../Vector4D.h"
#include "../Matrix.h"

// 16����Ʈ ������ ���缭 ����ؾ��Ѵ�
struct FTransformCBufferInfo
{
	FMatrix matrixWorld;
	FMatrix matrixView;
	FMatrix matrixProjection;
	FMatrix matrixWV;
	FMatrix matrixWVP;
	
	// ���� 16����Ʈ ������ �ƴ϶��
	// 16byte�� �ǵ��� �����͸� �־ ����ؾ��Ѵ�.
	// FVector3D test;
	// float empty1;
};