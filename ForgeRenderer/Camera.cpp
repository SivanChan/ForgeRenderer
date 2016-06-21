
#include "stdafx.h"
#include "Camera.h"

namespace Forge
{
	Camera::Camera()
		: fov_(FORGE_PI / 4.0f),
		aspect_(1.33333333333333f),
		near_clip_(100.0f),
		far_clip_(100000.0f),
		need_recalc_view_proj_(true)
	{
		SetViewParams(float3(0, 0, 0), float3(0, 0, 1), float3(0, 1, 0));
		SetProjParams(fov_, aspect_, near_clip_, far_clip_);
	}

	Camera::~Camera()
	{

	}

	void Camera::SetViewParams(float3 const & eye_pos, float3 const & look_at, float3 const & up_vec)
	{
		view_mat_ = Math::look_at_lh(eye_pos, look_at, up_vec);
		need_recalc_view_proj_ = true;
	}

	void Camera::SetProjParams(float fov, float aspect, float near_plane, float far_plane)
	{
		fov_ = fov;
		aspect_ = aspect;
		near_clip_ = near_plane;
		far_clip_ = far_plane;

		proj_mat_ = Math::perspective_fov_lh(fov_, aspect_, near_clip_, far_clip_);
		inv_proj_mat_ = Math::inverse(proj_mat_);
		need_recalc_view_proj_ = true;
	}

	Forge::float4x4 const & Camera::ViewMatrix() const
	{
		return view_mat_;
	}

	Forge::float4x4 const & Camera::ProjectionMatrix() const
	{
		return proj_mat_;
	}

	Forge::float4x4 const & Camera::ViewProjMatrix() const
	{
		if (need_recalc_view_proj_)
			view_proj_mat_ = ViewMatrix() * ProjectionMatrix();
		return view_proj_mat_;
	}
}