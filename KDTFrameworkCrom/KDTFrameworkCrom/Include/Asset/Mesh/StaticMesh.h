#pragma once

#include "Mesh.h"

/*
    Vertex Buffer : 정점 정보 저장 기능
    Index Buffer : 정점 버퍼에 들어가있는 정점 배열을
        어떤 순서로 연결하여 삼각형을 만들지 결정하는 기능

    두개의 Buffer 모두 DirectX에서 지원
    
    화면 Rendering : GPU 담당
    연산 처리를 위한 데이터가 Video Memory에 존재하면
     빨라진다.
    그러나 System Memory에 있는것을 끌어다 쓸땐 속도가 느리다.
    
*/

class CStaticMesh :
    public CMesh
{
public:
    CStaticMesh();
    virtual ~CStaticMesh();
};

