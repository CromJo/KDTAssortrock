#include "ConstantBuffer.h"
#include "../Device.h"

CConstantBuffer::CConstantBuffer()
{
}

CConstantBuffer::~CConstantBuffer()
{
    SAFE_RELEASE(mBuffer);
}

bool CConstantBuffer::Init(int Size, int Register, int ShaderBufferType)
{
    mSize = Size;
    mRegister = Register;
    mShaderBufferType = ShaderBufferType;

    D3D11_BUFFER_DESC Desc = {};

    // ��������� ��� ��ü�� �׸�������
    // �����Ͱ� �ٲ� �� �ִ�. 
    // (�����̸� ��ġ�� �ٲ�鼭, �̵�Ⱦ���� �޶����� ����)
    // Default���� ���ſ����� Dynamic�������ش�.
    Desc.Usage = D3D11_USAGE_DYNAMIC;
    // ���� ũ�� ����
    Desc.ByteWidth = Size;
    // ������� ����Ѵٰ� ���ε��Ѵ�.
    Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    // CPU���� ������ۿ� ���� ���ڴٰ� ������.
    Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    if (FAILED(CDevice::GetInstance()->GetDevice()->
        CreateBuffer(&Desc, nullptr, &mBuffer)))
        return false;

    return true;
}

void CConstantBuffer::Update(void* Data)
{
    // D3D11_MAPPED_SUBRESOURCE :
    //      - Buffer �ȿ��ִ� �����͸� �����ϱ� ����
    //          �迭�� �ּҸ� ������ �´�.
    D3D11_MAPPED_SUBRESOURCE Map = {};

    // Lock / Unlock �Լ� : Map / UnMap
    // D3D11_MAP :
    //      1. READ             : ���� �б�
    //      2. WRITE            : ���� ����
    //      3. Read|Write       : �б�/����
    //      4. Write_Discard    : 
    //          ���� �����͸� ������ ����
    //      5. Write no Overite : 
    //          ���� ������ �����ϰ� ����
    CDevice::GetInstance()->GetContext()->Map(mBuffer,
        0, D3D11_MAP_WRITE_DISCARD, 0, &Map);

    // Data�� mSize��ŭ Map.pData�� ����)
    memcpy(Map.pData, Data, mSize);

    // ������ ���ڷ� ���� �����ͷ� ���۸� ä���ָ�
    // ������ Shader�� ��������� �����͸� �Ѱ��ش�.
    // |�������� �־���ٸ� &�������� �־�����Ѵ�.
    if (mShaderBufferType & EShaderBufferType::Vertex)
    {
        CDevice::GetInstance()->GetContext()->
            VSSetConstantBuffers(mRegister, 1, &mBuffer);
    }

    if (mShaderBufferType & EShaderBufferType::Pixel)
    {
        CDevice::GetInstance()->GetContext()->
            PSSetConstantBuffers(mRegister, 1, &mBuffer);
    }

    if (mShaderBufferType & EShaderBufferType::Hull)
    {
        CDevice::GetInstance()->GetContext()->
            HSSetConstantBuffers(mRegister, 1, &mBuffer);
    }

    if (mShaderBufferType & EShaderBufferType::Domain)
    {
        CDevice::GetInstance()->GetContext()->
            DSSetConstantBuffers(mRegister, 1, &mBuffer);
    }

    if (mShaderBufferType & EShaderBufferType::Geometry)
    {
        CDevice::GetInstance()->GetContext()->
            GSSetConstantBuffers(mRegister, 1, &mBuffer);
    }

    if (mShaderBufferType & EShaderBufferType::Compute)
    {
        CDevice::GetInstance()->GetContext()->
            CSSetConstantBuffers(mRegister, 1, &mBuffer);
    }

}
