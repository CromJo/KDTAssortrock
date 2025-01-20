
/*
    Vertex�� ������ Vertex Buffer�� ������    
    �Է� �����Ⱑ ������ ���������ΰ�     

    ��ġ �������� : 
    ���� �������� : 
    �Է� �������� : 
    ��� �������� :
    ��� �������� :

*/

struct PixelShader_Output_Single
{
    // 4��¥�� float�� �����մϴ�.
    // SV_TARGET�� �ϸ� �ڿ� 0�� �����ȴ�.
    // SV : System Value�� �ǹ��Ѵ�.
    float4 Color : SV_TARGET;
};

cbuffer Transform : register(b0)
{
    matrix gmatWorld;
    matrix gmatView;
    matrix gmatProj;
    matrix gmatWV;
    matrix gmatWVP;
}
    