#pragma once

///////////////////////////////////////////////////////////////////////////////

#include <Windows.h>
#include <assert.h>
#include <math.h>
#include <string>

#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <functional>
#include <thread>
#include <iterator>

#include <memory>


#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h> 
#include <crtdbg.h> 

#define SET_DEBUG_MODE _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)
#define CHECK_MEMORY_NEW_POSITION(addr) _CrtSetBreakAlloc(addr)

#endif


using namespace std;

///////////////////////////////////////////////////////////////////////////////

//Direct3D
#include <dxgi1_2.h>
#include <d3dcommon.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <d3dx11effect.h>

//DirectXTex
#include <DirectXTex.h>

///////////////////////////////////////////////////////////////////////////////
//	In System

#include "ImGui/MyImGui.h"

#include "Math/MyMath.h"
#include "Utility/MyUtility.h"
#include "Memory\MyMemory.h"

#pragma comment(lib, "Math.lib")
#pragma comment(lib, "Utility.lib")
#pragma comment(lib, "Memory.lib")

#include "System\MyMacro.h"
#include "System\MyFunction.h"


///////////////////////////////////////////////////////////////////////////////

//	System Window
#include "System\Source\Window\Public\IWindow.h"
#include "System\Source\Window\Public\IWindowFactory.h"
#include "System\Source\Window\Public\IWindowManager.h"
#include "System\Source\Window\Public\IWindowSystem.h"

//	System Include
//#include "System\Source\Systems\InputSystem.h"
//#include "System\Source\Systems\TimeSystem.h"
//#include "System\Source\Systems\GraphicSystem.h"

//	System Manager
//#include "System\Source\SystemManager.h"


///////////////////////////////////////////////////////////////////////////////
#include "System\Source\System.h"


//	Application
//#include "System\Source\Application.h"

