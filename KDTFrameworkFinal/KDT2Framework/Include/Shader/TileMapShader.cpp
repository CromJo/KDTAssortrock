#include "TileMapShader.h"

CTileMapShader::CTileMapShader()
{
}

CTileMapShader::~CTileMapShader()
{
}

bool CTileMapShader::Init()
{
    // 버텍스 쉐이더 불러오기
    if (!LoadVertexShader("TileMapVS", TEXT("TileMap.fx")))
        return false;
    // 픽셀 쉐이더 불러오기
    if (!LoadPixelShader("TileMapPS", TEXT("TileMap.fx")))
        return false;

    AddInputLayoutDesc("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,
        0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0);
    AddInputLayoutDesc("TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,
        0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0);

    if (!CreateInputLayout())
        return false;

    return true;
}
