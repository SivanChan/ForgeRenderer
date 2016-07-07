
#include <stdafx.h>
#include <RenderDevice.h>
#include <D3D11/D3D11Model.h>
#include <D3D11/D3D11RenderDevice.h>
#include <fstream>

namespace Forge
{
	D3D11Model::D3D11Model()
	{

	}

	D3D11Model::~D3D11Model()
	{

	}

	void D3D11Model::Initialize(std::string const & mesh_file, std::string const & texture_file, RenderDevice* device)
	{
		Model::Initialize(mesh_file, texture_file, device);
		InitShader();
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
	}

	void D3D11Model::InitShader()
	{
		// create vertex shader
		HRESULT result;
		std::wstring vertex_shader_file(L"./data/vs.hlsl");
		ID3D10Blob* vs_buf = NULL;
		ID3D10Blob* error_msg = NULL;
		ID3D11VertexShader* vs_shader = NULL;
		result = D3DX11CompileFromFile(vertex_shader_file.c_str(), NULL, NULL, "vs_main",
			"vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &vs_buf, &error_msg, NULL);
		if (FAILED(result))
		{
			if (error_msg)
			{
				OutputShaderErrorMessage(error_msg, NULL, (WCHAR*)vertex_shader_file.c_str());
			}
			return;
		}
			
		result = (static_cast<D3D11RenderDevice*>(device_))->GetD3D11Device()->CreateVertexShader(vs_buf->GetBufferPointer(),
			vs_buf->GetBufferSize(), NULL, &vs_shader);
		if (FAILED(result))
			return;
		vertex_shader_ = MakeCOMPtr(vs_shader);

		// create pixel shader
		std::wstring pixel_shader_file(L"./data/ps.hlsl");
		ID3D10Blob* ps_buf = NULL;
		ID3D10Blob* error_msg_ps = NULL;
		ID3D11PixelShader* ps_shader = NULL;
		result = D3DX11CompileFromFile(pixel_shader_file.c_str(), NULL, NULL, "ps_main",
			"ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &ps_buf, &error_msg_ps, NULL);
		if (FAILED(result))
		{
			if (error_msg_ps)
			{
				OutputShaderErrorMessage(error_msg_ps, NULL, (WCHAR*)pixel_shader_file.c_str());
			}
			return;
		}
		result = (static_cast<D3D11RenderDevice*>(device_))->GetD3D11Device()->CreatePixelShader(ps_buf->GetBufferPointer(),
			ps_buf->GetBufferSize(), NULL, &ps_shader);
		if (FAILED(result))
			return;
		pixel_shader_ = MakeCOMPtr(ps_shader);

		// create render layout
		uint32_t num_elements;
		D3D11_INPUT_ELEMENT_DESC input_element[2];
		ID3D11InputLayout* input_layout = NULL;

		input_element[0].SemanticName = "POSITION";
		input_element[0].SemanticIndex = 0;
		input_element[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		input_element[0].InputSlot = 0;
		input_element[0].AlignedByteOffset = 0;
		input_element[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		input_element[0].InstanceDataStepRate = 0;

		input_element[1].SemanticName = "TEXCOORD";
		input_element[1].SemanticIndex = 0;
		input_element[1].Format = DXGI_FORMAT_R32G32_FLOAT;
		input_element[1].InputSlot = 0;
		input_element[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		input_element[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		input_element[1].InstanceDataStepRate = 0;

		num_elements = sizeof(input_element) / sizeof(input_element[0]);
		result = (static_cast<D3D11RenderDevice*>(device_))->GetD3D11Device()->CreateInputLayout(input_element, num_elements,
			vs_buf->GetBufferPointer(), vs_buf->GetBufferSize(), &input_layout);
		if (FAILED(result))
			return;
		input_layout_ = MakeCOMPtr(input_layout);

		if (vs_buf)
		{
			vs_buf->Release();
			vs_buf = NULL;
		}
		if (ps_buf)
		{
			ps_buf->Release();
			ps_buf = NULL;
		}

		// const buffer
		D3D11_BUFFER_DESC matrix_buffer;
		ID3D11Buffer* buf = NULL;
		matrix_buffer.Usage = D3D11_USAGE_DYNAMIC;
		matrix_buffer.ByteWidth = sizeof(ConstBufferType);
		matrix_buffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		matrix_buffer.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		matrix_buffer.MiscFlags = 0;
		matrix_buffer.StructureByteStride = 0;

		result = (static_cast<D3D11RenderDevice*>(device_))->GetD3D11Device()->CreateBuffer(&matrix_buffer, NULL, &buf);
		if (FAILED(result))
			return;
		const_buffer_ = MakeCOMPtr(buf);

		// sampler state
		ID3D11SamplerState* sampler_state = NULL;
		D3D11_SAMPLER_DESC sampler_desc;
		sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.MipLODBias = 0.0f;
		sampler_desc.MaxAnisotropy = 1;
		sampler_desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		sampler_desc.BorderColor[0] = 0;
		sampler_desc.BorderColor[1] = 0;
		sampler_desc.BorderColor[2] = 0;
		sampler_desc.BorderColor[3] = 0;
		sampler_desc.MinLOD = 0;
		sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;

		result = (static_cast<D3D11RenderDevice*>(device_))->GetD3D11Device()->CreateSamplerState(&sampler_desc, &sampler_state);
		if (FAILED(result))
			return;
		sampler_state_ = MakeCOMPtr(sampler_state);
	}

	void D3D11Model::RenderShader()
	{
		ID3D11DeviceContextPtr const & context = (static_cast<D3D11RenderDevice*>(device_))->GetD3D11DeviceContext();
		ID3D11SamplerState* ss = sampler_state_.get();
		float4x4 wvp = device_->WorldViewProjMatrix();
		HRESULT result;
		D3D11_MAPPED_SUBRESOURCE sub_res;
		ID3D11Buffer* buf = const_buffer_.get();
		ID3D11ShaderResourceView* srv = texture_.get();

		result = context->Map(buf, 0, D3D11_MAP_WRITE_DISCARD, 0, &sub_res);
		if (FAILED(result))
			return;
		wvp = Math::transpose(wvp); // HLSL中默认为列主序，需要转置一下
		ConstBufferType* data = static_cast<ConstBufferType*>(sub_res.pData);
		data->wvp = wvp;
		if (render_mode_ == RM_WireFrame)
			data->flag = float4(1.0f, 0.0f, 0.0f, 0.0f);
		else
			data->flag = float4(0.0f, 0.0f, 0.0f, 0.0f);
		context->Unmap(buf, 0);
		context->VSSetConstantBuffers(0, 1, &buf);
		context->PSSetConstantBuffers(0, 1, &buf);
		context->PSSetShaderResources(0, 1, &srv);

		context->IASetInputLayout(input_layout_.get());
		context->VSSetShader(vertex_shader_.get(), NULL, 0);
		context->PSSetShader(pixel_shader_.get(), NULL, 0);
		context->PSSetSamplers(0, 1, &ss);
		context->DrawIndexed((UINT)mesh_ib_.size() * 3, 0, 0);
	}

	void D3D11Model::OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename)
	{
		char* compileErrors;
		unsigned long bufferSize, i;
		std::ofstream fout;

		compileErrors = (char*)(errorMessage->GetBufferPointer());
		bufferSize = (unsigned long)errorMessage->GetBufferSize();

		fout.open("shader-error.txt");
		for (i = 0; i < bufferSize; i++)
		{
			fout << compileErrors[i];
		}
		fout.close();

		errorMessage->Release();
		errorMessage = 0;

		MessageBox(hwnd, L"Error compiling shader.  Check shader-error.txt for message.", shaderFilename, MB_OK);
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

		RenderShader();
	}
}