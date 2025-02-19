#pragma once

#include "Shader.h"

// �߻�Ŭ���� ���������Լ��� �ƴ�
class CGraphicShader abstract:
    public CShader
{
    friend class CShaderManager;

protected:
    CGraphicShader();
    virtual ~CGraphicShader();

    // Vertex Shader ���� ����� ��
    // �Է� ���̾ƿ��� �ʿ��ϴ�.
    // �Է� ���̾ƿ� : ���� ����ü�� ������� �Ǿ��ִ��� �����Ѵ�. (��Ī�ϴ� ����)

private:
    ID3D11InputLayout* mInputLayout = nullptr;

    // �������� ������ ���� ����ü
    // ELEMENT_DESC : ���̾ƿ� ��� �ϳ��� ǥ��
    //              (������ 1��, ���� 1���� �ǹ�)
    std::vector<D3D11_INPUT_ELEMENT_DESC> mVecDesc;
    
    unsigned int mInputLayoutSize = 0;

    // Vertex Shader ��ü
    ID3D11VertexShader* mVertexShader = nullptr;
    // Shader Code�� Compile�ؼ� Byte Code�� ���� Buffer.
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
    // �ڽ� Ŭ������ ������ ���ϵ��� final ó��
    virtual void SetShader() final;

public:
    void AddInputLayoutDesc(const char* Semantic,
        unsigned int SemanticIndex, DXGI_FORMAT Format,
        unsigned int InputSlot, unsigned int Size,
        D3D11_INPUT_CLASSIFICATION InputSlotClass,
        unsigned int InstanceDataStepRate);

    // �Է� ���̾ƿ� ����
    bool CreateInputLayout();

    // �Լ��̸�, ���
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

