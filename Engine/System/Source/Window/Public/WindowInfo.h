#pragma once

//	* HWND
//	* HINSTANCE
//	* DWORD
//	* memcpy()
#include <windef.h>

//	* Vector2
#include "Math\Source\Vector2.h"

//	* std::wstring
#include <string>


//	* Window's Info Struct
//	! Handle (HWND)					<Window Handle>
//	! HInstance (HINSTANCE)		<Window Handle Instance>
//	! ParentHandle (HWND)		<Parent Window Handle>
//	! Style (DWORD)					<Window Style>
//	! Name (std::wstring)			<Window Name>
//	! DefaultName (std::wstring)	<Window Default Name (ReadOnly)>
//	! Size (Vector2)					<Window Size>
//	! Position (Vector2)				<Window Position(Left Top)>
//	! IsMaximized (bool)				<Window Maximized>
//	! IsMinimized (bool)				<Window Minimized>
//	! IsHavingMouse (bool)				<Window Having A Mouse>
struct WindowInfo
{
public:
	//	Basic
	WindowInfo() noexcept
		: Handle(nullptr), ParentHandle(nullptr), HInstance(nullptr), Style(0), Name(L""), DefaultName(L"")
		, IsMaximized(false), IsMinimized(false), IsHavingMouse(false), IsHiding(false) {}
	
	WindowInfo(const WindowInfo& other) noexcept
		: HInstance(other.HInstance), ParentHandle(other.ParentHandle), Style(other.Style)
		, Size(other.Size), Position(other.Position), Name(other.Name), Handle(other.Handle)
		, DefaultName(other.DefaultName), IsMaximized(other.IsMaximized), IsMinimized(other.IsMinimized)
		, IsHavingMouse(other.IsHavingMouse), IsHiding(other.IsHiding)
	{ }



	~WindowInfo() noexcept {}

	bool operator== (const WindowInfo& other) const
	{
		return (Handle == other.Handle);
	}
	const WindowInfo& operator= (const WindowInfo& other) noexcept
	{
		this->HInstance = other.HInstance;
		this->ParentHandle = other.ParentHandle;
		this->Style = other.Style;
		this->Size = other.Size;
		this->Position = other.Position;
		this->Name = other.Name;
		this->Handle = other.Handle;
		this->DefaultName = other.DefaultName;
		this->IsMaximized = other.IsMaximized;
		this->IsMinimized = other.IsMinimized;
		this->IsHavingMouse = other.IsHavingMouse;
		this->IsHiding = other.IsHiding;

		return *this;
	}


public:
	HINSTANCE HInstance;
	HWND ParentHandle;
	DWORD Style;

	Vector2 Size;
	Vector2 Position;

	std::wstring Name;


	//

	HWND Handle;
	std::wstring DefaultName;

	bool IsMaximized;
	bool IsMinimized;
	bool IsHavingMouse;

	bool IsHiding;

};
