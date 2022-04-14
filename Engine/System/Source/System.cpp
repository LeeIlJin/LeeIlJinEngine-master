//	* System . CPP
///////////////////////////////////////////////////////////////////////////////

//	* System
#include "System.h"


//	* MyMacro
#include "MyMacro.h"

//	* WindowSystem
#include "Window\Private\WindowSystem.h"

///////////////////////////////////////////////////////////////////////////////

//	Static System Object
System System::Static_System_Instance;

///////////////////////////////////////////////////////////////////////////////

void System::GetWindowFactory(IWindowFactory* & Out_Window_Factory)
{
	//	Window System을 Window Factory 로 캐스트하여 주소를 줍니다.
	Out_Window_Factory = static_cast<IWindowFactory *>(Static_System_Instance.window_system);
}

void System::GetWindowManager(IWindowManager *& Out_Window_Manager)
{
	//	Window System을 Window Manager 로 캐스트하여 주소를 줍니다.
	Out_Window_Manager = static_cast<IWindowManager *>(Static_System_Instance.window_system);
}

///////////////////////////////////////////////////////////////////////////////

bool System::InputProc(const std::wstring & Key_Name, PROC_FUNCTION Proc_Function_Object) noexcept
{
	return Static_System_Instance.window_system->InputProc(Key_Name, Proc_Function_Object);
}

bool System::InputProc(const std::wstring & Key_Name, WNDPROC Proc_Function) noexcept
{
	return Static_System_Instance.window_system->InputProc(Key_Name, Proc_Function);
}

bool System::EraseProc(const std::wstring & Key_Name) noexcept
{
	return Static_System_Instance.window_system->EraseProc(Key_Name);
}

///////////////////////////////////////////////////////////////////////////////

System::System()
	:finishing(false)
{
	Initialize();
}

System::~System()
{
	finishing = true;

	Release();

	//	Window System 삭제
	SAFE_DELETE(window_system);
}

void System::Initialize()
{
	//	Window System 생성
	window_system = new WindowSystem(System::WndProc, &finishing);

}

void System::Release()
{
	//	Widnow System 해제
	window_system->Release();

}

///////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK System::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	return GetInstance().window_system->WindowProc(handle, message, wParam, lParam);
}

