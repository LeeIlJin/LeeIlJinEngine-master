#pragma once

class Application
{
public:

	//	* Create Application
	//	* Create Main Window Instance / InitializeWindow
	//	* Create System Manager Instance / Initialize
	static void CreateApplication(
		HINSTANCE hinstance = NULL, DWORD window_style = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW
		, Color background_color = Color(0xFF333344), LPCWSTR window_name = L"Game"
		, IntPoint window_size = IntPoint(1280, 720), IntPoint window_pos = IntPoint(0, 0)
		, bool full_screen = false, bool vertical_sync = false);


	//	* Run Application
	//	* Main Window Run
	//	* Loop()
	static WPARAM RunApplication();


	//	* Destroy Application
	//	* Destroy Main Window Instance / Release
	//	* Destroy System Manager Instance / Release
	static void DestroyApplication();

	inline static bool IsGameRunning() { return bGameRunning; }

	inline static void UseImGui() { if (IsGameRunning() == true)return; bUseImGui = true; }
	inline static bool IsUseImGui() { return bUseImGui; }

private:
	static bool bGameRunning;

	static bool bUseImGui;
};
