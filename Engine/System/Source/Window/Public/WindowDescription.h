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


//	* Window's Description Struct
//	! HInstance (HINSTANCE)		<Window Handle Instance>
//	! ParentHandle (HWND)		<Parent Window Handle>
//	! Style (DWORD)					<Window Style>
//	! Name (std::wstring)			<Window Name>
//	! Size (Vector2)					<Window Size>
//	! Position (Vector2)				<Window Position(Left Top)>
//	! FullScreen (bool)				<Is Window FullScreen>
struct WindowDescription
{
public:
	//	Basic
	WindowDescription() noexcept
		: ParentHandle(nullptr), HInstance(nullptr), Style(0), Name(L"") {}

	WindowDescription(const WindowDescription& other) noexcept
	{
		memcpy(this, &other, sizeof(other));
	}

	//	For Set (Initialize Window) Description
	explicit WindowDescription(HINSTANCE h_instance, HWND parent_handle, DWORD style, const std::wstring& name, const Vector2& size, const Vector2& position) noexcept
		: ParentHandle(parent_handle), HInstance(h_instance), Style(style), Name(name), Size(size), Position(position) {}

	~WindowDescription() noexcept {}

	const WindowDescription& operator= (const WindowDescription& other) noexcept
	{
		memcpy(this, &other, sizeof(other));
		return *this;
	}

public:
	HINSTANCE HInstance;
	HWND ParentHandle;
	DWORD Style;

	Vector2 Size;
	Vector2 Position;

	//
	std::wstring Name;

};
