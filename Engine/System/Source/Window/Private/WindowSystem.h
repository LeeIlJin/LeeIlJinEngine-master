#pragma once
//	Window System . H
///////////////////////////////////////////////////////////////////////////////

//	* Interface Of WindowSystem
#include "System\Source\Window\Public\IWindowSystem.h"


//	* std::vector
#include <vector>

//	* std::unordered_map
#include <unordered_map>

//	* std::wstring
#include <string>

//	* Window
#include "System\Source\Window\Private\Window.h"


///////////////////////////////////////////////////////////////////////////////
class WindowSystem : public IWindowSystem
{
public:		// Constructor & Annihilator
	WindowSystem(WNDPROC In_Static_Proc_Function, bool * In_System_Finishing_BoolPtr) noexcept;
	virtual ~WindowSystem() noexcept;


	///////////////////////////////////////////////////////////////////////////
public:		// IWindowFactory Functions
	bool CreateMainWindow(IWindow *& Out_Window_Ptr, HINSTANCE Window_Instance, const std::wstring & Window_Default_Name = L"Game", const Vector2 & Window_Size = Vector2(1240, 720)) override;
	bool CreateSubWindow(IWindow *& Out_Window_Ptr, const WindowDescription & Window_Desc, bool Window_Create_Show) override;


	///////////////////////////////////////////////////////////////////////////
public:		// IWindowManager Functions
	void InsertWindow(HWND Key_Handle, IWindow * In_Window) noexcept override;
	void EraseWindow(HWND Key_Handle) noexcept override;

	void GetWindow(IWindow *& Out_Window, const std::wstring & Key_String) noexcept override;
	void GetWindow(IWindow *& Out_Window, HWND Key_Handle) noexcept override;

	bool InputProc(const std::wstring & Key_Name, PROC_FUNCTION Proc_Function_Object) noexcept override;
	bool InputProc(const std::wstring & Key_Name, WNDPROC Proc_Function) noexcept override;
	bool EraseProc(const std::wstring & Key_Name) noexcept override;

	///////////////////////////////////////////////////////////////////////////
public:		// IWindowSystem Functions
	void Release() override;
	LRESULT WindowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) override;


	///////////////////////////////////////////////////////////////////////////
private:	// Private Functions

	//	�� Factory ��ü�� ���� ������ Window �� �� �ߺ��� �̸��� �����ϴ��� Ȯ���մϴ�.
	//	������ ��쿡 TRUE ��ȯ
	bool CheckDupWindowName(const std::wstring & Window_Name);

	void ClearReleasedWindow();

	///////////////////////////////////////////////////////////////////////////
private:	// Field
	Window * main_window;

	std::unordered_map<HWND, Window *> windows;
	std::unordered_map<std::wstring, HWND> window_keys_map;

	std::vector<Window *> released_windows;

	//	proc
	std::unordered_map<std::wstring, PROC_FUNCTION> proc_map;


	WNDPROC static_proc_function;
	bool * system_finishing_bool_ptr;
};
