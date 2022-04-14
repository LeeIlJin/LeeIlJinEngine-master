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
	//	= �����츦 ������ �����ڿ� ����մϴ�.
	virtual void InsertWindow(HWND Key_Handle, IWindow * In_Window) noexcept = 0;

	//	* Erase Widnow From Manager
	//	= �����츦 ������ �����ڷκ��� ��� ���� �մϴ�.
	virtual void EraseWindow(HWND Key_Handle) noexcept = 0;

	//	* Get Window From Manager
	//	= ���ڿ� Ű�� ������ ��ü�� �޽��ϴ�.
	virtual void GetWindow(IWindow *& Out_Window, const std::wstring & Key_String) noexcept = 0;

	//	* Get Window From Manager
	//	=  �ڵ� Ű�� ������ ��ü�� �޽��ϴ�.
	virtual void GetWindow(IWindow *& Out_Window, HWND Key_Handle) noexcept = 0;

	//	* Input Proc Function To Manager
	//	= ���μ��� �Լ��� Manager�� ����ϰ� ������, True�� ��ȯ�մϴ�.
	virtual bool InputProc(const std::wstring & Key_Name, PROC_FUNCTION Proc_Function_Object) noexcept = 0;

	//	* Input Proc Function To Manager
	//	= ���μ��� �Լ��� Manager�� ����ϰ� ������, True�� ��ȯ�մϴ�.
	virtual bool InputProc(const std::wstring & Key_Name, WNDPROC Proc_Function) noexcept = 0;

	//	* Erase Proc Function From Manager
	//	= ���μ��� �Լ��� ���ڿ� Ű�� ���� ��� ���� �մϴ�.
	virtual bool EraseProc(const std::wstring & Key_Name) noexcept = 0;
};
