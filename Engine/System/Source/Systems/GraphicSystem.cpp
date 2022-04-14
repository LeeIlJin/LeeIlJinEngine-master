#include "MySystem.h"

#include "GraphicSystem.h"


//	ImGui Function Call
//	ImGuiHelper :: Invalidate
//	ImGuiHelper :: Validate
//	ImGuiHelper :: Proc


//
GraphicSystem::GraphicSystem()
	: numerator(0), denominator(1), useVerticalSync(false), backgroundColor(0xFF333344)
	, procIndex(-1)
	, device(NULL), deviceContext(NULL), mainSwapChain(NULL), mainRenderTargetView(NULL)
{}
//


void GraphicSystem::Initialize(const MainWindowDescription& main_window_description)
{
	SetGPUInfo(main_window_description.Size.x, main_window_description.Size.y);

	CreateDeviceAndSwapChain(main_window_description.Handle, main_window_description.Fullscreen, useVerticalSync);
	CreateBackBuffer(main_window_description.Size.x, main_window_description.Size.y);

	//	+ Add Process Function To Main Window Process List
	procIndex = MainWindow::AddProc(BIND_FUNCTION_4(GraphicSystem, DirectProc, this));
}

void GraphicSystem::Release()
{
	//	- Erase Process Function From Main Window Process List
	if (procIndex >= 0)
		MainWindow::EraseProc(procIndex);

	DeleteBackBuffer();

	if (mainSwapChain != NULL)
		mainSwapChain->SetFullscreenState(false, NULL);

	SAFE_RELEASE(deviceContext);
	SAFE_RELEASE(device);
	SAFE_RELEASE(mainSwapChain);
}

EXTERN_IMGUI_WND_PROC_HANDLER;
LRESULT GraphicSystem::DirectProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (Application::IsUseImGui() == true)
		IMGUI_WND_PROC_HANDLER(handle, message, wParam, lParam);

	if (message == WM_SIZE)
	{
		unsigned int sx = (unsigned int)LOWORD(lParam);
		unsigned int sy = (unsigned int)HIWORD(lParam);

		//	ImGui Function !
		if (Application::IsUseImGui() == true)
			ImGuiHelper::Invalidate();

		//	* Resize
		ResizeSwapChain(mainSwapChain, sx, sy, &mainRenderTargetView);

		//	ImGui Function !
		if (Application::IsUseImGui() == true)
			ImGuiHelper::Validate();

		return 0;
	}

	return 0;
}

void GraphicSystem::SetRenderTargets(ID3D11RenderTargetView ** rtvs, UINT count, ID3D11DepthStencilView * dsv)
{
	deviceContext->OMSetRenderTargets(count, rtvs, dsv);
}

void GraphicSystem::SetMainRenderTarget()
{
	deviceContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
}

void GraphicSystem::Clear()
{
	deviceContext->ClearRenderTargetView(mainRenderTargetView, backgroundColor.ToD3DXCOLOR());
}

void GraphicSystem::Present()
{
	mainSwapChain->Present(useVerticalSync == true ? 1 : 0, 0);
}

void GraphicSystem::RenderTargetClear(ID3D11RenderTargetView * rtv, Color clear_color)
{
	deviceContext->ClearRenderTargetView(rtv, clear_color.ToD3DXCOLOR());
}

void GraphicSystem::DepthStencilClear(ID3D11DepthStencilView * dsv, D3D11_CLEAR_FLAG clear_flag, float depthValue, unsigned int stencilValue)
{
	deviceContext->ClearDepthStencilView(dsv, clear_flag, depthValue, stencilValue);
}

void GraphicSystem::ResizeSwapChain(IDXGISwapChain *& swapChain, unsigned int width, unsigned int height, ID3D11RenderTargetView ** rtv, ID3D11DepthStencilView ** dsv, ID3D11Texture2D ** ds_backBuffer)
{
	if (width < 1 || height < 1)
		return;

	if (rtv != NULL)
		SAFE_RELEASE(*rtv);
	if (dsv != NULL)
		SAFE_RELEASE(*dsv);
	if (ds_backBuffer != NULL)
		SAFE_RELEASE(*ds_backBuffer);

	HR(swapChain->ResizeBuffers(0, (UINT)width, (UINT)height, DXGI_FORMAT_UNKNOWN, 0));

	if (rtv != NULL)
	{
		ID3D11Texture2D* backbufferPointer;
		HR(swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **)&backbufferPointer));

		HR(device->CreateRenderTargetView(backbufferPointer, NULL, rtv));

		SAFE_RELEASE(backbufferPointer);
	}
	if (dsv != NULL)
	{
		ID3D11Texture2D* temp;

		//	Create Texture - DSV ¿ë
		{
			D3D11_TEXTURE2D_DESC desc = { 0 };
			desc.Width = (UINT)width;
			desc.Height = (UINT)height;
			desc.MipLevels = 1;
			desc.ArraySize = 1;
			desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			desc.SampleDesc.Count = 1;
			desc.SampleDesc.Quality = 0;
			desc.Usage = D3D11_USAGE_IMMUTABLE;
			desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			desc.CPUAccessFlags = 0;
			desc.MiscFlags = 0;

			HR(device->CreateTexture2D(&desc, NULL, &temp));
		}

		//	Create DSV (Depth Stencil View)
		{
			D3D11_DEPTH_STENCIL_VIEW_DESC desc;
			ZeroMemory(&desc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
			desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			desc.Texture2D.MipSlice = 0;

			HR(device->CreateDepthStencilView(temp, &desc, dsv));
		}

		if (ds_backBuffer != NULL)
		{
			*ds_backBuffer = temp;
		}
		else
		{
			temp->Release();
		}

		temp = NULL;
	}
}

