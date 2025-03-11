#pragma once

#define	DIRECTINPUT_VERSION	0x0800

#define	DIK_MOUSELBUTTON	0xfc
#define	DIK_MOUSERBUTTON	0xfd
#define	DIK_MOUSEWHEEL		0xfe

#include "../GameInfo.h"
#include <dinput.h>

#pragma comment(lib, "dinput8.lib")

enum class EInputSystem_Type	// 입력 시스템 타입
{
	DInput,						// ??
	Window						// Window 모드?
};

namespace EMouseButtonType		// 마우스가 버튼눌렀을때 타입
{
	enum Type
	{
		LButton,				// 왼쪽 마우스 버튼을 눌렀을 때
		RButton,				// 오른쪽 마우스 버튼을 눌렀을 때
		MButton,				// 중앙(휠) 마우스 버튼을 눌렀을 때
		End						// 그냥 끝내
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
	unsigned char	Key = 0;
	bool			Down = false;
	bool			Hold = false;
	bool			Up = false;
};

struct FBindFunction
{
	void* Obj = nullptr;
	std::function<void(float)>	Func;
};

struct FBindKey
{
	FKeyState* Key = nullptr;
	// 컨트롤 키를 누르고 키를 눌러야 하는지 조합키 사용 여부를 저장.
	bool	Ctrl = false;
	bool	Alt = false;
	bool	Shift = false;
	bool	KeyHold = false;
	std::vector<FBindFunction>	FunctionList[EInputType::End];
};

class CInput
{
	friend class CScene;

private:
	CInput();
	~CInput();

private:
	class CScene* mScene = nullptr;
	HINSTANCE	mhInst;
	HWND		mhWnd;
	IDirectInput8* mInput = nullptr;
	IDirectInputDevice8* mkeyboard = nullptr;
	IDirectInputDevice8* mMouse = nullptr;
	EInputSystem_Type	mInputType = EInputSystem_Type::DInput;

	std::unordered_map<unsigned char, FKeyState*>	mKeyStateMap;
	std::unordered_map<std::string, FBindKey*>		mBindKeyMap;

	unsigned char		mKeyState[256] = {};
	DIMOUSESTATE		mMouseState = {};

	bool				mCtrl[EInputType::End] = {};
	bool				mAlt[EInputType::End] = {};
	bool				mShift[EInputType::End] = {};

	bool				mMouseDown[EMouseButtonType::End] = {};
	bool				mMouseHold[EMouseButtonType::End] = {};
	bool				mMouseUp[EMouseButtonType::End] = {};

	FVector2D	mMousePos;
	FVector2D	mMouseWorldPos2D;
	FVector2D	mMouseMove;
	// 첫번째 프레임은 이전 마우스 위치가 의미가 없으므로
	// 2번째 프레임부터 마우스 이동을 계산한다.
	bool		mMouseCompute = false;

public:
	/// <summary>
	/// 마우스 다운했을때
	/// </summary>
	/// <param name="Type"></param>
	/// <returns></returns>
	bool GetMouseDown(EMouseButtonType::Type Type)
	{
		return mMouseDown[Type];
	}

	/// <summary>
	/// 마우스 홀드 헀을 때
	/// </summary>
	/// <param name="Type"></param>
	/// <returns></returns>
	bool GetMouseHold(EMouseButtonType::Type Type)
	{
		return mMouseHold[Type];
	}

	/// <summary>
	/// 마우스 업 했을 때
	/// </summary>
	/// <param name="Type"></param>
	/// <returns></returns>
	bool GetMouseUp(EMouseButtonType::Type Type)
	{
		return mMouseUp[Type];
	}

	const FVector2D& GetMousePos()	const
	{
		return mMousePos;
	}

	const FVector2D& GetMouseWorldPos2D()	const
	{
		return mMouseWorldPos2D;
	}

	const FVector2D& GetMouseMove()	const
	{
		return mMouseMove;
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
	bool Init();
	void Update(float DeltaTime);

private:
	void UpdateMousePos(float DeltaTime);
	void UpdateInput(float DeltaTime);
	void UpdateBind(float DeltaTime);



public:
	template <typename T>
	void AddBindFunction(const std::string& KeyName, EInputType::Type Type,
		T* Object, void (T::* Func)(float))
	{
		FBindKey* BindKey = FindBindKey(KeyName);

		if (!BindKey)
			return;

		FBindFunction	BindFunc;

		BindFunc.Obj = Object;
		// std::bind를 이용해서 함수주소와 객체를 이용하여 function 객체를
		// 만들어준다.
		BindFunc.Func = std::bind(Func, Object, std::placeholders::_1);

		BindKey->FunctionList[Type].emplace_back(BindFunc);
	}

private:
	unsigned char ConvertKey(unsigned char Key);
};

