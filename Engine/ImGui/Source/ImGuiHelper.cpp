#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include "ImGuiHelper.h"

void ImGuiHelper::CreateImGui(void * hwnd, void* device, void* deviceContext)
{
	ImGui_ImplWin32_EnableDpiAwareness();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking

	//	ImGui 윈도우를 실제 윈도우화 시킵니다. (메인 윈도우로부터 바깥으로 꺼낼 수 있음)
	//	[ 단점 : 매우 무거워집니다. ]
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

	io.ConfigWindowsMoveFromTitleBarOnly = true;
	
	//	Shift 키를 눌러야 Docking 할 수 있도록 합니다. (false 일 경우엔, 항상 Docking 가능)
	//io.ConfigDockingWithShift = true;


	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(reinterpret_cast<ID3D11Device*>(device), reinterpret_cast<ID3D11DeviceContext*>(deviceContext));

	// Setup Style
	//ImGui::StyleColorsDark();
	ImGui::StyleColorsClassic();
}

void ImGuiHelper::SetStyle()
{
	ImGuiStyle * style = &ImGui::GetStyle();

	//	Size
	style->ScaleAllSizes(0.7f);
	style->ItemSpacing.y = 4;
	style->IndentSpacing = 25.0f;
	style->ScrollbarSize = 14.0f;
	style->GrabMinSize = 8.0f;

	// Rounding
	style->ScrollbarRounding = 0.0f;
	style->GrabRounding = 0.0f;
	style->WindowRounding = 0.0f;
	style->ChildRounding = 0.0f;
	style->FrameRounding = 0.0f;
	style->TabRounding = 0.0f;
	style->PopupRounding = 0.0f;


	//	Color
	style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_WindowBg] = ImVec4(0.09f, 0.09f, 0.11f, 1.00f);
	style->Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.09f, 0.09f, 0.11f, 1.00f);
	style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
	style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 1.00f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.15f, 0.14f, 0.17f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.19f, 0.22f, 1.00f);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.43f, 0.41f, 0.42f, 1.00f);
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.17f, 0.17f, 0.19f, 1.00f);
	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.14f, 0.17f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.26f, 0.25f, 0.27f, 1.00f);
	style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Button] = ImVec4(0.15f, 0.14f, 0.17f, 1.00f);
	style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_Header] = ImVec4(0.15f, 0.14f, 0.17f, 1.00f);
	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);

	style->Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.36f, 0.35f, 0.37f, 1.00f);


	style->WindowRounding = 0.0f;                                // When viewports are enabled it is preferable to disable WinodwRounding
	style->Colors[ImGuiCol_WindowBg].w = 1.0f;                   // When viewports are enabled it is preferable to disable WindowBg alpha


	ImGuiIO io = ImGui::GetIO();

	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Ruda-Bold.ttf", 10);
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Ruda-Bold.ttf", 12);
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Ruda-Bold.ttf", 14);
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Ruda-Bold.ttf", 18);

	io.FontDefault = io.Fonts->Fonts[1];

}

void ImGuiHelper::DeleteImGui()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiHelper::UpdateStart()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void ImGuiHelper::RenderReady()
{
	ImGui::Render();
}

void ImGuiHelper::Render()
{
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	// Update and Render additional Platform Windows
	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
}

void ImGuiHelper::Validate()
{
	ImGui_ImplDX11_CreateDeviceObjects();
}

void ImGuiHelper::Invalidate()
{
	ImGui_ImplDX11_InvalidateDeviceObjects();
}
