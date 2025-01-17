#include "GraphicShader.h"
#include "../Device.h"

CGraphicShader::CGraphicShader()
{
}

CGraphicShader::~CGraphicShader()
{
    SAFE_RELEASE(mInputLayout);

    SAFE_RELEASE(mVertexShader);
    SAFE_RELEASE(mVertexShaderBlob);
    
    SAFE_RELEASE(mPixelShader);
    SAFE_RELEASE(mPixelShaderBlob);
    
    SAFE_RELEASE(mDomainShader);
    SAFE_RELEASE(mDomainShaderBlob);
    
    SAFE_RELEASE(mGeometryShader);
    SAFE_RELEASE(mGeometryShaderBlob);
    
    SAFE_RELEASE(mHullShader);
    SAFE_RELEASE(mHullShaderBlob);
}

bool CGraphicShader::Init()
{
    return true;
}

void CGraphicShader::SetShader()
{
    CDevice::GetInstance()->GetContext()->VSSetShader(mVertexShader, nullptr, 0);
    CDevice::GetInstance()->GetContext()->PSSetShader(mPixelShader, nullptr, 0);
    CDevice::GetInstance()->GetContext()->HSSetShader(mHullShader, nullptr, 0);
    CDevice::GetInstance()->GetContext()->DSSetShader(mDomainShader, nullptr, 0);
    CDevice::GetInstance()->GetContext()->GSSetShader(mGeometryShader, nullptr, 0);

    // 입력 조립기
    CDevice::GetInstance()->GetContext()->IASetInputLayout(mInputLayout);

}

void CGraphicShader::AddInputLayoutDesc(const char* Semantic, unsigned int SemanticIndex, DXGI_FORMAT Format, unsigned int InputSlot, unsigned int Size, D3D11_INPUT_CLASSIFICATION InputSlotClass, unsigned int InstanceDataStepRate)
{
    D3D11_INPUT_ELEMENT_DESC Desc = {};

    Desc.SemanticName = Semantic;
    Desc.SemanticIndex = SemanticIndex;
    Desc.Format = Format;
    Desc.InputSlot = InputSlot;
    Desc.InputSlotClass = InputSlotClass;
    Desc.InstanceDataStepRate = InstanceDataStepRate;
    Desc.AlignedByteOffset = mInputLayoutSize;

    mInputLayoutSize += Size;

    mVectorDesc.emplace_back(Desc);
}

bool CGraphicShader::CreateInputLayout()
{
    if (FAILED(CDevice::GetInstance()->GetDevice()->CreateInputLayout(&mVectorDesc[0],
        (UINT)mVectorDesc.size(), mVertexShaderBlob->GetBufferPointer(),
        mVertexShaderBlob->GetBufferSize(), &mInputLayout)))
        return false;

    return true;
}

bool CGraphicShader::LoadVertexShader(const char* EntryName, const TCHAR* FileName)
{
    TCHAR FullPath[MAX_PATH] = {};

    lstrcpy(FullPath, TEXT("../Bin/Shader/"));
    lstrcat(FullPath, FileName);

    unsigned int Flag = 0;
    
#ifdef _DEBUG
    Flag = D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* ErrorBlob = nullptr;

    if (FAILED(D3DCompileFromFile(FullPath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
        EntryName, "vs_5_0", Flag, 0, &mVertexShaderBlob , &ErrorBlob)))
    {
#ifdef _DEBUG
        char ErrorText[512] = {};
        strcpy_s(ErrorText, (const char*)ErrorBlob->GetBufferPointer());
        strcat_s(ErrorText, "\n");
        OutputDebugStringA((const char*)ErrorBlob->GetBufferPointer());
#endif // _DEBUG

        return false;
    }

    if (FAILED(CDevice::GetInstance()->GetDevice()->CreateVertexShader(
        mVertexShaderBlob->GetBufferPointer(), mVertexShaderBlob->GetBufferSize(), nullptr, &mVertexShader)))
        return false;

    return true;
}

