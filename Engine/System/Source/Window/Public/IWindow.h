#pragma once
//	* Interface Of Window

//	* Windows
//	* GWL_STYLE
#include <Windows.h>

//	* Window Description
#include "System\Source\Window\Public\WindowDescription.h"

//	* Window Info
#include "System\Source\Window\Public\WindowInfo.h"

//	* std::function<>
#include <functional>


//	* Process Function Type
typedef std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)> ProcFunctionType;

class IWindow
{
protected:
	//	* 가상 소멸자
	virtual ~IWindow() {}

public:
	//	* Widnow Release
	//	= 윈도우를 해제합니다.
	virtual void Release() = 0;

	//	* Window Get WindowInfo (Copy)
	//	= 윈도우의 정보를 가져옵니다.
	virtual void GetInfo(WindowInfo & Out_Dst_) = 0;

	//	* Window Get WindowInfo (Const Reference)
	//	= 윈도우의 정보를 반환합니다.
	virtual const WindowInfo GetInfo() = 0;

	//	* Main Window Run
	//	[ "While(true)" should not exist inside the Loop Function. ]
	//	! Loop_Function : void()
	//	= 윈도우에서 Loop_Function 을 무한 반복 시킵니다.
	//	= 윈도우에 Destroy 명령이 들어오면 무한 반복에서 탈출합니다.
	virtual WPARAM Run(std::function<void()> Loop_Function) = 0;

	//	* Window Set Name
	//	= 윈도우의 이름을 새로 설정합니다.
	//	[ 윈도우의 등록 이름(Default Name)은 변경되지 않습니다. ]
	virtual void SetName(const std::wstring& New_Name) = 0;

	//	* Window Set Position
	//	= 윈도우의 위치를 새로 설정합니다.
	virtual void SetPosition(const Vector2& New_Position) = 0;

	//	* Window Set Position To Screen Center
	//	= 윈도우를 Screen_Width(스크린 가로 길이) : Screen_Height(스크린 세로 길이) 에 맞게 중앙에 위치하게 합니다.
	virtual void SetPositionScreenCenter(float Screen_Width, float Screen_Height, float Screen_Start_X = 0.0f, float Screen_Start_Y = 0.0f) = 0;

	//	* Window Set Size
	//	= 윈도우의 크기를 새로 설정합니다.
	virtual void SetSize(const Vector2& New_Size) = 0;

	/*
		* Window Change Window Style
		! NIndex (Default = GWL_STYLE)
		@ GWL_STYLE           (-16)
		@ GWL_EXSTYLE         (-20)
		s================================
		! New_Style (Window Style)
		@ WS_ ~~
		= 윈도우의 스타일을 새로 설정합니다.
	*/
	virtual void ChangeWindowStyle(DWORD New_Style, int NIndex = GWL_STYLE) = 0;

	/*
		* Window Set Show
		! Flag_
		@ SW_HIDE             0
		@ SW_SHOWNORMAL       1
		@ SW_NORMAL           1
		@ SW_SHOWMINIMIZED    2
		@ SW_SHOWMAXIMIZED    3
		@ SW_MAXIMIZE         3
		@ SW_SHOWNOACTIVATE   4
		@ SW_SHOW             5
		@ SW_MINIMIZE         6
		@ SW_SHOWMINNOACTIVE  7
		@ SW_SHOWNA           8
		@ SW_RESTORE          9
		@ SW_SHOWDEFAULT      10
		@ SW_FORCEMINIMIZE    11
		@ SW_MAX              11
		= 윈도우의 보기 상태를 설정합니다.
	*/
	virtual void SetShowWindow(int Flag_) = 0;

	//	* Window Set Focus
	//	= 윈도우를 포커스 합니다. (레이어에서 가장 위에 위치하게 한다.)
	virtual void SetFocusWindow() = 0;

	//	* Window Get Handle
	//	= 윈도우의 핸들을 반환합니다.
	virtual HWND GetHandle() = 0;

	//	* Window Get Parent Handle
	//	= 윈도우의 부모의 핸들을 반환합니다.
	virtual HWND GetParentHandle() = 0;

};
