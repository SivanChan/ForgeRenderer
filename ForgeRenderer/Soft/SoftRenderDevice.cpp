
#include <stdafx.h>
#include <Camera.h>
#include <Soft/SoftRenderDevice.h>
#include <Soft/SoftModel.h>

namespace Forge
{
	SoftRenderDevice::SoftRenderDevice() : RenderDevice(), hwnd_(NULL),
		hdc_(NULL),
		bitmap_(NULL),
		bitmap_old_(NULL),
		dib_buffer_(NULL),
		frame_buffer_(NULL),
		depth_buffer_(NULL),
		texture_buffer_(NULL),
		depth_clear_value_(1.0f),
		texture_width_(0),
		texture_height_(0)
	{

	}

	SoftRenderDevice::~SoftRenderDevice()
	{
		ShutDown();
	}

	void SoftRenderDevice::ShutDown()
	{
		if (hdc_ != NULL)
		{
			if (bitmap_old_ != NULL)
			{
				SelectObject(hdc_, bitmap_old_);
				bitmap_old_ = NULL;
			}
			DeleteDC(hdc_);
			hdc_ = NULL;
		}
		if (bitmap_ != NULL)
		{
			DeleteObject(bitmap_);
			bitmap_ = NULL;
		}
	}

	bool SoftRenderDevice::Refresh()
	{
		BeginFrame();
		Render();
		EndFrame();
		return true;
	}

	std::wstring const & SoftRenderDevice::Name() const
	{
		static std::wstring const name(L"软渲染");
		return name;
	}

	void SoftRenderDevice::BeginFrame()
	{
		ClearFrameBuffer(background_color_, depth_clear_value_);
	}

	void SoftRenderDevice::EndFrame()
	{
		// present
		HDC hDC = GetDC(hwnd_);
		BitBlt(hDC, 0, 0, width_, height_, hdc_, 0, 0, SRCCOPY);
		ReleaseDC(hwnd_, hDC);
	}

	void SoftRenderDevice::ClearFrameBuffer(Color const & clr, float depth /*= 1.0f*/)
	{
		// clear frame buffer
		uint32_t color_value;
		uint8_t r, g, b, a;
		clr.RGBA(r, g, b, a);
		color_value = (r << 16) | (g << 8) | b;
		for (uint32_t i = 0; i < height_; ++i)
		{
			uint32_t* row = frame_buffer_[i];
			for (uint32_t j = 0; j < width_; ++j)
				row[j] = color_value;
		}

		// clear depth buffer
		for (uint32_t i = 0; i < height_; ++i)
		{
			float* row = depth_buffer_[i];
			for (uint32_t j = 0; j < width_; ++j)
				row[j] = depth;
		}
	}

	Forge::ModelPtr SoftRenderDevice::CreateModel()
	{
		return std::make_shared<SoftModel>();
	}

	void SoftRenderDevice::UpdateTexture(void* buffer, uint32_t pitch, uint32_t width, uint32_t height)
	{
		char* ptr = (char*)buffer;
		for (uint32_t i = 0; i < height; ptr += pitch, ++i)
		{
			texture_buffer_[i] = (uint32_t*)ptr;
		}
		texture_width_ = width;
		texture_height_ = height;
	}

	void SoftRenderDevice::SetFrameBufferData(uint32_t x, uint32_t y, uint32_t data)
	{
		frame_buffer_[x][y] = data;
	}

	bool SoftRenderDevice::InitDevice(HWND hWnd, uint32_t width, uint32_t height)
	{
		hwnd_ = hWnd;
		width_ = width;
		height_ = height;

		HDC hDC = GetDC(hwnd_);
		hdc_ = CreateCompatibleDC(hDC);
		ReleaseDC(hwnd_, hDC);

		LONG w, h; w = width; h = height;
		BITMAPINFO bi = { { sizeof(BITMAPINFOHEADER), w, -h, 1, 32, BI_RGB, (DWORD)w * h * 4, 0, 0, 0, 0 } };
		LPVOID void_ptr;
		bitmap_ = CreateDIBSection(hdc_, &bi, DIB_RGB_COLORS, &void_ptr, 0, 0);
		if (bitmap_ == NULL)
			return false;
		bitmap_old_ = (HBITMAP)SelectObject(hdc_, bitmap_);
		dib_buffer_ = (unsigned char*)void_ptr;

		// create frame buffer and depth buffer
		uint32_t total_size = sizeof(void*) * (height_ * 2 + 1024) + width_ * height_ * 8 + 64;
		buffer_pool_.resize(total_size);
		char* ptr = &buffer_pool_[0];

		// 行指针存储区
		frame_buffer_ = (uint32_t**)ptr;                                    // height个
		depth_buffer_ = (float**)(ptr + sizeof(void*) * height_);           // height个
		texture_buffer_ = (uint32_t**)(ptr + sizeof(void*) * height * 2);     // 1024个

																			  // 数据存储区
		char* frame_data, *depth_data;
		ptr += sizeof(void*) * height_ * 2 + sizeof(void*) * 1024;
		frame_data = (char*)ptr;
		depth_data = (char*)ptr + width_ * height_ * 4;

		if (dib_buffer_ != NULL)
			frame_data = (char*)dib_buffer_;
		// 填充行指针
		for (uint32_t i = 0; i < height_; ++i)
		{
			frame_buffer_[i] = (uint32_t*)(frame_data + width_ * 4 * i);
			depth_buffer_[i] = (float*)(depth_data + width_ * 4 * i);
		}
		ptr += width_ * height_ * 8;
		texture_buffer_[0] = (uint32_t*)ptr;
		texture_buffer_[1] = (uint32_t*)(ptr + 16);
		memset(texture_buffer_[0], 0, 64);

		return true;
	}

	void SoftRenderDevice::Render()
	{
		model_->Render();
	}
}
