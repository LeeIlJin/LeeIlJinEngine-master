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
	//	��ü

	//	* Get Window Factory
	//	! Out_Window_Factory : IWindowFactory
	//	= �ý����� ������ �ý������κ��� ������ ���丮�� �����ɴϴ�.
	static void GetWindowFactory(IWindowFactory* & Out_Window_Factory);

	//	* Get Window Manager
	//	! Out_Window_Manager : IWindowManager
	//	= �ý����� ������ �ý������κ��� ������ �����ڸ� �����ɴϴ�.
	static void GetWindowManager(IWindowManager* & Out_Window_Manager);

	//	* Set Window System Use Custom Type
	//	<> Template : Custom Window System Type (Interface : IWindowSystem)
	//	= �ý����� ������ �ý����� Ÿ���� ������ ����� Ÿ������ �����մϴ�.
	//	= ������ ������ �ý����� ���⼭ ���� & ���� �Ǳ� ������ �����ؾ��մϴ�.
	template <typename CUSTOM_WINDOW_SYSTEM, typename... Args>
	static void SetCustomWindowSystem(bool Use_System_Finishing_Ptr, Args... args);


	///////////////////////////////////////////////////////////////////////////
	//	����

	//	* System Finishing?
	//	= �ý����� ����ǰ� ���� ��� True�� ��ȯ�մϴ�.
	static inline bool Finishing() { return Static_System_Instance.finishing; }

	//	* System Running?
	//	= �ý����� �������� ��� True�� ��ȯ�մϴ�.
	static inline bool Running() { return !Static_System_Instance.finishing; }

	///////////////////////////////////////////////////////////////////////////
	//	���μ���

	//	* Input Proc Function To Window Manager
	//	= ���μ��� �Լ��� Window Manager�� ����ϰ� ������, True�� ��ȯ�մϴ�.
	static bool InputProc(const std::wstring & Key_Name, PROC_FUNCTION Proc_Function_Object) noexcept;

	//	* Input Proc Function To Window Manager
	//	= ���μ��� �Լ��� Window Manager�� ����ϰ� ������, True�� ��ȯ�մϴ�.
	static bool InputProc(const std::wstring & Key_Name, WNDPROC Proc_Function) noexcept;

	//	* Erase Proc Function From Window Manager
	//	= ���μ��� �Լ��� ���ڿ� Ű�� ���� ��� ���� �մϴ�.
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
//		IMPL (���� ��)

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
