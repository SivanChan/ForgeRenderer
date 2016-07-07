
#include "stdafx.h"
#include "Model.h"
#include <fstream>
#include "RenderDevice.h"

namespace Forge
{
	Model::Model() : render_mode_(RM_WireFrame)
	{
		Color color(1.0f, 0.0f, 0.0f, 1.0f);
		line_color_ = color.RGB_();
	}

	Model::~Model()
	{

	}

	void Model::Initialize(std::string const & mesh_file, std::string const & texture_file, RenderDevice* device)
	{
		// device
		device_ = device;

		// init mesh
		InitMesh(mesh_file);

		// init texture
		InitTexture(texture_file);		
	}

	void Model::SetRenderMode(RenderMode mode)
	{
		render_mode_ = mode;
	}

	void Model::InitMesh(std::string const & mesh_file)
	{
		std::ifstream in_file;
		std::string str;
		uint32_t read_flag = 0;

		in_file.open(mesh_file, std::ios::in);
		while (std::getline(in_file,str) && !str.empty())
		{
			if (str == "VB")
			{
				read_flag = 1;
				continue;
			}
			else if (str == "IB")
			{
				read_flag = 2;
				continue;
			}

			if (read_flag == 1)
			{
				VertexData vt;
				float4 color;
				sscanf_s(str.c_str(),"%f,%f,%f,%f,%f,%f,%f,%f,%f",
					&vt.position.x(),&vt.position.y(), &vt.position.z(),
					&vt.texture.x(), &vt.texture.y(),
					&color.x(),&color.y(),&color.z(),&vt.rhw);
				vt.color = Color(color.x(),color.y(),color.z(),1.0f);
				vt.position.w() = 1;
				mesh_vb_.push_back(vt);
			}
			else if (read_flag == 2)
			{
				IndexData it;
				sscanf_s(str.c_str(),"%u,%u,%u",&it.a,&it.b,&it.c);
				mesh_ib_.push_back(it);
			}
		}
		in_file.close();
	}

	void Model::InitTexture(std::string const & texture_file)
	{
	}
}