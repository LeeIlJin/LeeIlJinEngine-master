//	* Window . CPP
///////////////////////////////////////////////////////////////////////////////

//	* Window
#include "Window.h"

//	* assert
#include <assert.h>


///////////////////////////////////////////////////////////////////////////////
//	Public Constructor & Annihilator

Window::Window(IWindowManager * In_Window_Manager) noexcept
	: owner_manager(In_Window_Manager), ref_count(1)
{
	//	...
	assert(In_Window_Manager != nullptr && "The manager for that window is NULL.");
}

Window::~Window() noexcept
{
	//	...
	assert(owner_manager == nullptr && "This is not released.");
}

///////////////////////////////////////////////////////////////////////////////
//	IWindow Functions

void Window::Release()
{
	ref_count--;
	if (ref_count <= 0 && owner_manager != nullptr)
	{
		this->ReleaseWindow();
		IWindowManager * temp_manager = owner_manager;
		owner_manager = nullptr;

		temp_manager->EraseWindow(info.Handle);
	}
}

void Window::GetInfo(WindowInfo & Out_Dst_)
{
	Out_Dst_ = info;
}

const WindowInfo Window::GetInfo()
{
	return info;
}

WPARAM Window::Run(std::function<void()> Loop_Function)
{
	MSG msg = { 0 };

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;
		}

		Loop_Function();

	}

	return msg.wParam;
}

void Window::SetName(const std::wstring & New_Name)
{
	info.Name = New_Name;
	SetWindowText(info.Handle, info.Name.c_str());
}

void Window::SetPosition(const Vector2 & New_Position)
{
	info.Position = New_Position;

	SetWindowSizeAndPosition(SWP_NOSIZE | SWP_NOZORDER);
}

void Window::SetPositionScreenCenter(float Screen_Width, float Screen_Height, float Screen_Start_X, float Screen_Start_Y)
{
	info.Position.x = Screen_Start_X + ((Screen_Width - info.Size.x) / 2.0f);
	info.Position.y = Screen_Start_Y + ((Screen_Height - info.Size.y) / 2.0f);

	SetWindowSizeAndPosition(SWP_NOSIZE | SWP_NOZORDER);
}

void Window::SetSize(const Vector2 & New_Size)
{
	info.Size = New_Size;

	SetWindowSizeAndPosition(SWP_NOMOVE | SWP_NOZORDER);
}

void Window::ChangeWindowStyle(DWORD New_Style, int NIndex)
{
	info.Style = New_Style;
	SetWindowLongPtr(info.Handle, NIndex, info.Style);
	SetWindowSizeAndPosition(SWP_NOMOVE | SWP_NOZORDER);
}

void Window::SetShowWindow(int Flag_)
{
	ShowWindow(info.Handle, Flag_);

	if (Flag_ == SW_HIDE)
		info.IsHiding = true;
	else
		info.IsHiding = false;
}

void Window::SetFocusWindow()
{
	SetFocus(info.Handle);
}

HWND Window::GetHandle()
{
	return info.Handle;
}

HWND Window::GetParentHandle()
{
	return info.ParentHandle;
}

///////////////////////////////////////////////////////////////////////////////
//	Public Functions

void Window::Initialize(WNDPROC Static_Proc_, const WindowDescription & Desc_)
{
	info.HInstance = Desc_.HInstance;
	info.ParentHandle = Desc_.ParentHandle;
	info.Style = Desc_.Style;
	info.Size = Desc_.Size;
	info.Position = Desc_.Position;
	info.Name = Desc_.Name;

	if (info.HInstance == nullptr)
	{
		info.HInstance = GetModuleHandle(NULL);
	}

	//	초기 설정 윈도우 이름은 DefaultName에 들어가며 이는 Window 자체에 등록된다.
	assert(info.Name.length() >= 1 && "Window Name is empty.");

	info.DefaultName = info.Name;

	this->InitializeWindow(Static_Proc_);

	owner_manager->InsertWindow(info.Handle, this);
}

