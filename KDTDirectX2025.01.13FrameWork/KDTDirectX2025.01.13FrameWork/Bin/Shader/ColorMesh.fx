#include "Share.fx"

// Vertex Shader
struct VertexShader_Input_Color
{
    // SV�� �Ⱥ����� ���� ����� �� �ִٴ� �ǹ�.
    float3 Pos : POSITION;
    float4 Color : COLOR;
};

struct VertexShader_Output_Color
{
    // SV�� ������ ���常 �ؾ��Ѵ�. (Set ����)
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
};

VertexShader_Output_Color ColorMeshVertexShader(VertexShader_Input_Color Input)
{
    // 0�� struct Ÿ������ ����ȯ �Ͽ� �������ָ� 
    // ����ü�� ��� ����� 0���� �ʱ�ȭ�ȴ�.
    VertexShader_Output_Color Output = (VertexShader_Output_Color) 0;
    
    // Output.Pos�� x,y,z���� Input.Pos�� x,y,z�� ���Եǰ�,
    // w���� 1�� ���Եȴ�.
    Output.Pos = mul(float4(Input.Pos, 1.f), gmatWVP);
    Output.Color = Input.Color;
    
    return Output;
}

// �Ű�����1���� ���� ��ó�� ���� COLOR 0�� �������Ϳ� �ִ� ���� �������ڴٴ� �ǹ��̴�.
PixelShader_Output_Single ColorMeshPixelShader(float4 Color : COLOR)
{
    PixelShader_Output_Single Output = (PixelShader_Output_Single) 0;
    
    Output.Color = Color;
    
    return Output;
}
