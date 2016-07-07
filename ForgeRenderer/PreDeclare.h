/********************************************************************
	created  :	2016/6/16
	author   :	Sivan
	source   :  声明
*********************************************************************/

#ifndef Forge_PreDeclare_hpp__
#define Forge_PreDeclare_hpp__

#pragma once

#include <cstdint>

namespace Forge
{
	// 设备类型
	enum DeviceType
	{
		DT_Soft,
		DT_D3D11
	};

	// 填充模式
	enum RenderMode
	{
		RM_WireFrame,
		RM_Solid
	};

	// types
	using std::uint64_t;
	using std::uint32_t;
	using std::uint16_t;
	using std::uint8_t;

	using std::int64_t;
	using std::int32_t;
	using std::int16_t;
	using std::int8_t;

	// Math
	template<typename T>
	class Vector2_T;
	typedef Vector2_T<int32_t>  int2;
	typedef Vector2_T<uint32_t> uint2;
	typedef Vector2_T<float>    float2;
	typedef Vector2_T<double>   double2;

	template<typename T>
	class Vector3_T;
	typedef Vector3_T<int32_t>  int3;
	typedef Vector3_T<uint32_t> uint3;
	typedef Vector3_T<float>    float3;
	typedef Vector3_T<double>   double3;

	template<typename T>
	class Vector4_T;
	typedef Vector4_T<int32_t>  int4;
	typedef Vector4_T<uint32_t> uint4;
	typedef Vector4_T<float>    float4;
	typedef Vector4_T<double>   double4;

	template<typename T>
	class Matrix4x4_T;
	typedef Matrix4x4_T<float>    float4x4;
	typedef Matrix4x4_T<double>   double4x4;

	template<typename T>
	class AABBox_T;
	typedef AABBox_T<float>     AABBox;

	template<typename T>
	class Size_T;
	typedef Size_T<float> Size;

	template<typename T>
	class Rect_T;
	typedef Rect_T<float> Rectf;

	template<typename T>
	class Plane_T;
	typedef Plane_T<float> Plane;

	template<typename T>
	class Color_T;
	typedef Color_T<float> Color;

	template<typename T>
	class Sphere_T;
	typedef Sphere_T<float> Sphere;

	template<typename T>
	class Ray_T;
	typedef Ray_T<float> Ray;

	template<typename T>
	class Frustum_T;
	typedef Frustum_T<float> Frustum;

	template<typename T>
	class Quaternion_T;
	typedef Quaternion_T<float> Quaternion;

	// class
	class AppFramework;
	typedef std::shared_ptr<AppFramework> AppFrameworkPtr;

	class RenderDevice;
	typedef std::shared_ptr<RenderDevice> RenderDevicePtr;

	class Model;
	typedef std::shared_ptr<Model> ModelPtr;

	class Camera;
	typedef std::shared_ptr<Camera> CameraPtr;

	class KeyboardInput;
	typedef std::shared_ptr<KeyboardInput> KeyboardInputPtr;
}

#endif // Forge_PreDeclare_hpp__