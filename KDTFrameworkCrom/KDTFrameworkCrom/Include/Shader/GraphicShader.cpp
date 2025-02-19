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
    
    SAFE_RELEASE(mHullShader);
    SAFE_RELEASE(mHullShaderBlob);
    
    SAFE_RELEASE(mDomainShader);
    SAFE_RELEASE(mDomainShaderBlob);
    
    SAFE_RELEASE(mGeometryShader);
    SAFE_RELEASE(mGeometryShaderBlob);
}

bool CGraphicShader::Init()
{
    return true;
}

// 어떤 물체를 출력하기전 이 함수를 먼저 호출해서,
// 출력에 사용하고자 하는 쉐이더들을 렌더링파이프라인에 
// 등록 후 출력하라는 명령을 위한 함수
void CGraphicShader::SetShader()
{
    CDevice::GetInstance()->GetContext()->VSSetShader(mVertexShader, nullptr, 0);
    CDevice::GetInstance()->GetContext()->PSSetShader(mPixelShader, nullptr, 0);
    CDevice::GetInstance()->GetContext()->HSSetShader(mHullShader, nullptr, 0);
    CDevice::GetInstance()->GetContext()->DSSetShader(mDomainShader, nullptr, 0);
    CDevice::GetInstance()->GetContext()->GSSetShader(mGeometryShader, nullptr, 0);

    // IA : 입력 조립기
    // RS : Resterise
    // OA : 아웃풋
    // OM :
    CDevice::GetInstance()->GetContext()->
        IASetInputLayout(mInputLayout);
}

void CGraphicShader::AddInputLayoutDesc(
    const char* Semantic, unsigned int SemanticIndex, 
    DXGI_FORMAT Format, unsigned int InputSlot, 
    unsigned int Size, 
    D3D11_INPUT_CLASSIFICATION InputSlotClass,
    unsigned int InstanceDataStepRate)
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

    mVecDesc.emplace_back(Desc);

    /*
    UINT AlignedByteOffset;
    */
}

