#pragma once

#define EXTERN_IMGUI_WND_PROC_HANDLER extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
#define IMGUI_WND_PROC_HANDLER(handle,message,wParam,lParam) ImGui_ImplWin32_WndProcHandler(handle, message, wParam, lParam)

class ImGuiHelper
{
public:
	static void CreateImGui(void* hwnd, void* device, void* deviceContext);
	static void SetStyle();
	static void DeleteImGui();

	static void UpdateStart();
	static void RenderReady();
	static void Render();

	static void Validate();
	static void Invalidate();
};
