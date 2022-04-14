#pragma once
#include "System\Source\Interface\ISystem.h"


class GraphicSystem : public ISystem
{
	friend class SystemManager;

private:
	GraphicSystem();
	~GraphicSystem() {}

	GraphicSystem(const GraphicSystem& other) {}

	inline void SetInitilaizeValue(Color background_color = Color(0xFF333344), bool vertical_sync = false)
	{
		backgroundColor = background_color;
		useVerticalSync = vertical_sync;
	}

public:
	//	* Graphic System Initialize
	void Initialize(const MainWindowDescription& main_window_description) override;

	//	* Graphic System Release
	void Release() override;


	//	* Graphic System Direct Process Function
	LRESULT DirectProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

	//	* Set Render Targets
	//	* If you use more than one RenderTargetView, the output data of the PixelShader should also be modified.
	void SetRenderTargets(ID3D11RenderTargetView** rtvs, UINT count, ID3D11DepthStencilView* dsv = NULL);

	//	* Set Main Render Target
	void SetMainRenderTarget();


	//	* Clear
	//	* Main RenderTargetView Clear
	//	* call Before Present And DrawCall
	void Clear();

	//	* Present
	//	* Render All Data
	//	* call After Clear And DrawCall
	void Present();


	//	* Render Target View Clear
	void RenderTargetClear(ID3D11RenderTargetView* rtv, Color clear_color = Color::Black);

	//	* Depth Stencil View Clear
	void DepthStencilClear(ID3D11DepthStencilView* dsv, D3D11_CLEAR_FLAG clear_flag = D3D11_CLEAR_DEPTH, float depthValue = 1.0f, unsigned int stencilValue = 0);
	

	//	* Set Background Color
	inline void SetBackgroundColor(const Color& background_color) { backgroundColor = background_color; }

	//	* Get Background Color
	inline const Color& GetBackgroundColor() { return backgroundColor; }


	//	* Is Using Vertical Synchronization
	inline bool IsUsingVerticalSync() { return useVerticalSync; }

	//	* Swap Chain Resize (And BackBuffers)
	void ResizeSwapChain(IDXGISwapChain*& swapChain, unsigned int width, unsigned int height, ID3D11RenderTargetView** back_rtv = NULL, ID3D11DepthStencilView** back_dsv = NULL, ID3D11Texture2D** back_depth_backBuffer = NULL);



	//	* Get Graphic System's Device (For Create)
	inline ID3D11Device* GetDevice() { return device; }

	//	* Get Graphic System's Device Context (For Render)
	inline ID3D11DeviceContext* GetDeviceContext() { return deviceContext; }

	//	* Get Graphic System's Swap Chain (Window Surface)
	inline IDXGISwapChain* GetMainSwapChain() { return mainSwapChain; }


	//	* Get GPU Memory Size
	inline UINT GetGPUMemorySize() { return gpuMemorySize; }

	//	* Get GPU Info Description Wstring
	inline const wstring& GetGPUDescription() { return gpuDescription; }


private:
	void SetGPUInfo(float width, float height);
	void CreateDeviceAndSwapChain(HWND handle, bool fullScreen, bool vertical_sync);

	void CreateBackBuffer(float width, float height);
	void DeleteBackBuffer();

private:
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;

	IDXGISwapChain* mainSwapChain;

	UINT gpuMemorySize;
	wstring gpuDescription;

	UINT numerator;
	UINT denominator;

	//	* Not Use At Deferred
	//ID3D11Texture2D* depthBackBuffer;	// * Depth Back Buffer Texture

	//	* Main Render Target View
	ID3D11RenderTargetView* mainRenderTargetView;

	//	* Not Use At Deferred
	//	* Main Depth Stencil View
	//ID3D11DepthStencilView* mainDepthStencilView;

	//	* Use Vertical Synchronization
	bool useVerticalSync;

	//	* Background Color
	Color backgroundColor;

	int procIndex;
};