
#include <stdafx.h>
#include <Soft/SoftModel.h>
#include <Soft/SoftRenderDevice.h>
#include <fstream>

namespace Forge
{
	SoftModel::SoftModel() : Model()
	{

	}

	SoftModel::~SoftModel()
	{

	}

	void SoftModel::Initialize(std::string const & mesh_file, std::string const & texture_file, RenderDevice* device)
	{
		Model::Initialize(mesh_file,texture_file,device);
	}

	void SoftModel::SetRenderMode(RenderMode mode)
	{
		render_mode_ = mode;
	}

	void SoftModel::Render()
	{
		float4x4 const & wvp = device_->WorldViewProjMatrix();
		for (auto it = mesh_ib_.begin(); it != mesh_ib_.end(); ++it)
			RenderTriangle(wvp, mesh_vb_[it->a], mesh_vb_[it->b], mesh_vb_[it->c]);
	}

	void SoftModel::InitTexture(std::string const & texture_file)
	{
		uint32_t width, height;
		uint8_t r, g, b;
		std::ifstream in_file;

		in_file.open(texture_file, std::ios::binary | std::ios::in);
		in_file.seekg(0x0012);
		in_file.read((char*)&width, sizeof(width));
		in_file.seekg(0x0016);
		in_file.read((char*)&height, sizeof(height));

		uint32_t read_pos = 54;
		for (uint32_t i = 0; i < width; ++i)
		{
			for (uint32_t j = 0; j < height; ++j)
			{
				in_file.seekg(read_pos);
				in_file.read((char*)&b, sizeof(b));
				++read_pos;
				in_file.read((char*)&g, sizeof(g));
				++read_pos;
				in_file.read((char*)&r, sizeof(r));
				++read_pos;

				texture_buffer_[i][j] = (r << 16) | (g << 8) | b;
			}
		}
		in_file.close();
		static_cast<SoftRenderDevice*>(device_)->UpdateTexture((void*)texture_buffer_, 256 * 4, 256, 256);
	}

	void SoftModel::RenderTriangle(float4x4 const & wvp, VertexData & a, VertexData & b, VertexData & c)
	{
		float4 p1, p2, p3;

		// wvp变换
		p1 = Math::mul(a.position, wvp);
		p2 = Math::mul(b.position, wvp);
		p3 = Math::mul(c.position, wvp);

		// 裁剪 有一个点在外部，就裁掉
		if (ClipInCVV(p1) > 0)
			return;
		if (ClipInCVV(p2) > 0)
			return;
		if (ClipInCVV(p3) > 0)
			return;

		// 透视除法、转屏幕坐标
		float w1 = Homogenize(p1);
		float w2 = Homogenize(p2);
		float w3 = Homogenize(p3);

		if (render_mode_ == RM_WireFrame)
		{
			DrawLine(static_cast<uint32_t>(p1.x()), static_cast<uint32_t>(p1.y()), static_cast<uint32_t>(p2.x()), static_cast<uint32_t>(p2.y()));
			DrawLine(static_cast<uint32_t>(p2.x()), static_cast<uint32_t>(p2.y()), static_cast<uint32_t>(p3.x()), static_cast<uint32_t>(p3.y()));
			DrawLine(static_cast<uint32_t>(p3.x()), static_cast<uint32_t>(p3.y()), static_cast<uint32_t>(p1.x()), static_cast<uint32_t>(p1.y()));
		}
		else
		{
			VertexData v1, v2, v3;
			v1 = a; v2 = b; v3 = c;

			v1.position = p1; v2.position = p2; v3.position = p3;
			v1.position.w() = w1; v2.position.w() = w2;  v3.position.w() = w3;
			MakeVertexRHW(v1); MakeVertexRHW(v2); MakeVertexRHW(v3);
		}
	}

	int SoftModel::ClipInCVV(float4 const & p)
	{
		int return_val = 0;
		float w = p.w();

		if (p.z() < 0.0f)
			return_val |= 1;
		if (p.z() > w)
			return_val |= 2;
		if (p.x() < -w)
			return_val |= 4;
		if (p.x() > w)
			return_val |= 8;
		if (p.y() < -w)
			return_val |= 16;
		if (p.y() > w)
			return_val |= 32;
		return return_val;
	}

	float SoftModel::Homogenize(float4 & p)
	{
		float rhw = 1.0f / p.w();
		float w = p.w();
		p.x() = (p.x() * rhw + 1.0f) * device_->GetWidth() * 0.5f;
		p.y() = (1.0f - p.y() * rhw) * device_->GetHeight() * 0.5f;
		p.z() = p.z() * rhw;
		p.w() = 1.0f;
		return w;
	}

	void SoftModel::MakeVertexRHW(VertexData & vd)
	{
		float rhw = 1.0f / vd.position.w();
		vd.rhw = rhw;
		vd.texture.x() *= rhw;
		vd.texture.y() *= rhw;
		vd.color.r() *= rhw;
		vd.color.g() *= rhw;
		vd.color.b() *= rhw;
	}

	void SoftModel::DrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2)
	{
		if (x1 == x2 && y1 == y2) // 点重合
		{
			DrawPixel(x1, y1, line_color_);
		}
		else if (x1 == x2) // 垂直
		{
			int step = (y1 <= y2) ? 1 : -1;
			for (uint32_t y = y1; y <= y2; y += step)
				DrawPixel(x1, y, line_color_);
		}
		else if (y1 == y2) // 水平
		{
			int step = (x1 <= x2) ? 1 : -1;
			for (uint32_t x = x1; x <= x2; x += step)
				DrawPixel(x, y1, line_color_);
		}
		else // 斜线
		{
			uint32_t rem = 0;
			uint32_t dx = std::abs(int(x1 - x2)); 
			uint32_t dy = std::abs(int(y1 - y2)); 
			if (dx >= dy)
			{
				if (x2 < x1)
				{
					std::swap(x1, x2);
					std::swap(y1, y2);
				}
				for (uint32_t x = x1, y = y1; x <= x2; ++x)
				{
					DrawPixel(x, y, line_color_);
					rem += dy;
					if (rem >= dx)
					{
						rem -= dx;
						y += (y2 >= y1) ? 1 : -1;
						DrawPixel(x, y, line_color_);
					}
				}
				DrawPixel(x2, y2, line_color_);
			}
			else
			{
				if (y2 < y1)
				{
					std::swap(x1, x2);
					std::swap(y1, y2);
				}
				for (uint32_t x = x1, y = y1; y <= y2; ++y)
				{
					DrawPixel(x, y, line_color_);
					rem += dx;
					if (rem >= dy)
					{
						rem -= dy;
						x += (x2 >= x1) ? 1 : -1;
						DrawPixel(x, y, line_color_);
					}
				}
				DrawPixel(x2, y2, line_color_);
			}
		}
	}

	void SoftModel::DrawPixel(uint32_t x, uint32_t y, uint32_t color)
	{
		static_cast<SoftRenderDevice*>(device_)->SetFrameBufferData(y, x, color);
	}

}