bool CGraphicShader::CreateInputLayout()
{
    if(FAILED(CDevice::GetInstance()->GetDevice()->CreateInputLayout(&mVecDesc[0],
        (UINT)mVecDesc.size(), mVertexShaderBlob->GetBufferPointer(),
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
#endif // Debug

    // 쉐이더 컴파일이 문법적으로 오류가 났을 때,
    // 에러문자가 이곳으로 들어온다.
    ID3DBlob* ErrorBlob = nullptr;

    // 파일로부터 컴파일을 하는 함수
    // 컴파일 실패시 ErrorBlob에 문자가 들어가있다.
    if(FAILED(D3DCompileFromFile(FullPath, nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE, EntryName,
        "vs_5_0", Flag, 0, &mVertexShaderBlob, &ErrorBlob)))
    {
#ifdef _DEBUG
        char ErrorText[512] = {};

        strcpy_s(ErrorText, (const char*)ErrorBlob->GetBufferPointer());
        strcat_s(ErrorText, "\n");
        // 이 Buffer의 메모리주소를 가지고와서
        // 문자열 포인트로 바꿔서 넣으면 문자열이 출력된다.
        OutputDebugStringA(ErrorText);
#endif

        return false;
    }

    // GetBufferPointer()   : 컴파일된 코드
    // GetBufferSize()      : 컴파일된 코드의 크기
    if (FAILED(CDevice::GetInstance()->GetDevice()->CreateVertexShader(
        mVertexShaderBlob->GetBufferPointer(),
        mVertexShaderBlob->GetBufferSize(),
        nullptr, &mVertexShader)))
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
#endif // Debug

    // 쉐이더 컴파일이 문법적으로 오류가 났을 때,
    // 에러문자가 이곳으로 들어온다.
    ID3DBlob* ErrorBlob = nullptr;

    // 파일로부터 컴파일을 하는 함수
    // 컴파일 실패시 ErrorBlob에 문자가 들어가있다.
    if (FAILED(D3DCompileFromFile(FullPath, nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE, EntryName,
        "ps_5_0", Flag, 0, &mPixelShaderBlob, &ErrorBlob)))
    {
#ifdef _DEBUG
        char ErrorText[512] = {};

        strcpy_s(ErrorText, (const char*)ErrorBlob->GetBufferPointer());
        strcat_s(ErrorText, "\n");
        // 이 Buffer의 메모리주소를 가지고와서
        // 문자열 포인트로 바꿔서 넣으면 문자열이 출력된다.
        OutputDebugStringA(ErrorText);
#endif

        return false;
    }

    // GetBufferPointer()   : 컴파일된 코드
    // GetBufferSize()      : 컴파일된 코드의 크기
    if (FAILED(CDevice::GetInstance()->GetDevice()->CreatePixelShader(
        mPixelShaderBlob->GetBufferPointer(),
        mPixelShaderBlob->GetBufferSize(),
        nullptr, &mPixelShader)))
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
#endif // Debug

    // 쉐이더 컴파일이 문법적으로 오류가 났을 때,
    // 에러문자가 이곳으로 들어온다.
    ID3DBlob* ErrorBlob = nullptr;

    // 파일로부터 컴파일을 하는 함수
    // 컴파일 실패시 ErrorBlob에 문자가 들어가있다.
    if (FAILED(D3DCompileFromFile(FullPath, nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE, EntryName,
        "vs_5_0", Flag, 0, &mHullShaderBlob, &ErrorBlob)))
    {
#ifdef _DEBUG
        char ErrorText[512] = {};

        strcpy_s(ErrorText, (const char*)ErrorBlob->GetBufferPointer());
        strcat_s(ErrorText, "\n");
        // 이 Buffer의 메모리주소를 가지고와서
        // 문자열 포인트로 바꿔서 넣으면 문자열이 출력된다.
        OutputDebugStringA(ErrorText);
#endif

        return false;
    }

    // GetBufferPointer()   : 컴파일된 코드
    // GetBufferSize()      : 컴파일된 코드의 크기
    if (FAILED(CDevice::GetInstance()->GetDevice()->CreateHullShader(
        mHullShaderBlob->GetBufferPointer(),
        mHullShaderBlob->GetBufferSize(),
        nullptr, &mHullShader)))
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
#endif // Debug

    // 쉐이더 컴파일이 문법적으로 오류가 났을 때,
    // 에러문자가 이곳으로 들어온다.
    ID3DBlob* ErrorBlob = nullptr;

    // 파일로부터 컴파일을 하는 함수
    // 컴파일 실패시 ErrorBlob에 문자가 들어가있다.
    if (FAILED(D3DCompileFromFile(FullPath, nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE, EntryName,
        "vs_5_0", Flag, 0, &mDomainShaderBlob, &ErrorBlob)))
    {
#ifdef _DEBUG
        char ErrorText[512] = {};

        strcpy_s(ErrorText, (const char*)ErrorBlob->GetBufferPointer());
        strcat_s(ErrorText, "\n");
        // 이 Buffer의 메모리주소를 가지고와서
        // 문자열 포인트로 바꿔서 넣으면 문자열이 출력된다.
        OutputDebugStringA(ErrorText);
#endif

        return false;
    }

    // GetBufferPointer()   : 컴파일된 코드
    // GetBufferSize()      : 컴파일된 코드의 크기
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
#endif // Debug

    // 쉐이더 컴파일이 문법적으로 오류가 났을 때,
    // 에러문자가 이곳으로 들어온다.
    ID3DBlob* ErrorBlob = nullptr;

    // 파일로부터 컴파일을 하는 함수
    // 컴파일 실패시 ErrorBlob에 문자가 들어가있다.
    if (FAILED(D3DCompileFromFile(FullPath, nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE, EntryName,
        "vs_5_0", Flag, 0, &mGeometryShaderBlob, &ErrorBlob)))
    {
#ifdef _DEBUG
        char ErrorText[512] = {};

        strcpy_s(ErrorText, (const char*)ErrorBlob->GetBufferPointer());
        strcat_s(ErrorText, "\n");
        // 이 Buffer의 메모리주소를 가지고와서
        // 문자열 포인트로 바꿔서 넣으면 문자열이 출력된다.
        OutputDebugStringA(ErrorText);
#endif

        return false;
    }

    // GetBufferPointer()   : 컴파일된 코드
    // GetBufferSize()      : 컴파일된 코드의 크기
    if (FAILED(CDevice::GetInstance()->GetDevice()->CreateGeometryShader(
        mGeometryShaderBlob->GetBufferPointer(),
        mGeometryShaderBlob->GetBufferSize(),
        nullptr, &mGeometryShader)))
        return false;

    return true;
}
