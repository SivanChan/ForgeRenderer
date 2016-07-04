
#include <stdafx.h>
#include <RenderDevice.h>
#include <D3D11/D3D11Model.h>
#include <D3D11/D3D11RenderDevice.h>

namespace Forge
{
	D3D11Model::D3D11Model()
	{

	}

	D3D11Model::~D3D11Model()
	{

	}

	void D3D11Model::Render()
	{
		ID3D11DeviceContextPtr const & context = (static_cast<D3D11RenderDevice*>(device_))->GetD3D11DeviceContext();
		uint32_t stride, offset;
		stride = sizeof(VertexData);
		offset = 0;

		ID3D11Buffer* vertex_buffer = vertex_buffer_.get();
		context->IASetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);
		context->IASetIndexBuffer(index_buffer_.get(), DXGI_FORMAT_R32_UINT, 0);
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	void D3D11Model::InitMesh(std::string const & mesh_file)
	{
		Model::InitMesh(mesh_file);

		D3D11_BUFFER_DESC vertex_buffer_desc, index_buffer_desc;
		D3D11_SUBRESOURCE_DATA vertex_data, index_data;
		ID3D11Buffer* vertex_buffer = NULL, * index_buffer = NULL;
		HRESULT result;

		// create vertex buffer
		vertex_buffer_desc.Usage     = D3D11_USAGE_DEFAULT;
		vertex_buffer_desc.ByteWidth = sizeof(VertexData) * (UINT)mesh_vb_.size();
		vertex_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertex_buffer_desc.CPUAccessFlags = 0;
		vertex_buffer_desc.MiscFlags = 0;
		vertex_buffer_desc.StructureByteStride = 0;

		vertex_data.pSysMem = mesh_vb_.data();
		vertex_data.SysMemPitch = 0;
		vertex_data.SysMemSlicePitch = 0;

		result = (static_cast<D3D11RenderDevice*>(device_))->GetD3D11Device()->CreateBuffer(&vertex_buffer_desc, &vertex_data, &vertex_buffer);
		if (FAILED(result))
			return;
		vertex_buffer_ = MakeCOMPtr(vertex_buffer);

		// create index buffer
		index_buffer_desc.Usage     = D3D11_USAGE_DEFAULT;
		index_buffer_desc.ByteWidth = sizeof(IndexData) * (UINT)mesh_ib_.size();
		index_buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		index_buffer_desc.CPUAccessFlags = 0;
		index_buffer_desc.MiscFlags = 0;
		index_buffer_desc.StructureByteStride = 0;

		index_data.pSysMem = mesh_ib_.data();
		index_data.SysMemPitch = 0;
		index_data.SysMemSlicePitch = 0;

		result = (static_cast<D3D11RenderDevice*>(device_))->GetD3D11Device()->CreateBuffer(&index_buffer_desc, &index_data, &index_buffer);
		if (FAILED(result))
			return;
		index_buffer_ = MakeCOMPtr(index_buffer);

		// create shader
	}

	void D3D11Model::InitTexture(std::string const & texture_file)
	{
		std::wstring texture_file_w;
		ID3D11ShaderResourceView* srv = NULL;
		HRESULT result;
		ID3D11Device* device = NULL;

		StringConvert(texture_file, texture_file_w);
		device = (static_cast<D3D11RenderDevice*>(device_))->GetD3D11Device().get();
		result = D3DX11CreateShaderResourceViewFromFile(device,
			texture_file_w.c_str(), NULL, NULL, &srv,NULL );
		if (FAILED(result))
			return;
		texture_ = MakeCOMPtr(srv);

		// create shader
	}
}