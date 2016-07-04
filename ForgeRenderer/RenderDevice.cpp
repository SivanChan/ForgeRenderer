
#include <stdafx.h>
#include <RenderDevice.h>
#include <Model.h>
#include <Camera.h>

namespace Forge
{
	bool RenderDevice::Initialize(HWND hWnd, uint32_t width, uint32_t height, Camera* camera)
	{
		if (!InitDevice(hWnd, width, height))
			return false;

		camera_ = camera;

		// world matrix
		world_mat_ = Math::to_matrix(Math::rotation_axis(float3(-1, -0.5, 1), 1.0f));

		// init model
		InitModel();

		return true;
	}

	uint32_t RenderDevice::GetWidth() const
	{
		return width_;
	}

	uint32_t RenderDevice::GetHeight() const
	{
		return height_;
	}

	Forge::float4x4 const & RenderDevice::WorldViewProjMatrix()
	{
		wvp_mat_ = world_mat_ * camera_->ViewProjMatrix();
		return wvp_mat_;
	}

	void RenderDevice::SetBackgroundColor(Color const & color)
	{
		background_color_ = color;
	}

	bool RenderDevice::InitDevice(HWND hWnd, uint32_t width, uint32_t height)
	{
		hwnd_ = hWnd;
		width_ = width;
		height_ = height;

		return true;
	}

	void RenderDevice::InitModel()
	{
		model_ = this->CreateModel();
		model_->Initialize("cube.txt", "tex.bmp", this);
	}
}