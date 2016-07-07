/********************************************************************
	created  :	2016/6/18
	author   :	Sivan
	source   :  ‰÷»æ…Ë±∏
*********************************************************************/

#ifndef Forge_RenderDevice_hpp__
#define Forge_RenderDevice_hpp__

#pragma once

#include "PreDeclare.h"
#include <vector>
#include <Math/Math.hpp>

namespace Forge
{
	class RenderDevice
	{
	public:
		RenderDevice(RenderMode render_mode) : hwnd_(NULL), render_mode_(render_mode), camera_(NULL), background_color_(10 / 255.0f, 59 / 255.0f, 118 / 255.0f, 1.0f) {}
		virtual ~RenderDevice() {}

		virtual bool Initialize(HWND hWnd, uint32_t width, uint32_t height, Camera* camera);
		virtual void ShutDown() = 0;
		virtual bool Refresh() = 0;
		virtual std::wstring const & Name() const = 0;

		// ÷°ª∫≥Â≥ﬂ¥Á
		virtual uint32_t GetWidth()  const;
		virtual uint32_t GetHeight() const;

		// ‰÷»æœ‡πÿ
		virtual void BeginFrame() = 0;
		virtual void Render()     = 0;
		virtual void EndFrame()   = 0;

		// «Â≥˝÷°ª∫≥Â
		virtual void ClearFrameBuffer(Color const & clr, float depth = 1.0f) = 0;

		// model
		virtual ModelPtr CreateModel() = 0;

		// wvp
		virtual float4x4 const & WorldViewProjMatrix();

		// render mode
		virtual void SetRenderMode(RenderMode render_mode);

		// set background color
		void SetBackgroundColor(Color const & color);

	protected:
		virtual bool InitDevice(HWND hWnd, uint32_t width, uint32_t height);
		virtual void InitModel();

	protected:
		HWND                hwnd_;
		RenderMode          render_mode_;
		uint32_t			width_;
		uint32_t			height_;
		float4x4            world_mat_;
		mutable float4x4    wvp_mat_;
		Color               background_color_;
		Camera*             camera_;
		ModelPtr            model_;
	};
}

#endif // Forge_RenderDevice_hpp__