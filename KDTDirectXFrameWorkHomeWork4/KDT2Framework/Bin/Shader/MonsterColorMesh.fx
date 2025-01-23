#include "Share.fx"

struct VS_Input_Color2
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
};

struct VS_Output_Color2
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
};

VS_Output_Color2 MonsterColorMeshVS(VS_Input_Color2 input)
{
    // 0�� ����ü Ÿ������ ����ȯ �Ͽ� �������ָ� ����ü�� ��� ����� 0����
    // �ʱ�ȭ�ȴ�.
    VS_Output_Color2 output = (VS_Output_Color2) 1;

    // output.Pos�� x, y, z ���� input.Pos�� x, y, z �� ���Եǰ� w���� 1�� ���Եȴ�.
    output.Pos = mul(float4(input.Pos, 1.f), gmatWVP);
    output.Color = input.Color;
    
    return output;
}

// ���ڿ� �̷��� ����ϸ� COLOR0�� �������Ϳ� �ִ� ���� �������ڴٴ� �ǹ��̴�.
PS_Output_Single MonsterColorMeshPS(VS_Output_Color2 input)
{
    PS_Output_Single output = (PS_Output_Single) 0;
    
    output.Color = input.Color;
    
    return output;
}