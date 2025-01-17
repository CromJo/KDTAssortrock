#include "ConstantBuffer.h"
#include "../Device.h"

CConstantBuffer::CConstantBuffer()
{
}

CConstantBuffer::~CConstantBuffer()
{
    SAFE_DELETE(mBuffer)
}

bool CConstantBuffer::Init(int Size, int Register, int ShaderBufferType)
{
    mSize = Size;
    mRegister = 0;
    mShaderBufferType = ShaderBufferType;

    D3D11_BUFFER_DESC Desc = {};
    
    // ������۴� ���������� ���� ������ Dynamic���� ������ش�.
    Desc.Usage = D3D11_USAGE_DYNAMIC;
    // ���� ũ�⸦ �����Ѵ�.
    Desc.ByteWidth = Size;
    // ������۷� ����ϰڴٰ� ���ε��Ѵ�.
    Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    // CPU���� ������ۿ� ���� ���ڴٰ� �����Ѵ�.
    Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    if (FAILED(CDevice::GetInstance()->GetDevice()->CreateBuffer(
        &Desc, nullptr, &mBuffer)))
        return false;

    return true;
}

void CConstantBuffer::Update(void* Data)
{
    // Buffer �ȿ��ִ� �����͸� �����ϱ� ���� �迭�� �ּҸ� �����´�.
    D3D11_MAPPED_SUBRESOURCE Map = {};

    CDevice::GetInstance()->GetContext()->Map(mBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &Map);

    memcpy(Map.pData, Data, mSize);

    CDevice::GetInstance()->GetContext()->Unmap(mBuffer, 0);

    // ������ ���ڷ� ���� �����ͷ� ���۸� ä���ָ�,
    // ������ Shader�� ��������� �����͸� �Ѱ��ش�.
    if (mShaderBufferType & EShaderBufferType::Vertex)
    {
        CDevice::GetInstance()->GetContext()->VSSetConstantBuffers(mRegister, 1, &mBuffer);
    }
    if (mShaderBufferType & EShaderBufferType::Pixel)
    {
        CDevice::GetInstance()->GetContext()->PSSetConstantBuffers(mRegister, 1, &mBuffer);
    }
    if (mShaderBufferType & EShaderBufferType::Hull)
    {
        CDevice::GetInstance()->GetContext()->HSSetConstantBuffers(mRegister, 1, &mBuffer);
    }
    if (mShaderBufferType & EShaderBufferType::Domain)
    {
        CDevice::GetInstance()->GetContext()->DSSetConstantBuffers(mRegister, 1, &mBuffer);
    }
    if (mShaderBufferType & EShaderBufferType::Geometry)
    {
        CDevice::GetInstance()->GetContext()->GSSetConstantBuffers(mRegister, 1, &mBuffer);
    }
    if (mShaderBufferType & EShaderBufferType::Compute)
    {
        CDevice::GetInstance()->GetContext()->CSSetConstantBuffers(mRegister, 1, &mBuffer);
    }
}
