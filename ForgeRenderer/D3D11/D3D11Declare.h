/********************************************************************
	created:	2016/07/04
	created:	2016/7/4   23:21
	filename: 	D3D11Declare.h
	author:		Sivan
	purpose:	D3D11 ÉùÃ÷
*********************************************************************/

#ifndef Forge_D3D11Declare_hpp__
#define Forge_D3D11Declare_hpp__

#pragma once

#include <dxgi.h>
#include <d3d11.h>
#include <d3dx11tex.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")

namespace Forge
{
	typedef std::shared_ptr<IDXGISwapChain>          IDXGISwapChainPtr;
	typedef std::shared_ptr<ID3D11Device>            ID3D11DevicePtr;
	typedef std::shared_ptr<ID3D11DeviceContext>     ID3D11DeviceContextPtr;
	typedef std::shared_ptr<ID3D11RenderTargetView>  ID3D11RenderTargetViewPtr;
	typedef std::shared_ptr<ID3D11Texture2D>         ID3D11Texture2DPtr;
	typedef std::shared_ptr<ID3D11DepthStencilState> ID3D11DepthStencilStatePtr;
	typedef std::shared_ptr<ID3D11DepthStencilView>  ID3D11DepthStencilViewPtr;
	typedef std::shared_ptr<ID3D11RasterizerState>   ID3D11RasterizerStatePtr;
	typedef std::shared_ptr<ID3D11Buffer>            ID3D11BufferPtr;
	typedef std::shared_ptr<ID3D11ShaderResourceView> ID3D11ShaderResourceViewPtr;
}

#endif // Forge_D3D11Declare_hpp__