void GraphicSystem::SetGPUInfo(float width, float height)
{
	IDXGIFactory* factory;
	HR(CreateDXGIFactory(__uuidof(IDXGIFactory), (void **)&factory));

	IDXGIAdapter* adapter;
	HR(factory->EnumAdapters(0, &adapter));

	IDXGIOutput* adapterOutput;
	HR(adapter->EnumOutputs(0, &adapterOutput));

	UINT modeCount;
	HR(adapterOutput->GetDisplayModeList
	(
		DXGI_FORMAT_R8G8B8A8_UNORM
		, DXGI_ENUM_MODES_INTERLACED
		, &modeCount
		, NULL
	));

	DXGI_MODE_DESC* displayModeList = new DXGI_MODE_DESC[modeCount];
	HR(adapterOutput->GetDisplayModeList
	(
		DXGI_FORMAT_R8G8B8A8_UNORM
		, DXGI_ENUM_MODES_INTERLACED
		, &modeCount
		, displayModeList
	));

	for (UINT i = 0; i < modeCount; i++)
	{
		bool isCheck = true;
		isCheck &= displayModeList[i].Width == width;
		isCheck &= displayModeList[i].Height == height;

		if (isCheck == true)
		{
			numerator = displayModeList[i].RefreshRate.Numerator;
			denominator = displayModeList[i].RefreshRate.Denominator;
		}
	}

	DXGI_ADAPTER_DESC adapterDesc;
	HR(adapter->GetDesc(&adapterDesc));

	gpuMemorySize = adapterDesc.DedicatedVideoMemory / 1024 / 1024;
	gpuDescription = adapterDesc.Description;

	SAFE_DELETE_ARRAY(displayModeList);

	SAFE_RELEASE(adapterOutput);
	SAFE_RELEASE(adapter);
	SAFE_RELEASE(factory);
}

void GraphicSystem::CreateDeviceAndSwapChain(HWND handle, bool fullScreen, bool vertical_sync)
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = 0;
	swapChainDesc.BufferDesc.Height = 0;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	if (vertical_sync == true)
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}

	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = handle;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = !fullScreen;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;

	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined(_DEBUG)
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};
	
	HR(D3D11CreateDeviceAndSwapChain
	(
		NULL
		, D3D_DRIVER_TYPE_HARDWARE
		, NULL
		, creationFlags
		, featureLevels
		, 1
		, D3D11_SDK_VERSION
		, &swapChainDesc
		, &mainSwapChain
		, &device
		, NULL
		, &deviceContext
	));
}

void GraphicSystem::CreateBackBuffer(float width, float height)
{

	//	Create Main RTV (Render Target View)
	{
		ID3D11Texture2D* backbufferPointer;
		HR(mainSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **)&backbufferPointer));

		HR(device->CreateRenderTargetView(backbufferPointer, NULL, &mainRenderTargetView));

		SAFE_RELEASE(backbufferPointer);
	}

	//	* Not Use At Deferred
	////	Create Texture - DSV ¿ë (Depth BackBuffer)
	//{
	//	D3D11_TEXTURE2D_DESC desc = { 0 };
	//	desc.Width = (UINT)width;
	//	desc.Height = (UINT)height;
	//	desc.MipLevels = 1;
	//	desc.ArraySize = 1;
	//	desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	//	desc.SampleDesc.Count = 1;
	//	desc.SampleDesc.Quality = 0;
	//	desc.Usage = D3D11_USAGE_IMMUTABLE;
	//	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	//	desc.CPUAccessFlags = 0;
	//	desc.MiscFlags = 0;

	//	HR(device->CreateTexture2D(&desc, NULL, &depthBackBuffer));
	//}

	////	Create Main DSV (Depth Stencil View)
	//{
	//	D3D11_DEPTH_STENCIL_VIEW_DESC desc;
	//	ZeroMemory(&desc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	//	desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	//	desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	//	desc.Texture2D.MipSlice = 0;

	//	HR(device->CreateDepthStencilView(depthBackBuffer, &desc, &mainDepthStencilView));
	//}
}

void GraphicSystem::DeleteBackBuffer()
{
	SAFE_RELEASE(mainRenderTargetView);

	//	* Not Use At Deferred
	//SAFE_RELEASE(depthBackBuffer);
	//SAFE_RELEASE(mainDepthStencilView);
}
