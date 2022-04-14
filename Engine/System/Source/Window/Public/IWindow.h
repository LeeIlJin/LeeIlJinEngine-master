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
	//	* ���� �Ҹ���
	virtual ~IWindow() {}

public:
	//	* Widnow Release
	//	= �����츦 �����մϴ�.
	virtual void Release() = 0;

	//	* Window Get WindowInfo (Copy)
	//	= �������� ������ �����ɴϴ�.
	virtual void GetInfo(WindowInfo & Out_Dst_) = 0;

	//	* Window Get WindowInfo (Const Reference)
	//	= �������� ������ ��ȯ�մϴ�.
	virtual const WindowInfo GetInfo() = 0;

	//	* Main Window Run
	//	[ "While(true)" should not exist inside the Loop Function. ]
	//	! Loop_Function : void()
	//	= �����쿡�� Loop_Function �� ���� �ݺ� ��ŵ�ϴ�.
	//	= �����쿡 Destroy ����� ������ ���� �ݺ����� Ż���մϴ�.
	virtual WPARAM Run(std::function<void()> Loop_Function) = 0;

	//	* Window Set Name
	//	= �������� �̸��� ���� �����մϴ�.
	//	[ �������� ��� �̸�(Default Name)�� ������� �ʽ��ϴ�. ]
	virtual void SetName(const std::wstring& New_Name) = 0;

	//	* Window Set Position
	//	= �������� ��ġ�� ���� �����մϴ�.
	virtual void SetPosition(const Vector2& New_Position) = 0;

	//	* Window Set Position To Screen Center
	//	= �����츦 Screen_Width(��ũ�� ���� ����) : Screen_Height(��ũ�� ���� ����) �� �°� �߾ӿ� ��ġ�ϰ� �մϴ�.
	virtual void SetPositionScreenCenter(float Screen_Width, float Screen_Height, float Screen_Start_X = 0.0f, float Screen_Start_Y = 0.0f) = 0;

	//	* Window Set Size
	//	= �������� ũ�⸦ ���� �����մϴ�.
	virtual void SetSize(const Vector2& New_Size) = 0;

	/*
		* Window Change Window Style
		! NIndex (Default = GWL_STYLE)
		@ GWL_STYLE           (-16)
		@ GWL_EXSTYLE         (-20)
		s================================
		! New_Style (Window Style)
		@ WS_ ~~
		= �������� ��Ÿ���� ���� �����մϴ�.
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
		= �������� ���� ���¸� �����մϴ�.
	*/
	virtual void SetShowWindow(int Flag_) = 0;

	//	* Window Set Focus
	//	= �����츦 ��Ŀ�� �մϴ�. (���̾�� ���� ���� ��ġ�ϰ� �Ѵ�.)
	virtual void SetFocusWindow() = 0;

	//	* Window Get Handle
	//	= �������� �ڵ��� ��ȯ�մϴ�.
	virtual HWND GetHandle() = 0;

	//	* Window Get Parent Handle
	//	= �������� �θ��� �ڵ��� ��ȯ�մϴ�.
	virtual HWND GetParentHandle() = 0;

};
