#include "TransformCBuffer.h"


CTransformCBuffer::CTransformCBuffer()
{
}

CTransformCBuffer::CTransformCBuffer(const CTransformCBuffer& Data) :
    CConstantBufferData(Data),
    mData(Data.mData)
{
}

CTransformCBuffer::CTransformCBuffer(CTransformCBuffer&& Data) :
    CConstantBufferData(Data),
    mData(Data.mData)
 {
}

CTransformCBuffer::~CTransformCBuffer()
{
}

bool CTransformCBuffer::Init()
{
    // 
    SetConstantBuffer("Transform");

    return true;
}

// 최종 데이터 만들어짐
void CTransformCBuffer::UpdateBuffer()
{
    mData.matrixWV = mData.matrixWorld * mData.matrixView;
    mData.matrixWVP = mData.matrixWV * mData.matrixProjection;

    mData.matrixWorld.Transpose();
    mData.matrixView.Transpose();
    mData.matrixProjection.Transpose();
    mData.matrixWV.Transpose();
    mData.matrixWVP.Transpose();
    
    mBuffer->Update(&mData);
}

CTransformCBuffer* CTransformCBuffer::Clone()
{
    // 이 자체를 복제해서 하나 만드는 기능 
    return new CTransformCBuffer(*this);
}
