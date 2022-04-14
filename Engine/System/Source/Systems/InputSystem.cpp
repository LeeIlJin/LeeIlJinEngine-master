#include "MySystem.h"

#include "InputSystem.h"
//

InputSystem::InputSystem()
	:currentMousePosScreen(0, 0), oldMousePosScreen(0, 0), mouseVelocityScreen(0, 0)
	, currentMousePosDevice(0, 0), oldMousePosDevcie(0, 0), mouseVelocityDevice(0, 0)
	, currentWheel(0), oldWheel(0), wheelVal(0), keyDownCount(0), procIndex(-1), mouseInMainWindow(false)
{ }

//	* Input System Initialize
void InputSystem::Initialize(const MainWindowDescription& main_window_description)
{
	//	+ Set Main Window Size
	memcpy(&windowSize, &main_window_description.Size, sizeof(main_window_description.Size));

	//	+ Add Process Function To Main Window Process List
	procIndex = MainWindow::AddProc(BIND_FUNCTION_4(InputSystem, InputProc, this));

	ZeroMemory(keyState, sizeof(keyState));
	ZeroMemory(keyOldState, sizeof(keyOldState));
	ZeroMemory(keyMap, sizeof(keyMap));
	ZeroMemory(keyDoubleInfo, sizeof(keyDoubleInfo));

	timeDblClick = GetDoubleClickTime();

	DWORD tLine = 0;
	SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, &tLine, 0);
}

//	* Input System Release
void InputSystem::Release()
{
	//	- Erase Process Function From Main Window Process List
	if (procIndex >= 0)
		MainWindow::EraseProc(procIndex);
}

void InputSystem::Update()
{
	///////////////////////////////////////////////////////////////////////////
	//		Init

	memcpy(keyOldState, keyState, sizeof(keyOldState));

	ZeroMemory(keyState, sizeof(keyState));
	ZeroMemory(keyMap, sizeof(keyMap));

	keyDownCount = 0;

	///////////////////////////////////////////////////////////////////////////
	//		Mouse Pos , Wheel

	wheelVal = currentWheel - oldWheel;
	oldWheel = currentWheel;

	mouseVelocityScreen = currentMousePosScreen - oldMousePosScreen;
	mouseVelocityDevice = currentMousePosDevice - oldMousePosDevcie;

	oldMousePosScreen = currentMousePosScreen;
	oldMousePosDevcie = currentMousePosDevice;

	///////////////////////////////////////////////////////////////////////////
	//		Check

	GetKeyboardState(keyState);

	for (DWORD i = 0; i < MAX_INPUT_KEY; i++)
	{
		byte key = keyState[i] & 0x80;
		keyState[i] = key ? 1 : 0;

		int oldState = keyOldState[i];
		int state = keyState[i];

		keyDownCount += state;

		if (keyDoubleInfo[i].IsDouble == false)
		{
			if (oldState == 0 && state == 1)
				keyMap[i] = KEY_INPUT_DOWN; //이전 0, 현재 1, Double False - KeyDown
			else if (oldState == 1 && state == 0)
				keyMap[i] = KEY_INPUT_UP; //이전 1, 현재 0, Double False - KeyUp
			else if (oldState == 1 && state == 1)
				keyMap[i] = KEY_INPUT_PRESS; //이전 1, 현재 1, Double False - KeyPress
			else
				keyMap[i] = KEY_INPUT_NONE; //이전 0, 현재 0, Double False - KeyNone
		}
		else
		{
			if (oldState == 1 && state == 0)
				keyMap[i] = KEY_INPUT_DOUBLE_UP; //이전 1, 현재 0, Double True - KeyDoubleUp
			else if (oldState == 1 && state == 1)
				keyMap[i] = KEY_INPUT_DOUBLE_PRESS; //이전 1, 현재 1, Double True - KeyDoublePress
			else
				keyDoubleInfo[i].IsDouble = false;
		}
	}//for(i)

	
	SetAllKeyStateNone();

	///////////////////////////////////////////////////////////////////////////
	//		Double Click
	
	DWORD tButtonStatus = GetTickCount();
	for (DWORD i = 0; i < MAX_INPUT_KEY; i++)
	{
		if (keyDoubleInfo[i].Count > 0)
		{
			if ((tButtonStatus - keyDoubleInfo[i].StartTime) >= timeDblClick)
			{
				keyDoubleInfo[i].IsDouble = false;
				keyDoubleInfo[i].Count = 0;
				keyDoubleInfo[i].StartTime = 0;
			}
		}

		if (keyMap[i] == KEY_INPUT_DOWN)
		{
			if (keyDoubleInfo[i].Count == 2)
			{
				keyMap[i] = KEY_INPUT_DOUBLE_DOWN; //이전 0, 현재 1, Double True - KeyDoubleDown
				keyDoubleInfo[i].IsDouble = true;
				keyDoubleInfo[i].Count = 0;
				keyDoubleInfo[i].StartTime = 0;
			}
			else
			{
				keyDoubleInfo[i].StartTime = tButtonStatus;
				keyDoubleInfo[i].Count++;
			}
		}
		else if (keyDoubleInfo[i].Count == 1 && keyMap[i] == KEY_INPUT_UP)
		{
			keyDoubleInfo[i].Count++;
		}
	}//for(i)
}

LRESULT InputSystem::InputProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_SIZE)
	{
		windowSize.x = (float)LOWORD(lParam);
		windowSize.y = (float)HIWORD(lParam);

		return 0;
	}

	if (message == WM_MOUSEMOVE)
	{
		currentMousePosScreen.x = (float)LOWORD(lParam);
		currentMousePosScreen.y = (float)HIWORD(lParam);

		currentMousePosDevice.x = currentMousePosScreen.x - windowSize.x * 0.5f;
		currentMousePosDevice.y = -(currentMousePosScreen.y - windowSize.y * 0.5f);

		if (mouseInMainWindow == false)
		{
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(tme);
			tme.hwndTrack = MainWindow::Get()->GetHandle();
			tme.dwFlags = TME_LEAVE | TME_HOVER;
			tme.dwHoverTime = 1;
			TrackMouseEvent(&tme);
		}

		return 0;
	}

	if (message == WM_MOUSEHOVER)
	{
		mouseInMainWindow = true;

		return 0;
	}
	

	if (message == WM_MOUSELEAVE)
	{
		mouseInMainWindow = false;

		return 0;
	}

	if (message == WM_MOUSEWHEEL)
	{
		short tWheelValue = (short)HIWORD(wParam);

		currentWheel += tWheelValue;

		return 0;
	}


	return 0;
}

void InputSystem::SetAllKeyStateNone() noexcept
{
	if ((keyState[VK_LBUTTON] == 0 && keyState[VK_RBUTTON] == 0 && keyState[VK_MBUTTON] == 0)
		//&& ImGui::IsMouseHoveringAnyWindow()
		)
	{
		ZeroMemory(keyState, sizeof(keyState));
		ZeroMemory(keyOldState, sizeof(keyOldState));
		ZeroMemory(keyMap, sizeof(keyMap));
		ZeroMemory(keyDoubleInfo, sizeof(keyDoubleInfo));
	}
}
