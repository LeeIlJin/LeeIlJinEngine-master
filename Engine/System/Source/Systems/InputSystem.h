#pragma once

#include "System\Source\Interface\ISystem.h"

#define MAX_INPUT_KEY 255
//

class InputSystem : public ISystem
{
	friend class SystemManager;

	enum KeyState
	{
		KEY_INPUT_NONE = 0, KEY_INPUT_DOWN, KEY_INPUT_UP, KEY_INPUT_PRESS
		, KEY_INPUT_DOUBLE_DOWN, KEY_INPUT_DOUBLE_UP, KEY_INPUT_DOUBLE_PRESS
	};
	struct KeyDoubleInfo
	{
		bool IsDouble = false;
		unsigned char Count = 0;
		unsigned long StartTime = 0;
	};

private:
	InputSystem();
	~InputSystem() {}

	InputSystem(const InputSystem& other) {}

public:
	//	* Input System Initialize
	void Initialize(const MainWindowDescription& main_window_description) override;

	//	* Input System Release
	void Release() override;

	//	* Input System Update
	//	* Mouse Position , Wheel Update
	//	* Key(With Mouse) Down / Press / Up Update
	//	* Key(Width Mouse) DoubleDown / DoublePress / DoubleUp Update
	void Update();


	//	* Input System Input Process Function
	LRESULT InputProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

	//	* Any Key Down
	inline bool AnyKeyDown() const noexcept
	{
		return (keyDownCount > 0);
	}

	// (Keyboard , Mouse( VK_LBUTTON , VK_RBUTTON , VK_MBUTTON ))

	//	* Key Down (Flow: (result)KeyDown )
	inline bool KeyDown(unsigned long key) const noexcept { return keyMap[key] == KEY_INPUT_DOWN; }

	//	* Key Up (Flow: KeyDown -> KeyPress -> (result)KeyUp )
	inline bool KeyUp(unsigned long key) const noexcept { return keyMap[key] == KEY_INPUT_UP; }

	//	* Key Press (Flow: KeyDown -> (result)KeyPress )
	inline bool KeyPress(unsigned long key) const noexcept { return keyMap[key] == KEY_INPUT_PRESS; }

	//	* Key Double Down (Flow: KeyDown -> KeyPress -> KeyUp -> (result)KeyDown )
	inline bool KeyDobleDown(unsigned long key) const noexcept { return keyMap[key] == KEY_INPUT_DOUBLE_DOWN; }

	//	* Key Double Up (Flow: KeyDown -> KeyPress -> KeyUp -> KeyDown -> KeyPress -> (result)KeyUp )
	inline bool KeyDobleUp(unsigned long key) const noexcept { return keyMap[key] == KEY_INPUT_DOUBLE_UP; }

	//	* Key Double Press (Flow: KeyDown -> KeyPress -> KeyUp -> KeyDown -> (result)KeyPress )
	inline bool KeyDoblePress(unsigned long key) const noexcept { return keyMap[key] == KEY_INPUT_DOUBLE_PRESS; }

	//	* Mouse Wheel ( Down(-1) , None(0) , Up(1) )
	inline short MouseWheel() const noexcept { return wheelVal; }

	//	* Mouse Wheel State ( result += MouseWheel() )
	inline short MouseWheelState() const noexcept { return currentWheel; }

	//	* Mouse Wheel Is Up ( MouseWheel() > 0 )
	inline bool MouseWheelUp() const noexcept { return wheelVal > 0; }

	//	* Mouse Wheel Is Down ( MouseWheel() < 0 )
	inline bool MouseWheelDown() const noexcept { return wheelVal < 0; }


	//	* Mouse Cursor In Main Window
	inline bool MouseInMainWindow() const noexcept { return mouseInMainWindow; }


	//	* Get Mouse Position ( Screen Coordinates (LeftTop = {0,0}) )
	//	* ( return _ Mouse In Main Window )
	inline bool MousePositionScreen(Vector2& out_vals) const noexcept
	{
		memcpy(&out_vals, &currentMousePosScreen, sizeof(currentMousePosScreen)); return mouseInMainWindow; 
	}

	//	* Get Mouse Velocity ( Screen Coordinates (LeftTop = {0,0}) ) ( result = current - old )
	//	* ( return _ Mouse In Main Window )
	inline bool MouseVelocityScreen(Vector2& out_vals) const noexcept
	{
		memcpy(&out_vals, &mouseVelocityScreen, sizeof(mouseVelocityScreen)); return mouseInMainWindow;
	}

	//	* Get Mouse Position Ratio ( Screen Coordinates (LeftTop = {0,0}) (RightBottom = {1,1}) )
	//	* ( return _ Mouse In Main Window )
	inline bool MousePositionRatioScreen(Vector2& out_vals) const noexcept
	{
		out_vals = currentMousePosScreen / windowSize;
		return mouseInMainWindow;
	}


	//	* Get Mouse Position ( Device Coordinates (Center = {0,0}) )
	//	* ( return _ Mouse In Main Window )
	inline bool MousePositionDevice(Vector2& out_vals) const noexcept
	{
		memcpy(&out_vals, &currentMousePosDevice, sizeof(currentMousePosDevice)); return mouseInMainWindow;
	}

	//	* Get Mouse Velocity ( Device Coordinates (Center = {0,0}) ) ( result = current - old )
	//	* ( return _ Mouse In Main Window )
	inline bool MouseVelocityDevice(Vector2& out_vals) const noexcept
	{
		memcpy(&out_vals, &mouseVelocityDevice, sizeof(mouseVelocityDevice)); return mouseInMainWindow;
	}

	//	* Get Mouse Position Ratio ( Device Coordinates (Center = {0,0}) (LeftTop = {-0.5,0.5}) )
	//	* This Function Is Same To MousePositionNDC() / 2.0f
	//	* ( return _ Mouse In Main Window )
	inline bool MousePositionRatioDevice(Vector2& out_vals) const noexcept
	{
		out_vals = currentMousePosDevice / windowSize;
		return mouseInMainWindow;
	}

	//	* Get Mouse Position NDC ( Normal Device Coordinates (Center = {0,0}) (LeftTop = {-1,1}) )
	//	* This Function Is Same To MousePositionRatioDevice() * 2.0f
	//	* ( return _ Mouse In Main Window )
	inline bool MousePositionNDC(Vector2& out_vals) const noexcept
	{
		out_vals = (currentMousePosDevice / windowSize) * 2.0f;
		return mouseInMainWindow;
	}


private:
	void SetAllKeyStateNone() noexcept;

private:
	//	Key Input
	unsigned char keyState[MAX_INPUT_KEY];
	unsigned char keyOldState[MAX_INPUT_KEY];
	KeyState keyMap[MAX_INPUT_KEY];
	KeyDoubleInfo keyDoubleInfo[MAX_INPUT_KEY];

	unsigned long keyDownCount;

	unsigned long timeDblClick;

private:
	//	Mouse
	short currentWheel;
	short oldWheel;
	short wheelVal;
	
	Vector2 currentMousePosScreen;
	Vector2 oldMousePosScreen;
	Vector2 mouseVelocityScreen;

	Vector2 currentMousePosDevice;
	Vector2 oldMousePosDevcie;
	Vector2 mouseVelocityDevice;

	bool mouseInMainWindow;

private:
	//	Abount Main Window
	Vector2 windowSize;
	int procIndex;

};
