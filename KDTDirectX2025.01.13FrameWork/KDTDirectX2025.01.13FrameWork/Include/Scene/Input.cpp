#include "Input.h"
#include "../GameManager.h"
#include "../Device.h"

CInput::CInput()
{
}

CInput::~CInput()
{
    auto iter = mKeyStateMap.begin();
    auto iterEnd = mKeyStateMap.end();

    for (; iter != iterEnd; iter++)
    {
        SAFE_DELETE(iter->second);
    }

    auto iter1 = mBindKeyMap.begin();
    auto iter1End = mBindKeyMap.end();

    for (; iter1 != iter1End; iter1++)
    {
        SAFE_DELETE(iter1->second);
    }

	if (mKeyboard)
	{
		mKeyboard->Unacquire();
		SAFE_RELEASE(mKeyboard);
	}

	if (mMouse)
	{
		mMouse->Unacquire();
		SAFE_RELEASE(mMouse);
	}

	SAFE_RELEASE(mInput);
}

bool CInput::InitInput()
{
	// 1번 인자 : 장치에 대한 ID값
	// 2번 인자 : 1번 인자의 데이터값을 2번 인자에 대입해준다.
	// 3번 인자 : 몰?루
	if (FAILED(mInput->CreateDevice(GUID_SysKeyboard, &mKeyboard, nullptr)))
		return false;

	if (FAILED(mKeyboard->SetDataFormat(&c_dfDIKeyboard)))
		return false;

	if (CDevice::GetInstance()->GetWindowMode())
	{
		// DISCL_FOREGROUND		: 활성화 시에만 키를 입력받게 한다.			(창모드 사용불가능.)
		// DISCL_BACKGROUND		: 백그라운드에서도 사용할 수 있게 설정한다.	(창모드 사용가능.)
		// DISCL_EXCLUSIVE		: 입력 Device를 독점모드로 설정한다.		(전체화면에서 자주사용)
		// DISCL_NONEXCLUSIVE	: 입력 Device를 비독점모드로 설정한다.	
		if (FAILED(mKeyboard->SetCooperativeLevel(mHandleWindow, 
			DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
			return false;
	}
	else
	{
		if (FAILED(mKeyboard->SetCooperativeLevel(mHandleWindow,
			DISCL_FOREGROUND | DISCL_EXCLUSIVE)))
			return false;
	}
	// 키보드 장치를 획득한다.
	if (FAILED(mKeyboard->Acquire()))
		return false;

	// 마우스 장치 생성
	if (FAILED(mInput->CreateDevice(GUID_SysMouse, &mMouse, nullptr)))
		return false;

	// 마우스 데이터 형식 설정
	if (FAILED(mMouse->SetDataFormat(&c_dfDIMouse)))
		return false;

	if (CDevice::GetInstance()->GetWindowMode())
	{
		// DISCL_FOREGROUND		: 활성화 시에만 키를 입력받게 한다.			(창모드 사용불가능.)
		// DISCL_BACKGROUND		: 백그라운드에서도 사용할 수 있게 설정한다.	(창모드 사용가능.)
		// DISCL_EXCLUSIVE		: 입력 Device를 독점모드로 설정한다.		(전체화면에서 자주사용)
		// DISCL_NONEXCLUSIVE	: 입력 Device를 비독점모드로 설정한다.	
		if (FAILED(mMouse->SetCooperativeLevel(mHandleWindow,
			DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
			return false;
	}
	else
	{
		if (FAILED(mMouse->SetCooperativeLevel(mHandleWindow,
			DISCL_FOREGROUND | DISCL_EXCLUSIVE)))
			return false;
	}

	// 마우스 장치를 획득한다.
	if (FAILED(mMouse->Acquire()))
		return false;

	return true;
}

bool CInput::UpdateKeyboard()
{
	if (!mKeyboard)
		return false;

	HRESULT result = mKeyboard->GetDeviceState(256, (LPVOID)&mKeyState);
	if (FAILED(result))
	{
		// 키입력을 잃어버리거나 못받아왔을 때 다시 받아오도록 재시도.
		if (result == DIERR_INPUTLOST ||
			result == DIERR_NOTACQUIRED)
			mKeyboard->Acquire();
	}

	return true;
}

bool CInput::UpdateMouse()
{
	if (!mMouse)
		return false;

	// MouseState는 x, y에는 마우스 좌표, z에는 휠값이 들어온다.
	HRESULT result = mMouse->GetDeviceState(sizeof(mMouseState), (LPVOID)&mMouseState);
	
	if (FAILED(result))
	{
		// 키입력을 잃어버리거나 못받아왔을 때 다시 받아오도록 재시도.
		if (result == DIERR_INPUTLOST ||
			result == DIERR_NOTACQUIRED)
			mMouse->Acquire();
	}

	return true;
}

FKeyState* CInput::FindKeyState(unsigned char Key)
{
	auto iter = mKeyStateMap.find(Key);

	if (iter == mKeyStateMap.end())
		return nullptr;

	return iter->second;
}

FBindKey* CInput::FindBindKey(const std::string& Name)
{
	auto iter = mBindKeyMap.find(Name);

	if (iter == mBindKeyMap.end())
		return nullptr;

	return iter->second;
}

void CInput::AddBindKey(const std::string& Name, unsigned char Key)
{
	// 중복된 이름이 있는지 판단한다.
	if (FindBindKey(Name))
		return;

	FBindKey* NewKey = new FBindKey;
	FKeyState* State = FindKeyState(Key);

    // 등록된 키가 없다면 생성 및 등록
    if (!State)
    {
        State = new FKeyState;
        State->Key = ConvertKey(Key);
        mKeyStateMap.insert(std::make_pair(Key, State));
    }

    NewKey->Key = State;
    mBindKeyMap.insert(std::make_pair(Name, NewKey));
}

void CInput::ChangeKeyCtrl(const std::string& Name, bool Ctrl)
{
    FBindKey* Key = FindBindKey(Name);

    if (!Key)
        return;

    Key->Ctrl = Ctrl;
}

void CInput::ChangeKeyAlt(const std::string& Name, bool Alt)
{
    FBindKey* Key = FindBindKey(Name);

    if (!Key)
        return;

    Key->Alt = Alt;
}

void CInput::ChangeKeyShift(const std::string& Name, bool Shift)
{
    FBindKey* Key = FindBindKey(Name);

    if (!Key)
        return;

    Key->Shift = Shift;
}

bool CInput::Init()
{
	mHandleInstance = CGameManager::GetInstance()->GetWindowInstance();
	mHandleWindow = CGameManager::GetInstance()->GetWindowHandle();

	// 입력 디바이스가 지원안된다면 대체수단(윈도우 입력)으로 바뀌도록 처리
	if (FAILED(DirectInput8Create(mHandleInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&mInput, nullptr)))
		mInputType = EInputSystem_Type::Window;

	if (mInputType == EInputSystem_Type::DInput)
	{
		// 입력초기화 실패시 종료
		if (!InitInput())
			return false;
	}

	return true;
}

void CInput::Update(float deltaTime)
{
	if (mInputType == EInputSystem_Type::DInput)
	{
		// 키보드 및 마우스 업데이트
		UpdateKeyboard();
		UpdateMouse();
	}

	//TCHAR MouseInfo[64] = {};
	//wsprintf(MouseInfo, TEXT("x : %d \ty : %d\tz : %d\n"), mMouseState.lX,
	//	mMouseState.lY, mMouseState.lZ);
	//OutputDebugString(MouseInfo);

	// 마우스를 눌렀을 때 실행
	//if (mMouseState.rgbButtons[0] & 0x80)
	//	OutputDebugString(TEXT("Click\n"));

	UpdateInput(deltaTime);

    UpdateBind(deltaTime);
}

void CInput::UpdateInput(float deltaTime)
{
	switch (mInputType)
	{
	case EInputSystem_Type::DInput:
		if (mKeyState[DIK_LCONTROL] & 0x80)
			mCtrl = true;
		else
			mCtrl = false;
		
		if (mKeyState[DIK_LALT] & 0x80)
			mAlt = true;
		else
			mAlt = false;
		
		if (mKeyState[DIK_LSHIFT] & 0x80)
			mShift = true;
		else
			mShift = false;

		for (int i = 0; i < EMouseButtonType::End; i++)
		{
			if (mMouseState.rgbButtons[i] & 0x80)
			{
				// 처음으로 눌렀는가
				if (!mMouseDown[i] && !mMouseHold[i])
				{
					mMouseDown[i] = true;
					mMouseHold[i] = true;
				}
				// 누르고 있었는가
				else
				{
					mMouseDown[i] = false;
				}
			}
			// 누르고 있었다가 뗐는가
			else if (mMouseHold[i])
			{
				mMouseDown[i] = false;
				mMouseHold[i] = false;
				mMouseUp[i] = true;
			}
			else if (mMouseUp[i])
			{
				mMouseUp[i] = false;
			}
		}
		break;
	case EInputSystem_Type::Window:
		break;
	default:
		break;
	}

    auto iter = mKeyStateMap.begin();
    auto iterEnd = mKeyStateMap.end();

    for (; iter != iterEnd; iter++)
    {
        bool KeyPush = false;

        switch(iter->second->Key)
        {
        case DIK_MOUSELBUTTON:
            if (mMouseState.rgbButtons[EMouseButtonType::LButton] & 0x80)
                KeyPush = true;
            break;
        case DIK_MOUSERBUTTON:
            if (mMouseState.rgbButtons[EMouseButtonType::RButton] & 0x80)
                KeyPush = true;
            break;
        case DIK_MOUSEWHEEL:
            if (mMouseState.rgbButtons[EMouseButtonType::WButton] & 0x80)
                KeyPush = true;
            break;
        default:
            if (mKeyState[iter->second->Key] & 0x80)
                KeyPush = true;
            break;
        }

        // 현재 해당 키를 누르고 있을 경우
        if (KeyPush)
        {
            if (!iter->second->Down && !iter->second->Hold)
            {
                iter->second->Down = true;
                iter->second->Hold = true;
            }
            else
            {
                iter->second->Down = false;
            }
        }
        // 현재 해당 키를 안누르고 있을 경우
        // Hold가 true라면 이전 프레임에 이 키를 누르고 있다가
        // 이제 막 키를 해제했다는 것.
        else if (iter->second->Hold)
        {
            iter->second->Down = false;
            iter->second->Hold = false;
            iter->second->Up = true;
        }
        else if (iter->second->Up)
        {
            iter->second->Up = false;
        }
    }
}

void CInput::UpdateBind(float deltaTime)
{
    auto iter = mBindKeyMap.begin();
    auto iterEnd = mBindKeyMap.end();

    for (; iter != iterEnd; iter++)
    {
        // Down이 충족될 경우 등록된 함수를 호출.
        if (iter->second->Key->Down &&
            iter->second->Ctrl == mCtrl &&
            iter->second->Alt == mAlt &&
            iter->second->Shift == mShift)
        {
            size_t Size = iter->second->FunctionList[EInputType::Down].size();

            for (size_t i = 0; i < Size; i++)
            {
                iter->second->FunctionList[EInputType::Down][i].Func(deltaTime);
            }
        }
        
        if (iter->second->Key->Hold &&
            iter->second->Ctrl == mCtrl &&
            iter->second->Alt == mAlt &&
            iter->second->Shift == mShift)
        {
            size_t Size = iter->second->FunctionList[EInputType::Down].size();

            for (size_t i = 0; i < Size; i++)
            {
                iter->second->FunctionList[EInputType::Hold][i].Func(deltaTime);
            }
        }

        if (iter->second->Key->Up &&
            iter->second->Ctrl == mCtrl &&
            iter->second->Alt == mAlt &&
            iter->second->Shift == mShift)
        {
            size_t Size = iter->second->FunctionList[EInputType::Down].size();

            for (size_t i = 0; i < Size; i++)
            {
                iter->second->FunctionList[EInputType::Up][i].Func(deltaTime);
            }
        }
    }
}

unsigned char CInput::ConvertKey(unsigned char Key)
{
    if (mInputType == EInputSystem_Type::DInput)
    {
        switch (Key)
        {
        case VK_LBUTTON:
            return DIK_MOUSELBUTTON;
        case VK_RBUTTON:
            return DIK_MOUSERBUTTON;
        case VK_MBUTTON:
            return DIK_MOUSEWHEEL;
        case VK_BACK:
            return DIK_BACK;
        case VK_TAB:
            return DIK_TAB;
        case VK_RETURN:
            return DIK_RETURN;
        case VK_LCONTROL:
            return DIK_LCONTROL;
        case VK_RCONTROL:
            return DIK_RCONTROL;
        case VK_LMENU:
            return DIK_LALT;
        case VK_RMENU:
            return DIK_RALT;
        case VK_LSHIFT:
            return DIK_LSHIFT;
        case VK_RSHIFT:
            return DIK_RSHIFT;
        case VK_PAUSE:
            return DIK_PAUSE;
        case VK_CAPITAL:
            return DIK_CAPSLOCK;
        case VK_ESCAPE:
            return DIK_ESCAPE;
        case VK_SPACE:
            return DIK_SPACE;
        case VK_NEXT:
            return DIK_PGDN;
        case VK_PRIOR:
            return DIK_PGUP;
        case VK_END:
            return DIK_END;
        case VK_HOME:
            return DIK_HOME;
        case VK_LEFT:
            return DIK_LEFT;
        case VK_UP:
            return DIK_UP;
        case VK_RIGHT:
            return DIK_RIGHT;
        case VK_DOWN:
            return DIK_DOWN;
        case VK_PRINT:
            return DIK_SYSRQ;
        case VK_INSERT:
            return DIK_INSERT;
        case VK_DELETE:
            return DIK_DELETE;
        case VK_HELP:
            return 0;
        case '0':
            return DIK_0;
        case '1':
            return DIK_1;
        case '2':
            return DIK_2;
        case '3':
            return DIK_3;
        case '4':
            return DIK_4;
        case '5':
            return DIK_5;
        case '6':
            return DIK_6;
        case '7':
            return DIK_7;
        case '8':
            return DIK_8;
        case '9':
            return DIK_9;
        case 'A':
            return DIK_A;
        case 'B':
            return DIK_B;
        case 'C':
            return DIK_C;
        case 'D':
            return DIK_D;
        case 'E':
            return DIK_E;
        case 'F':
            return DIK_F;
        case 'G':
            return DIK_G;
        case 'H':
            return DIK_H;
        case 'I':
            return DIK_I;
        case 'J':
            return DIK_J;
        case 'K':
            return DIK_K;
        case 'L':
            return DIK_L;
        case 'M':
            return DIK_M;
        case 'N':
            return DIK_N;
        case 'O':
            return DIK_O;
        case 'P':
            return DIK_P;
        case 'Q':
            return DIK_Q;
        case 'R':
            return DIK_R;
        case 'S':
            return DIK_S;
        case 'T':
            return DIK_T;
        case 'U':
            return DIK_U;
        case 'V':
            return DIK_V;
        case 'W':
            return DIK_W;
        case 'X':
            return DIK_X;
        case 'Y':
            return DIK_Y;
        case 'Z':
            return DIK_Z;
        case VK_OEM_3:
            return DIK_GRAVE;
        case VK_OEM_MINUS:
            return DIK_MINUS;
        case VK_OEM_NEC_EQUAL:
            return DIK_EQUALS;
        case VK_OEM_4:
            return DIK_LBRACKET;
        case VK_OEM_6:
            return DIK_RBRACKET;
        case VK_OEM_5:
            return DIK_BACKSLASH;
        case VK_OEM_1:
            return DIK_SEMICOLON;
        case VK_OEM_7:
            return DIK_APOSTROPHE;
        case VK_OEM_COMMA:
            return DIK_COMMA;
        case VK_OEM_PERIOD:
            return DIK_PERIOD;
        case VK_OEM_2:
            return DIK_SLASH;
        case VK_NUMPAD0:
            return DIK_NUMPAD0;
        case VK_NUMPAD1:
            return DIK_NUMPAD1;
        case VK_NUMPAD2:
            return DIK_NUMPAD2;
        case VK_NUMPAD3:
            return DIK_NUMPAD3;
        case VK_NUMPAD4:
            return DIK_NUMPAD4;
        case VK_NUMPAD5:
            return DIK_NUMPAD5;
        case VK_NUMPAD6:
            return DIK_NUMPAD6;
        case VK_NUMPAD7:
            return DIK_NUMPAD7;
        case VK_NUMPAD8:
            return DIK_NUMPAD8;
        case VK_NUMPAD9:
            return DIK_NUMPAD9;
        case VK_MULTIPLY:
            return DIK_MULTIPLY;
        case VK_ADD:
            return DIK_ADD;
        case VK_SEPARATOR:
            return DIK_NUMPADCOMMA;
        case VK_SUBTRACT:
            return DIK_SUBTRACT;
        case VK_DECIMAL:
            return DIK_DECIMAL;
        case VK_DIVIDE:
            return DIK_DIVIDE;
            //case VK_RETURN:      
            //return DIK_NUMPADENTER;
        case VK_F1:
            return DIK_F1;
        case VK_F2:
            return DIK_F2;
        case VK_F3:
            return DIK_F3;
        case VK_F4:
            return DIK_F4;
        case VK_F5:
            return DIK_F5;
        case VK_F6:
            return DIK_F6;
        case VK_F7:
            return DIK_F7;
        case VK_F8:
            return DIK_F8;
        case VK_F9:
            return DIK_F9;
        case VK_F10:
            return DIK_F10;
        case VK_F11:
            return DIK_F11;
        case VK_F12:
            return DIK_F12;
        case VK_F13:
            return DIK_F13;
        case VK_F14:
            return DIK_F14;
        case VK_F15:
            return DIK_F15;
        case VK_F16:
        case VK_F17:
        case VK_F18:
        case VK_F19:
        case VK_F20:
        case VK_F21:
        case VK_F22:
        case VK_F23:
        case VK_F24:
            return 0;
        case VK_NUMLOCK:
            return DIK_NUMLOCK;
        case VK_SCROLL:
            return DIK_SCROLL;
        case VK_LWIN:
            return DIK_LWIN;
        case VK_RWIN:
            return DIK_RWIN;
        case VK_APPS:
            return DIK_APPS;
        case VK_OEM_102:
            return DIK_OEM_102;
        }

        return 0xff;
    }

    return Key;
}
