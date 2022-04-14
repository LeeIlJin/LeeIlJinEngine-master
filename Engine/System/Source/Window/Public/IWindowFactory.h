#pragma once


//	* IWindow
#include "System\Source\Window\Public\IWindow.h"


class IWindowFactory
{
protected:
	virtual ~IWindowFactory() {}

public:
	//	* Create Main Window
	//	! Out_Window_Ptr : IWindow
	//	= ���� �����츦 �����ϰ� ������, True�� ��ȯ�մϴ�.
	//	= ���� �����찡 �̹� ������ų� �������� ���, False�� ��ȯ�մϴ�.
	virtual bool CreateMainWindow(IWindow *& Out_Window_Ptr, HINSTANCE Window_Instance, const std::wstring& Window_Default_Name = L"Game", const Vector2& Window_Size = Vector2(1240, 720)) = 0;

	//	* Create Sub Window
	//	! Out_Window_Ptr : IWindow
	//	= �Ϲ� �����츦 �����ϰ� ������, True�� ��ȯ�մϴ�.
	virtual bool CreateSubWindow(IWindow *& Out_Window_Ptr, const WindowDescription& Window_Desc, bool Window_Create_Show) = 0;

};
