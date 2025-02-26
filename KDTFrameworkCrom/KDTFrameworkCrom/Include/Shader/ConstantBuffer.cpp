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

    // 상수버퍼의 경우 물체를 그릴때마다
    // 데이터가 바뀔 수 있다. 
    // (움직이면 위치값 바뀌면서, 이동횡렬이 달라지기 떄문)
    // Default보단 갱신용으로 Dynamic선언해준다.
    Desc.Usage = D3D11_USAGE_DYNAMIC;
    // 버퍼 크기 지정
    Desc.ByteWidth = Size;
    // 상수버퍼 사용한다고 바인딩한다.
    Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    // CPU에서 상수버퍼에 값을 쓰겠다고 정의함.
    Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    if (FAILED(CDevice::GetInstance()->GetDevice()->
        CreateBuffer(&Desc, nullptr, &mBuffer)))
        return false;

    return true;
}

void CConstantBuffer::Update(void* Data)
{
    // D3D11_MAPPED_SUBRESOURCE :
    //      - Buffer 안에있는 데이터를 저장하기 위한
    //          배열의 주소를 가지고 온다.
    D3D11_MAPPED_SUBRESOURCE Map = {};

    // Lock / Unlock 함수 : Map / UnMap
    // D3D11_MAP :
    //      1. READ             : 버퍼 읽기
    //      2. WRITE            : 버퍼 쓰기
    //      3. Read|Write       : 읽기/쓰기
    //      4. Write_Discard    : 
    //          기존 데이터를 버리고 갱신
    //      5. Write no Overite : 
    //          기존 데이터 유지하고 갱신
    CDevice::GetInstance()->GetContext()->Map(mBuffer,
        0, D3D11_MAP_WRITE_DISCARD, 0, &Map);

    // Data를 mSize만큼 Map.pData에 저장)
    memcpy(Map.pData, Data, mSize);

    // 위에서 인자로 들어온 데이터로 버퍼를 채워주면
    // 지정된 Shader에 상수버퍼의 데이터를 넘겨준다.
    // |연산으로 넣어줬다면 &연산으로 넣어줘야한다.
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
