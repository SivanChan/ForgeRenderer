/********************************************************************
	created:	2016/07/03
	created:	2016/7/3   15:19
	filename: 	D3D11Model.h
	author:		Sivan
	purpose:	D3D11Ä£ÐÍ
*********************************************************************/

#ifndef Forge_D3D11Model_hpp__
#define Forge_D3D11Model_hpp__

#pragma once

#include <Model.h>
#include <D3D11/D3D11Declare.h>

namespace Forge
{
	class D3D11Model : public Model
	{
	public:
		struct ConstBufferType
		{
			float4x4 wvp;
			float4   flag;
		};

	public:
		D3D11Model();
		~D3D11Model();

		virtual void Initialize(std::string const & mesh_file, std::string const & texture_file, RenderDevice* device);
		virtual void Render();

	protected:
		virtual void InitMesh(std::string const & mesh_file);
		virtual void InitTexture(std::string const & texture_file);
		void InitShader();
		void RenderShader();
		void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	private:
		ID3D11BufferPtr             vertex_buffer_;
		ID3D11BufferPtr             index_buffer_;
		ID3D11ShaderResourceViewPtr texture_;
		ID3D11VertexShaderPtr       vertex_shader_;
		ID3D11PixelShaderPtr        pixel_shader_;
		ID3D11InputLayoutPtr        input_layout_;
		ID3D11BufferPtr             const_buffer_;
		ID3D11SamplerStatePtr       sampler_state_;
	};
}

#endif // Forge_D3D11Model_hpp__