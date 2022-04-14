#include "MySystem.h"
#include "Application.h"

#include "psapi.h"

bool Application::bGameRunning = false;

bool Application::bUseImGui = false;

//	ImGui Function Call
//	ImGuiHelper :: SetStyle
//	ImGuiHelper :: Update Start
//	ImGuiHelper :: Render Ready
//	ImGuiHelper :: Render
void Loop();

void Application::CreateApplication(HINSTANCE hinstance, DWORD window_style, Color background_color, LPCWSTR window_name, IntPoint window_size, IntPoint window_pos, bool full_screen, bool vertical_sync)
{
	bGameRunning = true;

	MainWindow::CreateInstance(hinstance,window_style,window_name,window_size,window_pos,full_screen);
	SystemManager::CreateInstance(MainWindow::GetDescription(), background_color, vertical_sync);
	//
}

WPARAM Application::RunApplication()
{
	WPARAM returnParam;

	SystemManager::BeginSystem();

	//	Test
	{
		MEMORYSTATUSEX memInfo;
		memInfo.dwLength = sizeof(MEMORYSTATUSEX);
		GlobalMemoryStatusEx(&memInfo);
		DWORDLONG totalVirtualMem = memInfo.ullTotalPageFile;
		DWORDLONG virtualMemUsed = memInfo.ullTotalPageFile - memInfo.ullAvailPageFile;

		PROCESS_MEMORY_COUNTERS pmc;
		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		SIZE_T virtualMemUsedByMe = pmc.PagefileUsage;

		int a = 10;

		PointListAllocator allocator;
		allocator.buffer_set(100000000);

		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		virtualMemUsedByMe = pmc.PagefileUsage;

		int b = 20;

		allocator.buffer_clear();

		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		virtualMemUsedByMe = pmc.PagefileUsage;

		int c = 30;

	}


	//	ImGui Function !
	if (Application::IsUseImGui() == true)
		ImGuiHelper::SetStyle();

	SystemManager::Time()->AddTimer("FPSPrintTimer", true, 1.0f, 0.25f, false);

	returnParam = MainWindow::Get()->Run(&Loop);

	SystemManager::EndSystem();

	return returnParam;
}

void Application::DestroyApplication()
{
	SystemManager::DestroyInstance();
	MainWindow::DestroyInstance();
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//	TODO: Loop Function

//	* Loop Function
void Loop()
{

	//	~ Update
	{
		//	ImGui Function !
		if (Application::IsUseImGui() == true)
			ImGuiHelper::UpdateStart();
		//
		SystemManager::UpdateSystem();

		if (SystemManager::Time()->TimerGetRunningTime("FPSPrintTimer") >= 0.25f)
		{
			wstring name = MainWindow::Get()->GetDefaultName();
			name += L" FPS : " + to_wstring(SystemManager::Time()->GetFPS());

			MainWindow::Get()->SetName(name);

			SystemManager::Time()->TimerResetRunningTime("FPSPrintTimer");
			SystemManager::Time()->TimerStart("FPSPrintTimer");
		}
	}

	// TOOD: Delete This Later
	if (Application::IsUseImGui())
	{
		ImGui::Begin("Test");
		ImGui::Text("Text");
		ImGui::End();
	}

	//	~ Render
	{
		//	ImGui Function !
		if (Application::IsUseImGui() == true)
			ImGuiHelper::RenderReady();

		SystemManager::Graphic()->SetMainRenderTarget();
		SystemManager::Graphic()->Clear();
		//

		SystemManager::RenderSystem();

		//	ImGui Function !
		if(Application::IsUseImGui() == true)
			ImGuiHelper::Render();
		//
		SystemManager::Graphic()->Present();
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
