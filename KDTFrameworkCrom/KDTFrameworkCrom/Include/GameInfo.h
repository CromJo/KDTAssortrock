#pragma once

#include <Windows.h>
#include <list>
#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"

#include <unordered_map>
#include <vector>
// �޸𸮸��� �߻� �Ǿ��� ��, ��� �߻��Ǿ�����
// ã���ִ� ����� ����
#include <crtdbg.h>

// ���̷�Ʈ11 ��� �ҷ�����
#include <d3d11.h>
// ���̷�Ʈ �����Ϸ� �ҷ�����
#include <d3dcompiler.h>

// .lib�� ��ũ �ɾ��ִ� ���
#pragma comment(lib, "d3d11.lib")
// ���̷�Ʈ�� �̿��� �� C++�� �̿��ؼ� �ڵ��� �ϳ�,
// Direct11���ʹ� Shader�� �̿��ؼ� �ڵ带 ¥�� ����ϰԲ� �Ǿ��ִ�.
// ����� �ϱ����� HLSL�̶�� �� ����Ѵ�.
// �߰����� ���
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")



#define SAFE_DELETE(p) if(p) { delete p; p = nullptr; }
#define SAFE_RELEASE(p) if(p) { p->Release(); p = nullptr; }


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
	}

#define DEFINITION_SINGLE(Type) Type* Type::mInstance = nullptr;



struct FRect
{
	float Left	 = 0.f;
	float Top	 = 0.f;
	float Right	 = 0.f;
	float Bottom = 0.f;
};

enum class EBulletOption
{
	Normal,			// �Ϲ� Ư��
	Bounce			// ƨ��� Ư��
};

struct FBullet
{
	FVector2D Pos;			// ��ġ
	FVector2D Size;			// ũ��
	FVector2D MoveDirect;	// ����
	float Distance = 800.f;	// �Ÿ�
	EBulletOption Option = EBulletOption::Normal;
};

struct FResolution
{
	unsigned int Width = 0;
	unsigned int Height = 0;
};