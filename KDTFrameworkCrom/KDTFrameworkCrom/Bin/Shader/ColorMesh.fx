#include "Share.fx"

/*

*/

struct VertexShader_Input_Color
{
    // SV 키워드가 안붙기 때문에,
    //  값을 변경할 수 있다.
    float3 Position : POSITION;
    float4 Color : COLOR;
};

struct VertexShader_Output_Color
{
    // SV가 붙기 때문에 값 저장만 해야한다.
    float4 Position : SV_POSITION;
    float4 Color : COLOR;
};

VertexShader_Output_Color ColorMeshVertexShader(VertexShader_Input_Color input)
{
    // 0을 구조체 타입으로 형변환 후 대입해주면,
    // 구조체
    VertexShader_Output_Color output = (VertexShader_Output_Color) 0;

        
    output.Position = float4(input.Position, 1.f);
    output.Color = input.Color;
    
    return output;
}

// 인자에 이렇게 사용하면 COLOR 0번 Register에 있는 값을 꺼내오겠단 얘기이다.
PixelShader_Output_Single ColorMeshPixelShader(VertexShader_Output_Color input)
{
    PixelShader_Output_Single output = (PixelShader_Output_Single) 0;
    
    output.Color = input.Color;
    
    return output;

}
