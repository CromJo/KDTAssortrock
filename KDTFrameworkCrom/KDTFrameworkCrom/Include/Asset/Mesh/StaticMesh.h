#pragma once

#include "Mesh.h"

/*
    Vertex Buffer : ���� ���� ���� ���
    Index Buffer : ���� ���ۿ� ���ִ� ���� �迭��
        � ������ �����Ͽ� �ﰢ���� ������ �����ϴ� ���

    �ΰ��� Buffer ��� DirectX���� ����
    
    ȭ�� Rendering : GPU ���
    ���� ó���� ���� �����Ͱ� Video Memory�� �����ϸ�
     ��������.
    �׷��� System Memory�� �ִ°��� ����� ���� �ӵ��� ������.
    
*/

class CStaticMesh :
    public CMesh
{
public:
    CStaticMesh();
    virtual ~CStaticMesh();
};

