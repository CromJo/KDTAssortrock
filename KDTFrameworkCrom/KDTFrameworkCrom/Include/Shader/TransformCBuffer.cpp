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

// ���� ������ �������
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
    // �� ��ü�� �����ؼ� �ϳ� ����� ��� 
    return new CTransformCBuffer(*this);
}
