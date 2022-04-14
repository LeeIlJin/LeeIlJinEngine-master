//	Window System . CPP
///////////////////////////////////////////////////////////////////////////////

//	* WindowSystem
#include "WindowSystem.h"


//	* assert
#include <assert.h>

//	* System
#include "System\Source\System.h"

///////////////////////////////////////////////////////////////////////////////

//	def - pair
typedef std::pair<HWND, Window *> WindowPair;
typedef std::pair<std::wstring, HWND> KeyPair;

typedef std::pair<std::wstring, PROC_FUNCTION> ProcPair;

///////////////////////////////////////////////////////////////////////////////

WindowSystem::WindowSystem(WNDPROC In_Static_Proc_Function, bool * In_System_Finishing_BoolPtr) noexcept
	:main_window(nullptr), static_proc_function(In_Static_Proc_Function), system_finishing_bool_ptr(In_System_Finishing_BoolPtr)
{
	//	...
}

WindowSystem::~WindowSystem() noexcept
{
	//	...
	proc_map.clear();
}

///////////////////////////////////////////////////////////////////////////////
//	IWindowFactory Functions

bool WindowSystem::CreateMainWindow(IWindow *& Out_Window_Ptr, HINSTANCE Window_Instance, const std::wstring & Window_Default_Name, const Vector2 & Window_Size)
{
	if (main_window != nullptr)
		return false;

	if (WindowSystem::CheckDupWindowName(Window_Default_Name) == true)
		return false;


	Window * mainWindow = new Window(static_cast<IWindowManager *>(this));
	main_window = mainWindow;
	//

	WindowDescription desc;

	desc.HInstance = Window_Instance;
	desc.Name = Window_Default_Name;
	desc.Size = Window_Size;
	desc.Position = Vector2(0, 0);
	desc.Style = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW;

	mainWindow->Initialize(static_proc_function, desc);

	float screenX = (float)GetSystemMetrics(SM_CXSCREEN);
	float screenY = (float)GetSystemMetrics(SM_CYSCREEN);

	mainWindow->SetPositionScreenCenter(screenX, screenY);
	
	Out_Window_Ptr = static_cast<IWindow *>(mainWindow);

	
	mainWindow->SetShowWindow(SW_NORMAL);
	return true;
}

bool WindowSystem::CreateSubWindow(IWindow *& Out_Window_Ptr, const WindowDescription & Window_Desc, bool Window_Create_Show)
{
	if (WindowSystem::CheckDupWindowName(Window_Desc.Name) == true)
		return false;


	Window * newSubWindow = new Window(static_cast<IWindowManager *>(this));
	//

	newSubWindow->Initialize(static_proc_function, Window_Desc);

	Out_Window_Ptr = static_cast<IWindow *>(newSubWindow);

	if(Window_Create_Show == true)
		newSubWindow->SetShowWindow(SW_NORMAL);
	else
		newSubWindow->SetShowWindow(SW_HIDE);
	return true;
}

///////////////////////////////////////////////////////////////////////////////
//	IWindowManager Functions

void WindowSystem::InsertWindow(HWND Key_Handle, IWindow * In_Window) noexcept
{
	windows.insert(WindowPair(Key_Handle, static_cast<Window *>(In_Window)));
	window_keys_map.insert(KeyPair(In_Window->GetInfo().DefaultName, Key_Handle));
}

void WindowSystem::EraseWindow(HWND Key_Handle) noexcept
{
	if (windows.count(Key_Handle) > 0)
	{
		released_windows.push_back(windows.at(Key_Handle));

		window_keys_map.erase(windows.at(Key_Handle)->GetInfo().DefaultName);
		windows.erase(Key_Handle);
	}

	if (System::Finishing() == false)
	{
		ClearReleasedWindow();
	}
}

void WindowSystem::GetWindow(IWindow *& Out_Window, const std::wstring & Key_String) noexcept
{
	Window * out = windows.at(window_keys_map.at(Key_String));

	out->AddRef();

	Out_Window = static_cast<IWindow *>(out);
}

void WindowSystem::GetWindow(IWindow *& Out_Window, HWND Key_Handle) noexcept
{
	Window * out = windows.at(Key_Handle);

	out->AddRef();

	Out_Window = static_cast<IWindow *>(out);
}

bool WindowSystem::InputProc(const std::wstring & Key_Name, PROC_FUNCTION Proc_Function_Object) noexcept
{
	if (proc_map.count(Key_Name) > 0)
		return false;

	proc_map.insert(ProcPair(Key_Name, Proc_Function_Object));
	return true;
}

bool WindowSystem::InputProc(const std::wstring & Key_Name, WNDPROC Proc_Function) noexcept
{
	if (proc_map.count(Key_Name) > 0)
		return false;

	proc_map.insert(ProcPair(Key_Name, Proc_Function));
	return true;
}

bool WindowSystem::EraseProc(const std::wstring & Key_Name) noexcept
{
	if (proc_map.count(Key_Name) == 0)
		return false;

	proc_map.erase(Key_Name);
	return true;
}



///////////////////////////////////////////////////////////////////////////////
//	IWindowSystem Functions

LRESULT WindowSystem::WindowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (main_window != nullptr && main_window->GetHandle() == handle)	//	Main Window
	{
		for (ProcPair proc_func : proc_map)
			proc_func.second(handle, message, wParam, lParam);

		if (main_window->WindowProcess(handle, message, wParam, lParam) == true)
			return 0;

		if (message == WM_CLOSE)
		{
			(*system_finishing_bool_ptr) = true;
			main_window = nullptr;
			PostQuitMessage(0);
		}
	}
	else if (windows.count(handle) > 0)		//	Sub Window
	{
		Window * window = windows.at(handle);

		if (window->WindowProcess(handle, message, wParam, lParam) == true)
			return 0;

		if (message == WM_CLOSE)
		{
			window->SetShowWindow(SW_HIDE);
			return 0;
		}
	}

	return DefWindowProc(handle, message, wParam, lParam);;
}

void WindowSystem::Release()
{
	assert(windows.size() == 0 && "There is an not released window.");

	ClearReleasedWindow();
}

///////////////////////////////////////////////////////////////////////////////
//	Private Functions

bool WindowSystem::CheckDupWindowName(const std::wstring & Window_Name)
{
	if (window_keys_map.count(Window_Name) > 0)
		return true;

	return false;
}

void WindowSystem::ClearReleasedWindow()
{
	for (Window * window : released_windows)
	{
		delete window;
	}

	released_windows.clear();
}

