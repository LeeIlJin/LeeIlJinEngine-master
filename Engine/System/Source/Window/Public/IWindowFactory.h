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
	//	= 메인 윈도우를 생성하고 성공시, True를 반환합니다.
	//	= 메인 윈도우가 이미 생성됬거나 실패했을 경우, False를 반환합니다.
	virtual bool CreateMainWindow(IWindow *& Out_Window_Ptr, HINSTANCE Window_Instance, const std::wstring& Window_Default_Name = L"Game", const Vector2& Window_Size = Vector2(1240, 720)) = 0;

	//	* Create Sub Window
	//	! Out_Window_Ptr : IWindow
	//	= 일반 윈도우를 생성하고 성공시, True를 반환합니다.
	virtual bool CreateSubWindow(IWindow *& Out_Window_Ptr, const WindowDescription& Window_Desc, bool Window_Create_Show) = 0;

};
