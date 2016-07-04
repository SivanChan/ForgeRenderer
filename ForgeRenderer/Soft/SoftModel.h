/********************************************************************
	created:	2016/07/03
	created:	2016/7/3   15:11
	filename: 	SoftModel.h
	author:		Sivan
	purpose:	软渲染模型
*********************************************************************/

#ifndef Forge_SoftModel_hpp__
#define Forge_SoftModel_hpp__

#pragma once

#include <Model.h>
#include <RenderDevice.h>

namespace Forge
{
	class SoftModel : public Model
	{
	public:
		SoftModel();
		~SoftModel();

		virtual void Initialize(std::string const & mesh_file, std::string const & texture_file, RenderDevice* device);
		virtual void SetRenderMode(RenderMode mode);
		virtual void Render();

	protected:
		virtual void InitTexture(std::string const & texture_file);

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
		uint32_t                texture_buffer_[256][256];			
	};
	typedef std::shared_ptr<SoftModel> SoftModelPtr;
}

#endif // Forge_SoftModel_hpp__