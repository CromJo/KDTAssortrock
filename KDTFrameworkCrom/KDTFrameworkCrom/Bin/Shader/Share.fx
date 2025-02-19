/*
    Shader 
        - HLSL 언어 기반이다.
            Class가 없는 C++과 문법이 유사하다.
        - 코드 작성 시 Compile한다고 실행 File에 포함되지 않는다.
            Shader Code를 Compile하는 함수가 존재함.
            함수를 이용해 Rendering Pipeline에 Shader를 지정한다.
        - 반드시 File처럼 별도로 실행파일이 있는곳에 Shader파일이 필요.
        - 일반 txt 파일처럼 사용해도 된다. 
            굳이 visual studio로 코드 작성을 안해도 된다.

    Register
        - 모든 Shader는 
            Input Register (입력 레지스터) 
            Output Register (출력 레지스터)
            Const Register (상수 레지스터)가 있다.
        - Input Register
            - Vertex 정보는 Buffer가 가지고 있다.
            - 하나씩 끊어서 출력하려는 Vertex Buffer와,
                입력 조립기가 렌더링 파이프라인과 버텍스 버퍼간의 Stream을 만들고,
                Buffer안에 들어가있는 Vertex (12byte)를 Color (16byte)가 들어가있는데,
                앞쪽 위치(12byte) 뒤쪽 (16byte)은 색상으로 쓰겠다는 정의
        - Position Register
            - 0 ~ 15번까지 존재 (더 늘릴 수 있다)
        - Color Register
        - Custom Register


*/

// 픽셀 쉐이더 용 출력용 구조체
struct PixelShader_Output_Single
{
    // float 4개짜리 Vector 생성
    // 변수명에 "SV"가 붙어있으면 System Value를 의미하고,
    //   저장하는 용도로 쓰인다. 
    //   대입만 되고, 연산하려고 할 시 크래쉬가 난다.
    // SV_TARGET을 하면 뒤에 0이 생략.
    float4 Color : SV_TARGET;
    
};