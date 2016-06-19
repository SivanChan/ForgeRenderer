
#include "stdafx.h"
#include "RenderDevice.h"
#include "Camera.h"
#include "Model.h"
#include "KeyboardInput.h"

namespace Forge
{
	RenderDevice::RenderDevice() : hwnd_(NULL), 
		hdc_(NULL), 
		bitmap_(NULL), 
		bitmap_old_(NULL), 
		dib_buffer_(NULL), 
		width_(0), 
		height_(0),
		frame_buffer_(NULL),
		depth_buffer_(NULL),
		texture_buffer_(NULL),
		background_color_(10 / 255.0f, 59 / 255.0f, 118 / 255.0f, 1.0f),
		depth_clear_value_(1.0f),
		texture_width_(0),
		texture_height_(0)
	{

	}

	RenderDevice::~RenderDevice()
	{
		ShutDown();
	}

	bool RenderDevice::Initialize(HWND hWnd, uint32_t width, uint32_t height)
	{
		if (!InitDevice(hWnd,width,height))
			return false;

		// world matrix
		world_mat_ = Math::to_matrix(Math::rotation_axis(float3(-1, -0.5, 1), 1.0f));

		// camera
		camera_ = std::make_shared<Camera>();
		camera_->SetViewParams( float3(3.0f, 0.0f, 0.0f), float3(0.0f, 0.0f, 0.0f), float3(0.0f, 0.0f, 1.0f) );
		camera_->SetProjParams( FORGE_PIdiv2, float(width_) / float(height_), 1.0f, 500.0f );

		// model
		model_ = std::make_shared<Model>();
		model_->Initialize("cube.txt", "tex.bmp", this);

		// input
		input_ = std::make_shared<KeyboardInput>();

		return true;
	}

	void RenderDevice::ShutDown()
	{
		if (hdc_ != NULL)
		{
			if (bitmap_old_ != NULL)
			{
				SelectObject(hdc_,bitmap_old_);
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

	bool RenderDevice::FrameMove()
	{
		BeginFrame();
		Render();
		EndFrame();
		return true;
	}

	void RenderDevice::BeginFrame()
	{
		ClearFrameBuffer( background_color_, depth_clear_value_);
	}

	void RenderDevice::EndFrame()
	{
		// present
		HDC hDC = GetDC(hwnd_);
		BitBlt(hDC, 0, 0, width_, height_, hdc_, 0, 0, SRCCOPY);
		ReleaseDC(hwnd_, hDC);
	}

	void RenderDevice::ClearFrameBuffer(Color const & clr, float depth /*= 1.0f*/)
	{
		// clear frame buffer
		uint32_t color_value;
		uint8_t r, g, b, a;
		clr.RGBA(r,g,b,a);
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

	void RenderDevice::UpdateTexture(void* buffer, uint32_t pitch, uint32_t width, uint32_t height)
	{
		char* ptr = (char*)buffer;
		for (uint32_t i = 0; i < height; ptr += pitch, ++i)
		{
			texture_buffer_[i] = (uint32_t*)ptr;
		}
		texture_width_  = width;
		texture_height_ = height;
	}

	Forge::float4x4 const & RenderDevice::WorldViewProjMatrix()
	{
		wvp_mat_ = world_mat_ * camera_->ViewProjMatrix();
		return wvp_mat_;
	}

	uint32_t RenderDevice::GetWidth() const
	{
		return width_;
	}

	uint32_t RenderDevice::GetHeight() const
	{
		return height_;
	}

	bool RenderDevice::InitDevice(HWND hWnd, uint32_t width, uint32_t height)
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

	void RenderDevice::Render()
	{
		model_->Render();
	}
}