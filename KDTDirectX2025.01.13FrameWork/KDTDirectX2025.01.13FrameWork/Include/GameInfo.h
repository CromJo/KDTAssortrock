#pragma once
#include <Windows.h>
#include <list>
#include <vector>
#include <unordered_map>
#include <crtdbg.h>
#include <string>

#include <d3d11.h>
#include <d3dcompiler.h>

#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"

#include "Share/SharedPointer.h"
#include "Matrix.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

/*
	메모장
	ClearRenderTargetView : 
	DepthBuffer를 1로 초기화
	2번 프레임에 출력할 것을 전부 출력할 경우 페이지 클리핑을 해라.
		- 페이지 클리핑은 SwapChain으로 한다.
			하게 되면 Back Buffer가 Primary Buffer로 되고,
			Primary Buffer가 Back Buffer가 된다 (즉 번갈아가면서 Primary Buffer가 됨)
	
	crtdbg(crt Debug) : 메모리 릭이 발생헀을 시 
		어디서 발생되었는지 찾아주는 기능을 제공

	Vertex(정점)	: 3D에서 도형의 꼭지점
	Polygon		: 삼각형
		Ex) 정육면체를 만들기 위해선 Polygon이 12개가 필요하다.
			삼각형 2개로 사각형을 만들기 때문.
	Mesh : Vertex와 Polygon의 집합체.
		기하 정보를 가진 Mesh를 Static Mesh라고 한다.-
		Skeleton정보를 가진 Mesh를 Animation Mesh라고 한다.
		
	Vertex Buffer & Index Buffer
	
	Asset류는 공유 구조가 매우 중요하다.
		그렇기 떄문에 Smart Pointer가 자주 쓰일 예정.
		Smart Pointer 중 shared_ptr가 있는데,
		사용이 불편하여 쓰진 않을 예정이다.

	ID3D11Buffer : Vertext, Index Buffer를 만들 수가 있다.

	D3D11_USAGE : 어떤 메모리에 만들어줄지 결정하는 열거형
		Default : VRAM에 저장
		IMMUTABLE : VRAM에 저장 변경할 수는 없음.
		DYNAMIC : VRAM에 공간 및 저장 할당
				복사본을 시스템 메모리에 할당.
				시스템 메모리에 갱신 및 VRAM에 복사해준다.
		STAGING : System 메모리에 저장.
					데이터 갱신 전용 Buffer.

	D3D_PRIMITIVE_TOPOLOGY : 어떤 도형을 그릴지 지정하는 열거형

*/


/*
	WinAPI : 대부분 CPU로 연산처리를 함
	DirectX : 대부분 GPU로 연산처리를 함.
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

namespace EShaderBufferType
{
	enum Type
	{
		Vertex = 0x1,
		Pixel = 0x2,
		Hull = 0x4,
		Domain = 0x8,
		Geometry = 0x10,
		Compute = 0x20,
		Graphic = Vertex | Pixel | Hull | Domain | Geometry,
		All = Graphic | Compute
	};
}

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
	// 데이터 저장용 Buffer
	ID3D11Buffer* Buffer = nullptr;
	// 데이터 1개의 크기
	int Size = 0;
	// 데이터 갯수
	int Count = 0;
	// 데이터 포맷
	DXGI_FORMAT Format = DXGI_FORMAT_UNKNOWN;
	void* Data = nullptr;

	FIndexBuffer() {}
	~FIndexBuffer()
	{
		SAFE_DELETE(Buffer);
		SAFE_DELETE_ARRAY(Data);
	}

};

// 정점 정보 (색상 정보)
struct FVertexColor
{
	FVector3D Pos;
	// 색상은 RGB 정보를 가지고 있음
	// 0 ~ 1 Float타입을 할지
	// 0 ~ 255 Int타입을 할지 택1
	// 4DVector로 한 이유는 RGB 및 A(알파)값을 가지기 위함.
	FVector4D Color;

	FVertexColor() {}
	FVertexColor(const FVector3D& _Pos, const FVector4D& _Color) :
		Pos(_Pos),
		Color(_Color)
	{ 
	}

	FVertexColor(float x, float y, float z, float r, float g, float b, float a) :
		Pos(x, y, z),
		Color(r, g, b, a)
	{
	}
};