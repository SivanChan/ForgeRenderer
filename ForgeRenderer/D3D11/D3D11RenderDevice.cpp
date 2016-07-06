
#include <stdafx.h>
#include <D3D11/D3D11RenderDevice.h>
#include <D3D11/D3D11Model.h>

namespace Forge
{
	D3D11RenderDevice::D3D11RenderDevice() : RenderDevice()
	{

	}

	D3D11RenderDevice::~D3D11RenderDevice()
	{

	}

	bool D3D11RenderDevice::InitDevice(HWND hWnd, uint32_t width, uint32_t height)
	{
		RenderDevice::InitDevice(hWnd, width, height);

		HRESULT result;
		DXGI_SWAP_CHAIN_DESC swap_chain_desc;
		D3D_FEATURE_LEVEL feature_level;
		IDXGISwapChain* swap_chain = NULL;
		ID3D11Device* d3d_device = NULL;
		ID3D11DeviceContext* d3d_context = NULL;
		ID3D11Texture2D* back_buffer = NULL;
		ID3D11RenderTargetView* rtv = NULL;
		D3D11_TEXTURE2D_DESC depth_buffer;
		ID3D11Texture2D* depth_stencil_buffer = NULL;
		D3D11_DEPTH_STENCIL_DESC depth_stencil_desc;
		ID3D11DepthStencilState* depth_stencil_state = NULL;
		D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc;
		ID3D11DepthStencilView* depth_stencil_view = NULL;
		D3D11_RASTERIZER_DESC rasterizer_desc;
		ID3D11RasterizerState* rasterizer_state = NULL;
		D3D11_VIEWPORT viewport;

		ZeroMemory(&swap_chain_desc, sizeof(swap_chain_desc));
		swap_chain_desc.BufferCount = 1;
		swap_chain_desc.BufferDesc.Width = width_;
		swap_chain_desc.BufferDesc.Height = height_;
		swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swap_chain_desc.BufferDesc.RefreshRate.Numerator = 0;
		swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
		swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swap_chain_desc.OutputWindow = hwnd_;
		swap_chain_desc.SampleDesc.Count = 1;
		swap_chain_desc.SampleDesc.Quality = 0;
		swap_chain_desc.Windowed = true;
		swap_chain_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swap_chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swap_chain_desc.Flags = 0;
		
		feature_level = D3D_FEATURE_LEVEL_11_0;
		
		result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &feature_level, 1, 
			D3D11_SDK_VERSION, &swap_chain_desc, &swap_chain,
			&d3d_device, NULL, &d3d_context);
		if (FAILED(result))
			return false;

		swap_chain_  = MakeCOMPtr(swap_chain);
		d3d_device_  = MakeCOMPtr(d3d_device);
		d3d_context_ = MakeCOMPtr(d3d_context);

