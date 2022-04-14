#include "System\MySystem.h"
#include "System\MyLibIncluder.h"

class TestLoop
{
public:
	TestLoop() {}
	~TestLoop() {}

	void Initialize()
	{
		IWindowManager * manager;
		System::GetWindowManager(manager);

		manager->GetWindow(sub1, L"SUB1");
		manager->GetWindow(sub2, L"SUB2");
	}

	void Loop()
	{
		// ...

		if (sub1 != nullptr && sub1->GetInfo().IsHiding == true)
		{
			SAFE_RELEASE(sub1);
		}
		if (sub2 != nullptr && sub2->GetInfo().IsHiding == true)
		{
			SAFE_RELEASE(sub2);
		}
	}

	void Release()
	{
		if(sub1 != NULL)
			sub1->Release();
		if (sub2 != NULL)
			sub2->Release();
	}

private:
	IWindow * sub1;
	IWindow * sub2;
};

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR param, int command)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	//_CrtSetBreakAlloc(브레이크 포인터를 걸 주소 번호);
#endif

	IWindow * mainWindow;
	IWindow * sub1;
	IWindow * sub2;
	IWindowFactory * windowFactory;

	
	System::GetWindowFactory(windowFactory);
	
	windowFactory->CreateMainWindow(mainWindow, instance);

	windowFactory->CreateSubWindow(sub1, WindowDescription(nullptr, mainWindow->GetHandle(), WS_CAPTION | WS_SYSMENU | WS_CHILD | WS_MINIMIZEBOX
		, L"SUB1", Vector2(300, 300), Vector2(0, 0)), true);

	windowFactory->CreateSubWindow(sub2, WindowDescription(nullptr, mainWindow->GetHandle(), WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX
		, L"SUB2", Vector2(300, 300), Vector2(600, 600)), true);

	mainWindow->SetFocusWindow();

	TestLoop * loopC = new TestLoop;

	loopC->Initialize();
	sub1->Release();

	WPARAM wParam = mainWindow->Run(BIND_FUNCTION_0(TestLoop, Loop, loopC));
	loopC->Release();

	SAFE_DELETE(loopC);

	mainWindow->Release();
	sub2->Release();


	return wParam;
}

