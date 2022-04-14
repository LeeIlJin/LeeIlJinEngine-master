#pragma once
//	* Window . H
///////////////////////////////////////////////////////////////////////////////

//	* Interface Of Window
#include "System\Source\Window\Public\IWindow.h"

//	* IWindowManager
#include "System\Source\Window\Public\IWindowManager.h"


///////////////////////////////////////////////////////////////////////////////
class Window : public IWindow
{
public:		// Constructor & Annihilator
	Window(IWindowManager * In_Window_Manager) noexcept;
	virtual ~Window() noexcept;


	///////////////////////////////////////////////////////////////////////////
public:		// IWindow Functions
	void Release() override;

	void GetInfo(WindowInfo & Out_Dst_) override;
	const WindowInfo GetInfo() override;

	virtual WPARAM Run(std::function<void()> Loop_Function) override;

	void SetName(const std::wstring & New_Name) override;
	void SetPosition(const Vector2 & New_Position) override;
	void SetPositionScreenCenter(float Screen_Width, float Screen_Height, float Screen_Start_X = 0.0f, float Screen_Start_Y = 0.0f) override;
	void SetSize(const Vector2 & New_Size) override;

	void ChangeWindowStyle(DWORD New_Style, int NIndex = GWL_STYLE) override;
	void SetShowWindow(int Flag_) override;
	void SetFocusWindow() override;

	HWND GetHandle() override;
	HWND GetParentHandle() override;


	///////////////////////////////////////////////////////////////////////////
public:		// Public Functions
	void Initialize(WNDPROC Static_Proc_, const WindowDescription & Desc_);
	inline bool IsReleased() noexcept
	{
		return (owner_manager == nullptr);
	}

	//	Window Process ... (TRUE 를 반환 할 경우엔 그 이하의 처리를 모두 생략한다.)
	//	(자식 클래스에 오버라이드 할 경우 부모의 것도 돌려줘야 한다. = __super::WindowProcess(handle,message,wParam,lParam))
	virtual bool WindowProcess(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

	inline void AddRef() { ref_count++; }

protected:	// Protected Functions
	virtual void InitializeWindow(WNDPROC Static_Proc_Function);
	virtual void ReleaseWindow();

	/*
		! Flag_

		@ SWP_NOSIZE          0x0001	
		@ SWP_NOMOVE          0x0002
		@ SWP_NOZORDER        0x0004
		@ SWP_NOREDRAW        0x0008
		@ SWP_NOACTIVATE      0x0010
		@ SWP_FRAMECHANGED    0x0020   The frame changed: send WM_NCCALCSIZE
		@ SWP_SHOWWINDOW      0x0040
		@ SWP_HIDEWINDOW      0x0080
		@ SWP_NOCOPYBITS      0x0100
		@ SWP_NOOWNERZORDER   0x0200   Don't do owner Z ordering 
		@ SWP_NOSENDCHANGING  0x0400   Don't send WM_WINDOWPOSCHANGING 
		
		@ SWP_DRAWFRAME       SWP_FRAMECHANGED
		@ SWP_NOREPOSITION    SWP_NOOWNERZORDER
	*/
	void SetWindowSizeAndPosition(UINT Flag_);

	///////////////////////////////////////////////////////////////////////////
protected:	// Field
	WindowInfo info;

	IWindowManager * owner_manager;

	UINT ref_count;
};