		// back buffer
		result = swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&back_buffer);
		if (FAILED(result))
			return false;
		result = d3d_device_->CreateRenderTargetView(back_buffer, NULL, &rtv);
		if (FAILED(result))
			return false;
		rtv_ = MakeCOMPtr(rtv);
		if (back_buffer != NULL)
		{
			back_buffer->Release();
			back_buffer = NULL;
		}

		// depth stencil
		ZeroMemory(&depth_buffer, sizeof(depth_buffer));
		depth_buffer.Width = width_;
		depth_buffer.Height = height_;
		depth_buffer.MipLevels = 1;
		depth_buffer.ArraySize = 1;
		depth_buffer.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depth_buffer.SampleDesc.Count = 1;
		depth_buffer.SampleDesc.Quality = 0;
		depth_buffer.Usage = D3D11_USAGE_DEFAULT;
		depth_buffer.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depth_buffer.CPUAccessFlags = 0;
		depth_buffer.MiscFlags = 0;

		result = d3d_device_->CreateTexture2D(&depth_buffer, NULL, &depth_stencil_buffer);
		if (FAILED(result))
			return false;
		depth_stencil_buffer_ = MakeCOMPtr(depth_stencil_buffer);

		ZeroMemory(&depth_stencil_desc, sizeof(depth_stencil_desc));
		depth_stencil_desc.DepthEnable = true;
		depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depth_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS;
		depth_stencil_desc.StencilEnable = true;
		depth_stencil_desc.StencilReadMask = 0xFF;
		depth_stencil_desc.StencilWriteMask = 0xFF;
		depth_stencil_desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depth_stencil_desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		depth_stencil_desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depth_stencil_desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		depth_stencil_desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depth_stencil_desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		depth_stencil_desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depth_stencil_desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		result = d3d_device_->CreateDepthStencilState(&depth_stencil_desc, &depth_stencil_state);
		if (FAILED(result))
			return false;
		depth_stencil_state_ = MakeCOMPtr(depth_stencil_state);
		if (FAILED(result))
			return false;

		ZeroMemory(&depth_stencil_view_desc, sizeof(depth_stencil_view_desc));
		depth_stencil_view_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depth_stencil_view_desc.Texture2D.MipSlice = 0;

		result = d3d_device_->CreateDepthStencilView(depth_stencil_buffer_.get(), &depth_stencil_view_desc, &depth_stencil_view);
		if (FAILED(result))
			return false;
		depth_stencil_view_ = MakeCOMPtr(depth_stencil_view);

		d3d_context_->OMSetRenderTargets(1, &rtv, depth_stencil_view_.get());

		// rasterizer
		ZeroMemory(&rasterizer_desc, sizeof(rasterizer_desc));
		rasterizer_desc.AntialiasedLineEnable = true;
		rasterizer_desc.CullMode = D3D11_CULL_NONE;
		rasterizer_desc.DepthBias = 0;
		rasterizer_desc.DepthBiasClamp = 0.0f;
		rasterizer_desc.DepthClipEnable = true;
		rasterizer_desc.FillMode = D3D11_FILL_SOLID;
		rasterizer_desc.FrontCounterClockwise = false;
		rasterizer_desc.MultisampleEnable = false;
		rasterizer_desc.ScissorEnable = false;
		rasterizer_desc.SlopeScaledDepthBias = 0.0f;

		result = d3d_device_->CreateRasterizerState(&rasterizer_desc, &rasterizer_state);
		if (FAILED(result))
			return false;
		rasterizer_state_ = MakeCOMPtr(rasterizer_state);
		d3d_context_->RSSetState(rasterizer_state);

		// viewport
		viewport.Width = (float)width_;
		viewport.Height = (float)height_;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		d3d_context_->RSSetViewports(1, &viewport);

		return true;
	}

	void D3D11RenderDevice::ShutDown()
	{
		rasterizer_state_.reset();
		depth_stencil_view_.reset();
		depth_stencil_state_.reset();
		depth_stencil_buffer_.reset();
		rtv_.reset();
		d3d_context_.reset();
		d3d_device_.reset();
		swap_chain_.reset();
	}

	bool D3D11RenderDevice::Refresh()
	{
		BeginFrame();
		Render();
		EndFrame();
		return false;
	}

	std::wstring const & D3D11RenderDevice::Name() const
	{
		static std::wstring const name(L"D3D11");
		return name;
	}

	void D3D11RenderDevice::BeginFrame()
	{
		ClearFrameBuffer(background_color_, 1.0f);
	}

	void D3D11RenderDevice::Render()
	{
		model_->Render();
	}

	void D3D11RenderDevice::EndFrame()
	{
		swap_chain_->Present(0, 0);
	}

	void D3D11RenderDevice::ClearFrameBuffer(Color const & clr, float depth /*= 1.0f*/)
	{
		float color[4];
		color[0] = clr.r();
		color[1] = clr.g();
		color[2] = clr.b();
		color[3] = clr.a();

		d3d_context_->ClearRenderTargetView(rtv_.get(), color);
		d3d_context_->ClearDepthStencilView(depth_stencil_view_.get(), D3D11_CLEAR_DEPTH, depth, 0);
	}

	Forge::ModelPtr D3D11RenderDevice::CreateModel()
	{
		return std::make_shared<D3D11Model>();
	}

	Forge::ID3D11DevicePtr const & D3D11RenderDevice::GetD3D11Device() const
	{
		return d3d_device_;
	}

	Forge::ID3D11DeviceContextPtr const & D3D11RenderDevice::GetD3D11DeviceContext() const
	{
		return d3d_context_;
	}
}