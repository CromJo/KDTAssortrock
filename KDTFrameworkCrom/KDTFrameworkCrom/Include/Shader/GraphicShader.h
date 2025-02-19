#pragma once

#include "Shader.h"

// 추상클래스 순수가상함수는 아님
class CGraphicShader abstract:
    public CShader
{
    friend class CShaderManager;

protected:
    CGraphicShader();
    virtual ~CGraphicShader();

    // Vertex Shader 등을 사용할 때
    // 입력 레이아웃이 필요하다.
    // 입력 레이아웃 : 정점 구조체가 어떤식으로 되어있는지 정의한다. (매칭하는 과정)

private:
    ID3D11InputLayout* mInputLayout = nullptr;

    // 레지스터 지정을 위한 구조체
    // ELEMENT_DESC : 레이아웃 요소 하나를 표현
    //              (포지션 1개, 색상 1개를 의미)
    std::vector<D3D11_INPUT_ELEMENT_DESC> mVecDesc;
    
    unsigned int mInputLayoutSize = 0;

    // Vertex Shader 객체
    ID3D11VertexShader* mVertexShader = nullptr;
    // Shader Code를 Compile해서 Byte Code를 가진 Buffer.
    ID3DBlob* mVertexShaderBlob = nullptr;

    ID3D11PixelShader* mPixelShader = nullptr;
    ID3DBlob* mPixelShaderBlob = nullptr;
    
    ID3D11HullShader* mHullShader = nullptr;
    ID3DBlob* mHullShaderBlob = nullptr;
    
    ID3D11DomainShader* mDomainShader = nullptr;
    ID3DBlob* mDomainShaderBlob = nullptr;
    
    ID3D11GeometryShader* mGeometryShader = nullptr;
    ID3DBlob* mGeometryShaderBlob = nullptr;
    
public:
    virtual bool Init();
    // 자식 클래스에 재정의 못하도록 final 처리
    virtual void SetShader() final;

public:
    void AddInputLayoutDesc(const char* Semantic,
        unsigned int SemanticIndex, DXGI_FORMAT Format,
        unsigned int InputSlot, unsigned int Size,
        D3D11_INPUT_CLASSIFICATION InputSlotClass,
        unsigned int InstanceDataStepRate);

    // 입력 레이아웃 생성
    bool CreateInputLayout();

    // 함수이름, 경로
    bool LoadVertexShader(const char* EntryName, 
        const TCHAR* FileName);
    bool LoadPixelShader(const char* EntryName, 
        const TCHAR* FileName);
    bool LoadHullShader(const char* EntryName, 
        const TCHAR* FileName);
    bool LoadDomainShader(const char* EntryName, 
        const TCHAR* FileName);
    bool LoadGeometryShader(const char* EntryName, 
        const TCHAR* FileName);

};

