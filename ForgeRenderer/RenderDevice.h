/********************************************************************
	created  :	2016/6/18
	author   :	Sivan
	source   :  渲染设备
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
		RenderDevice();
		~RenderDevice();

		bool Initialize(HWND hWnd, uint32_t width, uint32_t height);
		void ShutDown();
		bool FrameMove();

		void BeginFrame();
		void EndFrame();

		void ClearFrameBuffer(Color const & clr, float depth = 1.0f);

		void UpdateTexture(void* buffer, uint32_t pitch, uint32_t width, uint32_t height);
		float4x4 const & WorldViewProjMatrix();

		uint32_t GetWidth()  const;
		uint32_t GetHeight() const;

		void SetFrameBufferData(uint32_t x, uint32_t y, uint32_t data);

	protected:
		bool InitDevice(HWND hWnd, uint32_t width, uint32_t height);
		void Render();

	private:
		HWND				hwnd_;
		HDC					hdc_;
		uint32_t			width_;
		uint32_t			height_;
		HBITMAP				bitmap_;
		HBITMAP				bitmap_old_;
		std::vector<char>   buffer_pool_;// 缓冲区
		unsigned char*      dib_buffer_; // 位图数据指针
		uint32_t**          frame_buffer_;
		float**             depth_buffer_;
		uint32_t**          texture_buffer_;
		Color               background_color_;
		float               depth_clear_value_;
		uint32_t            texture_width_;
		uint32_t            texture_height_;
		float4x4            world_mat_;
		mutable float4x4    wvp_mat_;

		ModelPtr            model_;
		CameraPtr           camera_;
		KeyboardInputPtr    input_;
	};
}

#endif // Forge_RenderDevice_hpp__