bool CGraphicShader::LoadHullShader(const char* EntryName, const TCHAR* FileName)
{
    TCHAR FullPath[MAX_PATH] = {};

    lstrcpy(FullPath, TEXT("../Bin/Shader/"));
    lstrcat(FullPath, FileName);

    unsigned int Flag = 0;

#ifdef _DEBUG
    Flag = D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* ErrorBlob = nullptr;

    if (FAILED(D3DCompileFromFile(FullPath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
        EntryName, "hs_5_0", Flag, 0, &mHullShaderBlob, &ErrorBlob)))
    {
#ifdef _DEBUG
        char ErrorText[512] = {};
        strcpy_s(ErrorText, (const char*)ErrorBlob->GetBufferPointer());
        strcat_s(ErrorText, "\n");
        OutputDebugStringA(ErrorText);
#endif // _DEBUG

        return false;
    }

    if (FAILED(CDevice::GetInstance()->GetDevice()->CreateHullShader(
        mHullShaderBlob->GetBufferPointer(),
        mHullShaderBlob->GetBufferSize(),
        nullptr, &mHullShader)))
        return false;

    return true;
}

bool CGraphicShader::LoadPixelShader(const char* EntryName, const TCHAR* FileName)
{
    TCHAR FullPath[MAX_PATH] = {};

    lstrcpy(FullPath, TEXT("../Bin/Shader/"));
    lstrcat(FullPath, FileName);

    unsigned int Flag = 0;

#ifdef _DEBUG
    Flag = D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* ErrorBlob = nullptr;

    if (FAILED(D3DCompileFromFile(FullPath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
        EntryName, "ps_5_0", Flag, 0, &mPixelShaderBlob, &ErrorBlob)))
    {
#ifdef _DEBUG
        char ErrorText[512] = {};
        strcpy_s(ErrorText, (const char*)ErrorBlob->GetBufferPointer());
        strcat_s(ErrorText, "\n");
        OutputDebugStringA(ErrorText);
#endif // _DEBUG

        return false;
    }

    if (FAILED(CDevice::GetInstance()->GetDevice()->CreatePixelShader(
        mPixelShaderBlob->GetBufferPointer(), 
        mPixelShaderBlob->GetBufferSize(),
        nullptr, &mPixelShader)))
        return false;

    return true;
}

bool CGraphicShader::LoadDomainShader(const char* EntryName, const TCHAR* FileName)
{
    TCHAR FullPath[MAX_PATH] = {};

    lstrcpy(FullPath, TEXT("../Bin/Shader/"));
    lstrcat(FullPath, FileName);

    unsigned int Flag = 0;

#ifdef _DEBUG
    Flag = D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* ErrorBlob = nullptr;

    if (FAILED(D3DCompileFromFile(FullPath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
        EntryName, "ds_5_0", Flag, 0, &mDomainShaderBlob, &ErrorBlob)))
    {
#ifdef _DEBUG
        char ErrorText[512] = {};
        strcpy_s(ErrorText, (const char*)ErrorBlob->GetBufferPointer());
        strcat_s(ErrorText, "\n");
        OutputDebugStringA(ErrorText);
#endif // _DEBUG

        return false;
    }

    if (FAILED(CDevice::GetInstance()->GetDevice()->CreateDomainShader(
        mDomainShaderBlob->GetBufferPointer(),
        mDomainShaderBlob->GetBufferSize(),
        nullptr, &mDomainShader)))
        return false;

    return true;
}

bool CGraphicShader::LoadGeometryShader(const char* EntryName, const TCHAR* FileName)
{
    TCHAR FullPath[MAX_PATH] = {};

    lstrcpy(FullPath, TEXT("../Bin/Shader/"));
    lstrcat(FullPath, FileName);

    unsigned int Flag = 0;

#ifdef _DEBUG
    Flag = D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* ErrorBlob = nullptr;

    if (FAILED(D3DCompileFromFile(FullPath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
        EntryName, "gs_5_0", Flag, 0, &mGeometryShaderBlob, &ErrorBlob)))
    {
#ifdef _DEBUG
        char ErrorText[512] = {};
        strcpy_s(ErrorText, (const char*)ErrorBlob->GetBufferPointer());
        strcat_s(ErrorText, "\n");
        OutputDebugStringA(ErrorText);
#endif // _DEBUG

        return false;
    }

    if (FAILED(CDevice::GetInstance()->GetDevice()->CreateGeometryShader(
        mGeometryShaderBlob->GetBufferPointer(),
        mGeometryShaderBlob->GetBufferSize(),
        nullptr, &mGeometryShader)))
        return false;

    return true;
}