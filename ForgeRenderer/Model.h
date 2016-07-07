/********************************************************************
	created  :	2016/6/18
	author   :	Sivan
	source   :  Ä£ÐÍ
*********************************************************************/

#ifndef Forge_Model_hpp__
#define Forge_Model_hpp__

#pragma once

#include <PreDeclare.h>
#include <Math/Math.hpp>
#include <vector>

namespace Forge
{
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
		virtual ~Model();

		virtual void Initialize(std::string const & mesh_file, std::string const & texture_file, RenderDevice* device);
		virtual void SetRenderMode(RenderMode mode);
		virtual void Render() = 0;

	protected:
		virtual void InitMesh(std::string const & mesh_file);
		virtual void InitTexture(std::string const & texture_file);

	protected:
		RenderMode              render_mode_;
		std::vector<VertexData> mesh_vb_;
		std::vector<IndexData>  mesh_ib_;
		RenderDevice*           device_;
		uint32_t                line_color_;
	};
}

#endif // Forge_Model_hpp__