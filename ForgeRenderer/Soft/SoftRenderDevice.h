/********************************************************************
	created:	2016/07/03
	created:	2016/7/3   15:11
	filename: 	SoftRenderDevice.h
	author:		Sivan
	purpose:	软渲染设备
*********************************************************************/

#ifndef Forge_SoftRenderDevice_hpp__
#define Forge_SoftRenderDevice_hpp__

#pragma once

#include <RenderDevice.h>

namespace Forge
{
	class SoftRenderDevice : public RenderDevice
	{
	public:
		SoftRenderDevice(RenderMode render_mode);
		~SoftRenderDevice();

		virtual void ShutDown();
		virtual bool Refresh();
		virtual std::wstring const & Name() const;

		virtual void BeginFrame();
		virtual void Render();
		virtual void EndFrame();

		virtual void ClearFrameBuffer(Color const & clr, float depth = 1.0f);
		virtual ModelPtr CreateModel();

		void UpdateTexture(void* buffer, uint32_t pitch, uint32_t width, uint32_t height);
		void SetFrameBufferData(uint32_t x, uint32_t y, uint32_t data);

	protected:
		virtual bool InitDevice(HWND hWnd, uint32_t width, uint32_t height);		

	private:
		HWND				hwnd_;
		HDC					hdc_;

		HBITMAP				bitmap_;
		HBITMAP				bitmap_old_;
		std::vector<char>   buffer_pool_;// 缓冲区
		unsigned char*      dib_buffer_; // 位图数据指针
		uint32_t**          frame_buffer_;
		float**             depth_buffer_;
		uint32_t**          texture_buffer_;
		
		float               depth_clear_value_;
		uint32_t            texture_width_;
		uint32_t            texture_height_;
	};
}

#endif // Forge_SoftRenderDevice_hpp__