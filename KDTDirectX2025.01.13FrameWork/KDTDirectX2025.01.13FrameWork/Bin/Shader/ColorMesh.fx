#include "Share.fx"

// Vertex Shader
struct VertexShader_Input_Color
{
    // SV가 안붙으면 값을 사용할 수 있다는 의미.
    float3 Pos : POSITION;
    float4 Color : COLOR;
};

struct VertexShader_Output_Color
{
    // SV가 붙으면 저장만 해야한다. (Set 느낌)
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
};

VertexShader_Output_Color ColorMeshVertexShader(VertexShader_Input_Color Input)
{
    // 0을 struct 타입으로 형변환 하여 대입해주면 
    // 구조체의 모든 멤버가 0으로 초기화된다.
    VertexShader_Output_Color Output = (VertexShader_Output_Color) 0;
    
    // Output.Pos의 x,y,z에는 Input.Pos의 x,y,z가 대입되고,
    // w에는 1이 대입된다.
    Output.Pos = mul(float4(Input.Pos, 1.f), gmatWVP);
    Output.Color = Input.Color;
    
    return Output;
}

// 매개변수1에서 사용된 것처럼 사용시 COLOR 0번 레지스터에 있는 값을 꺼내오겠다는 의미이다.
PixelShader_Output_Single ColorMeshPixelShader(float4 Color : COLOR)
{
    PixelShader_Output_Single Output = (PixelShader_Output_Single) 0;
    
    Output.Color = Color;
    
    return Output;
}
