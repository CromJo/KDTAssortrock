/*
    Shader 
        - HLSL ��� ����̴�.
            Class�� ���� C++�� ������ �����ϴ�.
        - �ڵ� �ۼ� �� Compile�Ѵٰ� ���� File�� ���Ե��� �ʴ´�.
            Shader Code�� Compile�ϴ� �Լ��� ������.
            �Լ��� �̿��� Rendering Pipeline�� Shader�� �����Ѵ�.
        - �ݵ�� Fileó�� ������ ���������� �ִ°��� Shader������ �ʿ�.
        - �Ϲ� txt ����ó�� ����ص� �ȴ�. 
            ���� visual studio�� �ڵ� �ۼ��� ���ص� �ȴ�.

    Register
        - ��� Shader�� 
            Input Register (�Է� ��������) 
            Output Register (��� ��������)
            Const Register (��� ��������)�� �ִ�.
        - Input Register
            - Vertex ������ Buffer�� ������ �ִ�.
            - �ϳ��� ��� ����Ϸ��� Vertex Buffer��,
                �Է� �����Ⱑ ������ ���������ΰ� ���ؽ� ���۰��� Stream�� �����,
                Buffer�ȿ� ���ִ� Vertex (12byte)�� Color (16byte)�� ���ִµ�,
                ���� ��ġ(12byte) ���� (16byte)�� �������� ���ڴٴ� ����
        - Position Register
            - 0 ~ 15������ ���� (�� �ø� �� �ִ�)
        - Color Register
        - Custom Register


*/

// �ȼ� ���̴� �� ��¿� ����ü
struct PixelShader_Output_Single
{
    // float 4��¥�� Vector ����
    // ������ "SV"�� �پ������� System Value�� �ǹ��ϰ�,
    //   �����ϴ� �뵵�� ���δ�. 
    //   ���Ը� �ǰ�, �����Ϸ��� �� �� ũ������ ����.
    // SV_TARGET�� �ϸ� �ڿ� 0�� ����.
    float4 Color : SV_TARGET;
    
};