///////////////////////////////////////////////////////////////////////////////
//	Protected Functions

void Window::InitializeWindow(WNDPROC Static_Proc_Function)
{
	WNDCLASSEX wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hIconSm = wndClass.hIcon;
	wndClass.hInstance = info.HInstance;
	wndClass.lpfnWndProc = Static_Proc_Function;
	wndClass.lpszClassName = info.DefaultName.c_str();
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClass.cbSize = sizeof(WNDCLASSEX);

	WORD wHr = RegisterClassEx(&wndClass);
	assert(wHr != 0);

	info.Handle = CreateWindowEx
	(
		WS_EX_APPWINDOW
		, info.DefaultName.c_str()
		, info.Name.c_str()
		, info.Style
		, CW_USEDEFAULT
		, CW_USEDEFAULT
		, CW_USEDEFAULT
		, CW_USEDEFAULT
		, info.ParentHandle
		, (HMENU)NULL
		, info.HInstance
		, NULL
	);
	assert(info.Handle != NULL && "Window creating failed.");
	//

	this->SetWindowSizeAndPosition(SWP_NOZORDER);

	UpdateWindow(info.Handle);
}

void Window::ReleaseWindow()
{
	DestroyWindow(info.Handle);

	UnregisterClass(info.DefaultName.c_str(), info.HInstance);
}

void Window::SetWindowSizeAndPosition(UINT Flag_)
{
	RECT rect = { 0, 0, (LONG)info.Size.x, (LONG)info.Size.y };

	AdjustWindowRect(&rect, info.Style, FALSE);

	SetWindowPos(info.Handle, NULL
		, (int)info.Position.x, (int)info.Position.y
		, (int)info.Size.x, (int)info.Size.y
		, Flag_);
}




///////////////////////////////////////////////////////////////////////////////
//	Proc

bool Window::WindowProcess(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	///////////////////////////////////////////////////////////////////////////
	//	Move , Size , Close|Destroy Check
	switch (message)
	{
	case WM_SIZING:	// ReSizing
	{
		//
	}
	return true;
	case WM_SIZE:	// Resize Complete	: Can Get The Size Value
	{
		this->info.Size.x = (float)LOWORD(lParam);
		this->info.Size.y = (float)HIWORD(lParam);

		if (wParam == SIZE_MINIMIZED)
		{
			if (this->info.IsMaximized == true)
				this->info.IsMaximized = false;

			this->info.IsMinimized = true;
		}
		else if (wParam == SIZE_MAXIMIZED)
		{
			if (this->info.IsMinimized == true)
				this->info.IsMinimized = false;

			this->info.IsMaximized = true;
		}

		if (wParam == SIZE_RESTORED)
		{
			if (this->info.IsMinimized == true)
				this->info.IsMinimized = false;

			if (this->info.IsMaximized == true)
				this->info.IsMaximized = false;
		}

	}
	return true;
	case WM_MOVING:	// Moving
	{
		//
	}
	return true;
	case WM_MOVE:	// Moving Complete	: Can Get The Position Value
	{
		this->info.Position.x = (float)LOWORD(lParam);
		this->info.Position.y = (float)HIWORD(lParam);
	}
	return true;
	default:
		break;
	}

	///////////////////////////////////////////////////////////////////////////
	//	Mouse Hover Check
	{
		if (message == WM_MOUSEMOVE)
		{
			if (this->info.IsHavingMouse == false)
			{
				TRACKMOUSEEVENT tme;
				tme.cbSize = sizeof(tme);
				tme.hwndTrack = this->info.Handle;
				tme.dwFlags = TME_LEAVE | TME_HOVER;
				tme.dwHoverTime = 1;
				TrackMouseEvent(&tme);
			}

			return true;
		}

		if (message == WM_MOUSEHOVER)
		{
			this->info.IsHavingMouse = true;

			return true;
		}


		if (message == WM_MOUSELEAVE)
		{
			this->info.IsHavingMouse = false;

			return true;
		}
	}

	return false;
}
