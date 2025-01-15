#pragma once
#include <Windows.h>
#include <list>
#include <vector>
#include <unordered_map>
#include <string>

#include <d3d11.h>
#include <d3dcompiler.h>

#include <time.h>
#include <math.h>
#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"

#include "Share/SharedPointer.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

/*
	�޸���
	ClearRenderTargetView : 
	DepthBuffer�� 1�� �ʱ�ȭ
	2�� �����ӿ� ����� ���� ���� ����� ��� ������ Ŭ������ �ض�.
		- ������ Ŭ������ SwapChain���� �Ѵ�.
			�ϰ� �Ǹ� Back Buffer�� Primary Buffer�� �ǰ�,
			Primary Buffer�� Back Buffer�� �ȴ� (�� �����ư��鼭 Primary Buffer�� ��)
	
	crtdbg(crt Debug) : �޸� ���� �߻����� �� 
		��� �߻��Ǿ����� ã���ִ� ����� ����

	Vertex(����)	: 3D���� ������ ������
	Polygon		: �ﰢ��
		Ex) ������ü�� ����� ���ؼ� Polygon�� 12���� �ʿ��ϴ�.
			�ﰢ�� 2���� �簢���� ����� ����.
	Mesh : Vertex�� Polygon�� ����ü.
		���� ������ ���� Mesh�� Static Mesh��� �Ѵ�.-
		Skeleton������ ���� Mesh�� Animation Mesh��� �Ѵ�.
		
	Vertex Buffer & Index Buffer
	
	Asset���� ���� ������ �ſ� �߿��ϴ�.
		�׷��� ������ Smart Pointer�� ���� ���� ����.
		Smart Pointer �� shared_ptr�� �ִµ�,
		����� �����Ͽ� ���� ���� �����̴�.

	ID3D11Buffer : Vertext, Index Buffer�� ���� ���� �ִ�.

	D3D11_USAGE : � �޸𸮿� ��������� �����ϴ� ������
		Default : VRAM�� ����
		IMMUTABLE : VRAM�� ���� ������ ���� ����.
		DYNAMIC : VRAM�� ���� �� ���� �Ҵ�
				���纻�� �ý��� �޸𸮿� �Ҵ�.
				�ý��� �޸𸮿� ���� �� VRAM�� �������ش�.
		STAGING : System �޸𸮿� ����.
					������ ���� ���� Buffer.

	D3D_PRIMITIVE_TOPOLOGY : � ������ �׸��� �����ϴ� ������

*/


/*
	WinAPI : ��κ� CPU�� ����ó���� ��
	DirectX : ��κ� GPU�� ����ó���� ��.
*/

#define SAFE_DELETE(p)	if(p)   { delete p; p = nullptr;}
#define SAFE_DELETE_ARRAY(p)	if(p)   { delete[] p; p = nullptr;}
#define	SAFE_RELEASE(p)	if(p)	{ p->Release(); p = nullptr;}

#define DECLARE_SINGLE(Type)	\
private:\
	Type();\
	~Type();\
private:\
	static Type* mInstance;\
public:\
	static Type* GetInstance()\
	{\
		if(!mInstance)\
			mInstance = new Type;\
		return mInstance;\
	}\
	static void DestroyInstance()\
{\
	SAFE_DELETE(mInstance);\
}\

#define DEFINITION_SINGLE(Type) Type* Type::mInstance = nullptr;

struct FRect
{
	float Left = 0.f;
	float Top = 0.f;
	float Right = 0.f;
	float Bottom = 0.f;
};

enum class EBulletOption
{
	Normal,
	Bounce
};

struct FBullet
{
	FVector2D Pos;
	FVector2D Size;
	FVector2D MoveDirect;

	float Distance = 500.f;
	EBulletOption Option = EBulletOption::Normal;
};

struct FResolution
{
	unsigned int Width = 0;
	unsigned int Height = 0;
};

struct FVertexBuffer
{
	ID3D11Buffer* Buffer = nullptr;
	int Size = 0;
	int Count = 0;
	void* Data = nullptr;

	FVertexBuffer() {}
	~FVertexBuffer()
	{
		SAFE_DELETE(Buffer);
		SAFE_DELETE_ARRAY(Data);
	}
};

struct FIndexBuffer
{
	// ������ ����� Buffer
	ID3D11Buffer* Buffer = nullptr;
	// ������ 1���� ũ��
	int Size = 0;
	// ������ ����
	int Count = 0;
	// ������ ����
	DXGI_FORMAT Format = DXGI_FORMAT_UNKNOWN;
	void* Data = nullptr;

	FIndexBuffer() {}
	~FIndexBuffer()
	{
		SAFE_DELETE(Buffer);
		SAFE_DELETE_ARRAY(Data);
	}

};