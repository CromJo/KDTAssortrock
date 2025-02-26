#pragma once
#include "ConstantBufferData.h"

class CTransformCBuffer :
    public CConstantBufferData
{
public:
	CTransformCBuffer();
	CTransformCBuffer(const CTransformCBuffer& Data);
	CTransformCBuffer(CTransformCBuffer&& Data);
	virtual ~CTransformCBuffer();

private:
	FTransformCBufferInfo mData;

public:
	virtual bool Init();
	virtual void UpdateBuffer();
	virtual CTransformCBuffer* Clone();

public:
	void SetWorldMatrix(const FMatrix& matrixWorld)
	{
		mData.matrixWorld = matrixWorld;
	}
	void SetViewMatrix(const FMatrix& matrixView)
	{
		mData.matrixView = matrixView;
	}
	void SetProjectionMatrix(const FMatrix& matrixProjection)
	{
		mData.matrixProjection = matrixProjection;
	}
};

