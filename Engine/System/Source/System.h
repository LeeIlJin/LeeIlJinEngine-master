#pragma once
//	* System . H
///////////////////////////////////////////////////////////////////////////////

//	* Interface Of Window System (Factory , Manager)
#include "Window\Public\IWindowSystem.h"

//	* std::function
#include <functional>

//	* std::wstring
#include <string>

///////////////////////////////////////////////////////////////////////////////
class System
{
public:
	///////////////////////////////////////////////////////////////////////////
	//	개체

	//	* Get Window Factory
	//	! Out_Window_Factory : IWindowFactory
	//	= 시스템의 윈도우 시스템으로부터 윈도우 펙토리를 가져옵니다.
	static void GetWindowFactory(IWindowFactory* & Out_Window_Factory);

	//	* Get Window Manager
	//	! Out_Window_Manager : IWindowManager
	//	= 시스템의 윈도우 시스템으로부터 윈도우 관리자를 가져옵니다.
	static void GetWindowManager(IWindowManager* & Out_Window_Manager);

	//	* Set Window System Use Custom Type
	//	<> Template : Custom Window System Type (Interface : IWindowSystem)
	//	= 시스템의 윈도우 시스템의 타입을 임의의 사용자 타입으로 설정합니다.
	//	= 기존의 윈도우 시스템은 여기서 해제 & 삭제 되기 때문에 주의해야합니다.
	template <typename CUSTOM_WINDOW_SYSTEM, typename... Args>
	static void SetCustomWindowSystem(bool Use_System_Finishing_Ptr, Args... args);


	///////////////////////////////////////////////////////////////////////////
	//	상태

	//	* System Finishing?
	//	= 시스템이 종료되고 있을 경우 True를 반환합니다.
	static inline bool Finishing() { return Static_System_Instance.finishing; }

	//	* System Running?
	//	= 시스템이 실행중일 경우 True를 반환합니다.
	static inline bool Running() { return !Static_System_Instance.finishing; }

	///////////////////////////////////////////////////////////////////////////
	//	프로세스

	//	* Input Proc Function To Window Manager
	//	= 프로세스 함수를 Window Manager에 등록하고 성공시, True를 반환합니다.
	static bool InputProc(const std::wstring & Key_Name, PROC_FUNCTION Proc_Function_Object) noexcept;

	//	* Input Proc Function To Window Manager
	//	= 프로세스 함수를 Window Manager에 등록하고 성공시, True를 반환합니다.
	static bool InputProc(const std::wstring & Key_Name, WNDPROC Proc_Function) noexcept;

	//	* Erase Proc Function From Window Manager
	//	= 프로세스 함수를 문자열 키를 통해 등록 해제 합니다.
	static bool EraseProc(const std::wstring & Key_Name) noexcept;


private:
	System();
	~System();

	void Initialize();
	void Release();

private:	// Field
	IWindowSystem * window_system;	// Window System (Factory , Manager)

	bool finishing;					// Is Finishing?


private:	// Static Instance

	static System Static_System_Instance;
	
	// Get Instance
	static inline System & GetInstance() { return Static_System_Instance; }


private:	// 
	//	Proc Function
	static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
};

///////////////////////////////////////////////////////////////////////////////
//		IMPL (구현 부)

//	* Set Window System Use Custom Type
template<typename CUSTOM_WINDOW_SYSTEM, typename... Args>
void System::SetCustomWindowSystem(bool Use_System_Finishing_Ptr, Args... args)
{
	Static_System_Instance.window_system->Release();
	delete (Static_System_Instance.window_system);

	if (Use_System_Finishing_Ptr == true)
		Static_System_Instance.window_system = new CUSTOM_WINDOW_SYSTEM(System::WndProc, &Static_System_Instance.finishing, args...);
	else
		Static_System_Instance.window_system = new CUSTOM_WINDOW_SYSTEM(System::WndProc, args...);

}
