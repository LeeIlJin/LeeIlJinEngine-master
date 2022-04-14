#pragma once

//	* IWindowFactory
#include "System\Source\Window\Public\IWindowFactory.h"

//	* IWindowManager
#include "System\Source\Window\Public\IWindowManager.h"

class IWindowSystem : public IWindowFactory , public IWindowManager
{
	friend class System;
protected:
	virtual ~IWindowSystem() {}

	//	* Window System Release
	//	= 윈도우 시스템을 해제합니다.
	virtual void Release() = 0;

	//	* Widnow Proc
	//	= 윈도우 프로세스 함수
	virtual LRESULT WindowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) = 0;

};

