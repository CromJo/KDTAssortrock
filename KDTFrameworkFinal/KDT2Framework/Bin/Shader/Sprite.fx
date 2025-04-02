
#include "Share.fx"

struct VS_Input_Tex
{
    float3 Pos : POSITION;
    float2 UV : TEXCOORD;
};

struct VS_Output_Tex
{
    float4 Pos : SV_POSITION;
    float2 UV : TEXCOORD;
};

cbuffer Sprite : register(b3)
{
    float4 gSpriteTint;
    float4 gSpriteIgnoreColor;
}

VS_Output_Tex SpriteVS(VS_Input_Tex input)
{
    VS_Output_Tex output = (VS_Output_Tex) 0;
    
    // Old
    float3 Pos = input.Pos - gPivot;
    
    // 가상 Z 스케일 계산 (Y값에 비례)
    //float yScale = 1.0f - (abs(input.Pos.y) / 720.f * 0.5f); // 720은 화면 높이
    //float3 scaledPos = input.Pos * float3(yScale, yScale, 1.f);
    //
    //float3 Pos = scaledPos - gPivot; // 피벗 보정
    
    // output.Pos의 x, y, z 에는 input.Pos의 x, y, z 가 대입되고 w에는 1이 대입된다.
    output.Pos = mul(float4(Pos, 1.f), gmatWVP);
    output.UV = UpdateAnimation2D(input.UV);
    
    return output;
}

PS_Output_Single SpritePS(VS_Output_Tex input)
{
    PS_Output_Single output = (PS_Output_Single) 0;
    
    float4 Color = gBaseTexture.Sample(gBaseSampler, input.UV);
   
    if ((gSpriteIgnoreColor.x - Color).x == 0.f &&
        (gSpriteIgnoreColor.y - Color).y == 0.f &&
        (gSpriteIgnoreColor.z - Color).z == 0.f)
    {        
        discard;    
    }
    
    output.Color = Color * gSpriteTint;
    
    return output;
}
