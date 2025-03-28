
#include "Share.fx"

struct VS_Input_Color
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
};

struct VS_Output_Color
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
};

VS_Output_Color ColorMeshVS(VS_Input_Color input)
{
    // 0을 구조체 타입으로 형변환 하여 대입해주면 구조체의 모든 멤버가 0으로
    // 초기화된다.
    VS_Output_Color output = (VS_Output_Color)0;

    // output.Pos의 x, y, z 에는 input.Pos의 x, y, z 가 대입되고 w에는 1이 대입된다.
    output.Pos = mul(float4(input.Pos, 1.f), gmatWVP);
    output.Color = input.Color;
    
    return output;
}

// 인자에 이렇게 사용하면 COLOR0번 레지스터에 있는 값을 꺼내오겠다는 의미이다.
PS_Output_Single ColorMeshPS(VS_Output_Color input)
{
    PS_Output_Single output = (PS_Output_Single) 0;
    
    output.Color = input.Color;
    
    return output;
}