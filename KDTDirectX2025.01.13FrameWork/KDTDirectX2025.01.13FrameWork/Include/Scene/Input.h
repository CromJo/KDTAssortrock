#pragma once
#define DIRECTINPUT_VERSION 0x0800
#define DIK_MOUSELBUTTON 0xfc
#define DIK_MOUSERBUTTON 0xfd
#define DIK_MOUSEWHEEL 0xfe
#include "../GameInfo.h"
#include <dinput.h>

#pragma comment(lib, "dinput8.lib")

enum class EInputSystem_Type
{
	DInput,
	Window
};

namespace EMouseButtonType
{
	enum Type
	{
		LButton,
		RButton,
		WButton,
		End
	};
}

namespace EInputType
{
	enum Type
	{
		Down,
		Hold,
		Up,
		End
	};
}

struct FKeyState
{
	unsigned char Key = 0;
	bool Down = false;
	bool Hold = false;
	bool Up = false;
};

struct FBindFunction
{
	void* Obj = nullptr;
	std::function<void(float)> Func;
};

struct FBindKey
{
	FKeyState* Key = nullptr;
	// Ư��Ű�� ������ Ű�� �������� üũ�ϱ� ����.
	bool Ctrl = false;
	bool Alt = false;
	bool Shift = false;
	std::vector<FBindFunction> FunctionList[EInputType::End];
};

class CInput
{
	friend class CScene;

private:
	CInput();
	~CInput();

private:
	HINSTANCE mHandleInstance;
	HWND mHandleWindow;
	// �Է¹ް��� �ϴ� Device�� dInput���� ���� �� �ְ� �ȴ�.
	IDirectInput8* mInput = nullptr;
	IDirectInputDevice8* mKeyboard = nullptr;
	IDirectInputDevice8* mMouse = nullptr;
	EInputSystem_Type mInputType = EInputSystem_Type::DInput;
	
	std::unordered_map<unsigned char, FKeyState*> mKeyStateMap;
	std::unordered_map<std::string, FBindKey*> mBindKeyMap;

	unsigned char mKeyState[256] = {};
	DIMOUSESTATE mMouseState = {};

	bool mCtrl = false;
	bool mAlt = false;
	bool mShift = false;

	// ���콺 ��ư �̺�Ʈ
	bool mMouseDown[EMouseButtonType::End] = {};
	bool mMouseHold[EMouseButtonType::End] = {};
	bool mMouseUp[EMouseButtonType::End] =  {};
	
public:
	bool GetMouseDown(EMouseButtonType::Type Type)
	{
		return mMouseDown[Type];
	}

	bool GetMouseHold(EMouseButtonType::Type Type)
	{
		return mMouseHold[Type];
	}

	bool GetMouseUp(EMouseButtonType::Type Type)
	{
		return mMouseUp[Type];
	}

private:
	bool InitInput();
	bool UpdateKeyboard();
	bool UpdateMouse();

	FKeyState* FindKeyState(unsigned char Key);
	FBindKey* FindBindKey(const std::string& Name);

public:
	void AddBindKey(const std::string& Name, unsigned char Key);
	void ChangeKeyCtrl(const std::string& Name, bool Ctrl);
	void ChangeKeyAlt(const std::string& Name, bool Alt);
	void ChangeKeyShift(const std::string& Name, bool Shift);

public:
	// ���̷�ƮX�� �ʱ�ȭ�ϱ� ���ؼ� HInstance�� �� �ʿ���.
	bool Init();
	//bool Init(HINSTANCE hInstance);
	void Update(float deltaTime);

private:
	void UpdateInput(float deltaTime);
	void UpdateBind(float deltaTime);

public:
	template <typename T>
	void AddBindFunction(const std::string& KeyName, 
		EInputType::Type Type,
		T* Object, void (T::* Func)(float))
	{
		FBindKey* BindKey = FindBindKey(KeyName);

		if (!BindKey)
			return;

		FBindFunction BindFunc;
		BindFunc.Obj = Object;
		// std::bind�� �̿��Ͽ� �Լ��ּҿ� ��ü�� �̿��� 
		// function ��ü�� ������ش�.
		BindFunc.Func = std::bind(Func, Object, std::placeholders::_1);
		BindKey->FunctionList[Type].emplace_back(BindFunc);
	}

private:
	unsigned char ConvertKey(unsigned char Key);
};

