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
	//	= ������ �ý����� �����մϴ�.
	virtual void Release() = 0;

	//	* Widnow Proc
	//	= ������ ���μ��� �Լ�
	virtual LRESULT WindowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) = 0;

};

