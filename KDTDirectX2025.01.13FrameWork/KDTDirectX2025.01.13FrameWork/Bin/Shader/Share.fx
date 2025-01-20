
/*
    Vertex의 정보는 Vertex Buffer가 보유중    
    입력 조립기가 렌더링 파이프라인과     

    위치 레지스터 : 
    색상 레지스터 : 
    입력 레지스터 : 
    출력 레지스터 :
    상수 레지스터 :

*/

struct PixelShader_Output_Single
{
    // 4개짜리 float을 생성합니다.
    // SV_TARGET을 하면 뒤에 0이 생략된다.
    // SV : System Value를 의미한다.
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
    