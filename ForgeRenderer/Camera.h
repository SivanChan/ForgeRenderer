/********************************************************************
	created  :	2016/6/19
	author   :	Sivan
	source   :  相机
*********************************************************************/

#ifndef Forge_Camera_hpp__
#define Forge_Camera_hpp__

#pragma once

#include <Math/Math.hpp>

namespace Forge
{
	class Camera
	{
	public:
		Camera();
		~Camera();

		void SetViewParams(float3 const & eye_pos, float3 const & look_at, float3 const & up_vec);
		void SetProjParams(float fov, float aspect, float near_plane, float far_plane);

		float4x4 const & ViewMatrix() const;
		float4x4 const & ProjectionMatrix() const;
		float4x4 const & ViewProjMatrix() const;

	private:
		float fov_;               // Field of view
		float aspect_;
		float near_clip_;
		float far_clip_;

		mutable float4x4 view_mat_;        // 视图矩阵
		mutable float4x4 inv_view_mat_;    // 视图矩阵逆矩阵
		mutable float4x4 proj_mat_;        // 投影矩阵
		mutable float4x4 inv_proj_mat_;    // 投影矩阵逆矩阵
		mutable float4x4 view_proj_mat_;   // 视图投影矩阵

		mutable bool need_recalc_view_proj_;
	};
}

#endif // Forge_Camera_hpp__