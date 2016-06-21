/********************************************************************
	created  :	2016/6/18
	author   :	Sivan
	source   :  模型
*********************************************************************/

#ifndef Forge_Model_hpp__
#define Forge_Model_hpp__

#pragma once

#include <Math/Math.hpp>
#include <vector>

namespace Forge
{
	enum RenderMode
	{
		RM_Line,
		RM_FillColor,
		RM_Texture
	};

	class Model
	{
	public:
		struct VertexData
		{
			float4 position;
			float2 texture;
			Color  color;
			float  rhw;
		};
		struct IndexData
		{
			uint32_t a;
			uint32_t b;
			uint32_t c;
		};

		Model();
		~Model();

		void Initialize(std::string const & mesh_file, std::string const & texture_file, RenderDevice * device);
		void SetRenderMode(RenderMode mode);
		void Render();

	protected:
		void InitMesh(std::string const & mesh_file);
		void InitTexture(std::string const & texture_file);
		void RenderTriangle(float4x4 const & wvp, VertexData & a, VertexData & b, VertexData & c);

		/**
			在规则观察体（CVV）中进行多边形裁剪，不进行透视除法，利用返回值可以判定在哪个分量上超出CVV
		*/
		int  ClipInCVV(float4 const & p);

		/**
			对顶点进行透视除法，和转化为屏幕坐标
		*/
		float Homogenize(float4 & p);

		void MakeVertexRHW(VertexData & vd);

		void DrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);
		void DrawPixel(uint32_t x, uint32_t y, uint32_t color);

	private:
		RenderMode              render_mode_;
		std::vector<VertexData> mesh_vb_;
		std::vector<IndexData>  mesh_ib_;
		uint32_t                texture_buffer_[256][256];
		RenderDevice*           device_;
		uint32_t                line_color_;
		uint32_t                count_;
	};
}

#endif // Forge_Model_hpp__