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
		D3D11Model();
		~D3D11Model();

		virtual void Render();

	protected:
		virtual void InitMesh(std::string const & mesh_file);
		virtual void InitTexture(std::string const & texture_file);

	private:
		ID3D11BufferPtr             vertex_buffer_;
		ID3D11BufferPtr             index_buffer_;
		ID3D11ShaderResourceViewPtr texture_;
	};
}

#endif // Forge_D3D11Model_hpp__