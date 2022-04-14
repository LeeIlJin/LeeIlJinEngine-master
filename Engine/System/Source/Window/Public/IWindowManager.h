#pragma once

//	Interface For Window <-> WindowSystem

#include "System\Source\Window\Public\IWindow.h"

typedef std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)> PROC_FUNCTION;

class IWindowManager
{
protected:
	virtual ~IWindowManager() {}

public:
	//	* Insert Window To Manager
	//	! In_Window : IWindow
	//	= 윈도우를 윈도우 관리자에 등록합니다.
	virtual void InsertWindow(HWND Key_Handle, IWindow * In_Window) noexcept = 0;

	//	* Erase Widnow From Manager
	//	= 윈도우를 윈도우 관리자로부터 등록 해제 합니다.
	virtual void EraseWindow(HWND Key_Handle) noexcept = 0;

	//	* Get Window From Manager
	//	= 문자열 키로 윈도우 개체를 받습니다.
	virtual void GetWindow(IWindow *& Out_Window, const std::wstring & Key_String) noexcept = 0;

	//	* Get Window From Manager
	//	=  핸들 키로 윈도우 개체를 받습니다.
	virtual void GetWindow(IWindow *& Out_Window, HWND Key_Handle) noexcept = 0;

	//	* Input Proc Function To Manager
	//	= 프로세스 함수를 Manager에 등록하고 성공시, True를 반환합니다.
	virtual bool InputProc(const std::wstring & Key_Name, PROC_FUNCTION Proc_Function_Object) noexcept = 0;

	//	* Input Proc Function To Manager
	//	= 프로세스 함수를 Manager에 등록하고 성공시, True를 반환합니다.
	virtual bool InputProc(const std::wstring & Key_Name, WNDPROC Proc_Function) noexcept = 0;

	//	* Erase Proc Function From Manager
	//	= 프로세스 함수를 문자열 키를 통해 등록 해제 합니다.
	virtual bool EraseProc(const std::wstring & Key_Name) noexcept = 0;
};
