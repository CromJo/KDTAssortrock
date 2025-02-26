#include "Share.fx"

struct VertexShader_Input_Color
{
    // SV Ű���尡 �Ⱥٱ� ������,
    //  ���� ������ �� �ִ�.
    float3 Position : POSITION;
    float4 Color : COLOR;
};

struct VertexShader_Output_Color
{
    // SV�� �ٱ� ������ �� ���常 �ؾ��Ѵ�.
    float4 Position : SV_POSITION;
    float4 Color : COLOR;
};

VertexShader_Output_Color ColorMeshVertexShader(VertexShader_Input_Color input)
{
    // 0�� ����ü Ÿ������ ����ȯ �� �������ָ�,
    // ����ü
    VertexShader_Output_Color output = (VertexShader_Output_Color) 0;

    // x,y,z�� �� = (input.Position)
    // w�� �� = ��� ������ �ִ� ��
    // w�� ���� 0�� �����Ҽ��� ������Ʈ(output)�� 
    //  �Ÿ��� ī�޶�� ���������.
    output.Position = mul(float4(input.Position, 1.f), gMatrixWVP);
    output.Color = input.Color;
   
    return output;
}

// ���ڿ� �̷��� ����ϸ� COLOR 0�� Register�� �ִ� ���� �������ڴ� ����̴�.
PixelShader_Output_Single ColorMeshPixelShader(VertexShader_Output_Color input)
{
    PixelShader_Output_Single output = (PixelShader_Output_Single) 0;
    
    output.Color = input.Color;
    
    return output;

}
