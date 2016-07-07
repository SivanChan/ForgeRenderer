/********************************************************************
	created:	2016/07/03
	created:	2016/7/3   15:18
	filename: 	D3D11RenderDevice.h
	author:		Sivan
	purpose:	D3D11‰÷»æ…Ë±∏
*********************************************************************/

#ifndef Forge_D3D11RenderDevice_hpp__
#define Forge_D3D11RenderDevice_hpp__

#pragma once

#include <RenderDevice.h>
#include <D3D11/D3D11Declare.h>

namespace Forge
{
	class D3D11RenderDevice : public RenderDevice
	{
	public:
		D3D11RenderDevice(RenderMode render_mode);
		~D3D11RenderDevice();

		virtual void ShutDown();
		virtual bool Refresh();
		virtual std::wstring const & Name() const;

		virtual void BeginFrame();
		virtual void Render();
		virtual void EndFrame();

		virtual void ClearFrameBuffer(Color const & clr, float depth = 1.0f);
		virtual ModelPtr CreateModel();
		virtual void SetRenderMode(RenderMode render_mode);

		ID3D11DevicePtr const & GetD3D11Device() const;
		ID3D11DeviceContextPtr const & GetD3D11DeviceContext() const;

	protected:
		virtual bool InitDevice(HWND hWnd, uint32_t width, uint32_t height);

	private:
		IDXGISwapChainPtr          swap_chain_;
		ID3D11DevicePtr            d3d_device_;
		ID3D11DeviceContextPtr     d3d_context_;
		ID3D11RenderTargetViewPtr  rtv_;
		ID3D11Texture2DPtr         depth_stencil_buffer_;
		ID3D11DepthStencilStatePtr depth_stencil_state_;
		ID3D11DepthStencilViewPtr  depth_stencil_view_;
		ID3D11RasterizerStatePtr   rasterizer_state_frame_;
		ID3D11RasterizerStatePtr   rasterizer_state_solid_;
	};
}

#endif // Forge_D3D11RenderDevice_hpp__