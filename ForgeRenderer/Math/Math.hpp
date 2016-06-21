/********************************************************************
	created:	2014/05/10
	created:	2014/5/10   17:47
	filename: 	Math.hpp
	author:		Sivan
	purpose:	数学库
*********************************************************************/

#ifndef Forge_Math_hpp__
#define Forge_Math_hpp__

#pragma once

#include <PreDeclare.h>

namespace Forge
{
	// 数学常量
	float const FORGE_PI      = 3.14159265f;              // π    //float(4.0f * std::atan(1.0));
	float const FORGE_2PI     = float(FORGE_PI * 2.0);    // 2π
	float const FORGE_PIdiv2  = float(FORGE_PI * 0.5);    // π/2
	float const FORGE_1divPI  = float(1.0f / FORGE_PI);   // 1/π
	float const FORGE_1div2PI = float(1.0f / FORGE_2PI);  // 1/2π

	float const DEG2RAD	= 0.01745329f;			          // 角度化弧度因数
	float const RAD2DEG	= 57.29577f;			          // 弧度化角度因数

	enum BoundIntersection
	{
		BI_Outside,
		BI_Inside,
		BI_Intersecting
	};

	// 数学运算
	namespace Math
	{
		// 三则最大
		template<typename T>
		inline T const & max3(T const & x, T const & y, T const & z)
		{
			return (std::max)((std::max)(x, y), z);
		}

		// 三则最小
		template<typename T>
		inline T const & min3(T const & x, T const & y, T const & z)
		{
			return (std::min)((std::min)(x, y), z);
		}

		// 小于等于x的最大整数
		template<typename T>
		inline T floor(T const & x)
		{
			return static_cast<T>(static_cast<int>(x > 0 ? x : (x - 1)));
		}

		// 判断value是否在low和high之间
		template<typename T>
		inline bool in_bound(T const & value, T const & low, T const & high)
		{
			return ((value >= low) && (value <= high));
		}

		// 限制 val 在 low 和 high 之间
		template <typename T>
		inline T const & clamp(T const & val, T const & low, T const & high)
		{
			return (std::max)(low, (std::min)(high, val));
		}

		// 平方
		template<typename T>
		inline T sqr(T const & x)
		{
			return x * x;
		}

		// 弧度转角度
		template<typename T>
		inline T degree_to_radian(T const & x)
		{
			return static_cast<T>(x * DEG2RAD);
		}

		// 角度转弧度
		template<typename T>
		inline T radian_to_degree(T const & x)
		{
			return static_cast<T>(x * RAD2DEG);
		}

		// 立方
		template<typename T>
		inline T cube(T const & x)
		{
			return x * x * x;
		}

		// 求长度
		template<typename T>
		inline T length(Vector2_T<T> const & rhs)
		{
			return (T)std::sqrt(rhs.x() * rhs.x() + rhs.y() * rhs.y());
		}

		template<typename T>
		inline T length(Vector3_T<T> const & rhs)
		{
			return (T)std::sqrt(rhs.x() * rhs.x() + rhs.y() * rhs.y() + rhs.z() * rhs.z());
		}

		// 长度的平方
		template<typename T>
		inline T squared_length(Vector2_T<T> const & rhs)
		{
			return (T)(rhs.x() * rhs.x() + rhs.y() * rhs.y());
		}

		template<typename T>
		inline T squared_length(Vector3_T<T> const & rhs)
		{
			return (T)(rhs.x() * rhs.x() + rhs.y() * rhs.y() + rhs.z() * rhs.z());
		}

		template<typename T>
		inline T squared_length(Vector4_T<T> const & rhs)
		{
			return (T)(rhs.x() * rhs.x() + rhs.y() * rhs.y() + rhs.z() * rhs.z() + rhs.w() * rhs.w());
		}

		template<typename T>
		inline T squared_length(Plane_T<T> const & rhs)
		{
			return (T)(rhs.a() * rhs.a() + rhs.b() + rhs.b() + rhs.c() * rhs.c());
		}

		template<typename T>
		inline T squared_length(Quaternion_T<T> const & rhs)
		{
			return (T)(rhs.x() * rhs.x() + rhs.y() * rhs.y() + rhs.z() * rhs.z() + rhs.w() * rhs.w());
		}

		// 交换
		template<typename T, typename U>
		inline void swap(T & lhs, U & rhs)
		{
			T val(lhs);
			lhs = rhs;
			rhs = val;
		}

		template<typename T>
		inline void swap(Vector2_T<T> & lhs, Vector2_T<T> & rhs)
		{
			lhs.Swap(rhs);
		}

		template<typename T>
		inline void swap(Vector3_T<T> & lhs, Vector3_T<T> & rhs)
		{
			lhs.Swap(rhs);
		}

		template<typename T>
		inline void swap(Vector4_T<T> & lhs, Vector4_T<T> & rhs)
		{
			lhs.Swap(rhs);
		}

		// 
		template<typename T>
		T recip_sqrt(T const & rhs)
		{
			if ( rhs < std::numeric_limits<T>::epsilon() )
				return (T)0;
			return 1.0f / std::sqrt(rhs);
		}

		// 归一化
		template<typename T>
		T normalize(T const & rhs)
		{
			return rhs * recip_sqrt(Math::squared_length(rhs));
		}

		// 叉乘
		template<typename T>
		inline Vector3_T<T> cross_product(Vector3_T<T> const & lhs, Vector3_T<T> const & rhs)
		{
			return Vector3_T<T>( lhs.y() * rhs.z() - lhs.z() * rhs.y(),
				lhs.z() * rhs.x() - lhs.x() * rhs.z(),
				lhs.x() * rhs.y() - lhs.y() * rhs.x() );
		}

		template<typename T>
		Quaternion_T<T> cross_product(Quaternion_T<T> const & lhs, Quaternion_T<T> const & rhs)
		{
			return Quaternion_T<T>(
				lhs.w() * rhs.w() - lhs.x() * rhs.x() - lhs.y() * rhs.y() - lhs.z() * rhs.z(),
				lhs.w() * rhs.x() + lhs.x() * rhs.w() + lhs.z() * rhs.y() - lhs.y() * rhs.z(),
				lhs.w() * rhs.y() + lhs.y() * rhs.w() + lhs.x() * rhs.z() - lhs.z() * rhs.x(),
				lhs.w() * rhs.z() + lhs.z() * rhs.w() + lhs.y() * rhs.x() - lhs.x() * rhs.y() );
		}
		template Quaternion cross_product(Quaternion const & lhs, Quaternion const & rhs);

		// 点乘
		template<typename T>
		inline T dot_product(Vector3_T<T> const & lhs, Vector3_T<T> const & rhs)
		{
			return lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.z() * rhs.z();
		}

		// vector matrix 相乘
		template<typename T>
		Vector4_T<T> mul(Vector4_T<T> const & v, Matrix4x4_T<T> const & m)
		{
			return Vector4_T<T>( 
				v.x() * m(0, 0) + v.y() * m(1, 0) + v.z() * m(2, 0) + v.w() * m(3, 0),
				v.x() * m(0, 1) + v.y() * m(1, 1) + v.z() * m(2, 1) + v.w() * m(3, 1),
				v.x() * m(0, 2) + v.y() * m(1, 2) + v.z() * m(2, 2) + v.w() * m(3, 2), 
				v.x() * m(0, 3) + v.y() * m(1, 3) + v.z() * m(2, 3) + v.w() * m(3, 3) );
		}

		/** 相交测试 */

		// 球 - 球
		template<typename T>
		bool intersect(Sphere_T<T> const & lhs, Sphere_T<T> const & rhs);

		// 球 - 面
		template<typename T>
		bool intersect(Sphere_T<T> const & s, Plane_T<T> const & p);

		// 球 - 包围盒
		template<typename T>
		bool intersect(Sphere_T<T> const & s, AABBox_T<T> const & b);

		// 球 - 点
		template<typename T>
		bool intersect(Sphere_T<T> const & s, Vector3_T<T> const & p);

		// 包围盒 - 包围盒
		template<typename T>
		bool intersect(AABBox_T<T> const & lhs, AABBox_T<T> const & rhs);

		// 包围盒 - 点
		template<typename T>
		bool intersect(AABBox_T<T> const & b, Vector3_T<T> const & p);

		// 射线 - 面
		template<typename T>
		std::pair<bool,T> intersect(Ray_T<T> const & r, Plane_T<T> const & p);

		// 射线 - 球 From OGRE
		template<typename T>
		std::pair<bool,T> intersect(Ray_T<T> const & r, Sphere_T<T> const & s);

		// 射线 - 包围盒 From Gameplay
		template<typename T>
		std::pair<bool,T> intersect(Ray_T<T> const & r, AABBox_T<T> const & b);

		// 面 - 包围盒
		template<typename T>
		BoundIntersection intersect(Plane_T<T> const & p, AABBox_T<T> const & b);

		// 平截头体 - 包围盒
		template<typename T>
		BoundIntersection intersect(Frustum_T<T> const & f, AABBox_T<T> const & b);

		// 平截头体 - 球
		template<typename T>
		BoundIntersection intersect(Frustum_T<T> const & f, Sphere_T<T> const & s);

		// 平截头体 - 点
		template<typename T>
		bool intersect(Frustum_T<T> const & f, Vector3_T<T> const & p);


		//////////////////////////////////////////////////////////////////////////
		/// 三维向量
		template<typename T>
		Vector3_T<T> transform_quaternion(Vector3_T<T> const & v, Quaternion_T<T> const & q);
	
		//////////////////////////////////////////////////////////////////////////
		/// 四元数

		// 四元数的共轭
		template<typename T>
		Quaternion_T<T> conjugate(Quaternion_T<T> const & rhs);

		// 绕轴旋转角度
		template<typename T>
		Quaternion_T<T> rotation_axis(Vector3_T<T> const & v, T const & angle);

		// 
		template <typename T>
		Quaternion_T<T> inverse(Quaternion_T<T> const & rhs);

		/** 矩阵 */
		/// 转置
		template<typename T>
		Matrix4x4_T<T> transpose(Matrix4x4_T<T> const & m);

		/// 四元数转矩阵
		template<typename T>
		Matrix4x4_T<T> to_matrix(Quaternion_T<T> const & rhs);

		/// 3阶行列式
		template<typename T>
		T minor(Matrix4x4_T<T> const & m, T const r0, T const r1, T const r2,
			                              T const c0, T const c1, T const c2);
		/// 行列式
		template<typename T>
		T determinant(Matrix4x4_T<T> const & m);

		/// 逆矩阵
		template<typename T>
		Matrix4x4_T<T> inverse(Matrix4x4_T<T> const & m);

		template<typename T>
		Matrix4x4_T<T> transformation(Vector3_T<T> const & pos, Vector3_T<T> const & scale, Quaternion_T<T> const & orientation);
	
		/**
			左手系视图矩阵

			zaxis = normal(At - Eye)
			xaxis = normal(cross(Up, zaxis))
			yaxis = cross(zaxis, xaxis)

			xaxis.x           yaxis.x           zaxis.x          0
			xaxis.y           yaxis.y           zaxis.y          0
			xaxis.z           yaxis.z           zaxis.z          0
			-dot(xaxis, eye)  -dot(yaxis, eye)  -dot(zaxis, eye)  1
		*/
		template<typename T>
		Matrix4x4_T<T> look_at_lh(Vector3_T<T> const & eye, Vector3_T<T> const & at, Vector3_T<T> const & up);

		/** 
			右手系视图矩阵

			zaxis = normal(Eye - At)
			xaxis = normal(cross(Up, zaxis))
			yaxis = cross(zaxis, xaxis)

			xaxis.x           yaxis.x           zaxis.x          0
			xaxis.y           yaxis.y           zaxis.y          0
			xaxis.z           yaxis.z           zaxis.z          0
			-dot(xaxis, eye)  -dot(yaxis, eye)  -dot(zaxis, eye)  1
		*/
		template<typename T>
		Matrix4x4_T<T> look_at_rh(Vector3_T<T> const & eye, Vector3_T<T> const & at, Vector3_T<T> const & up);
	
		/// 左手系透视投影矩阵
		template<typename T>
		Matrix4x4_T<T> perspective_fov_lh(T const fov, T const aspect, T const zn, T const zf);

		/// 右手系透视投影矩阵
		template<typename T>
		Matrix4x4_T<T> perspective_fov_rh(T const fov, T const aspect, T const zn, T const zf);

		/// 左手系正射投影矩阵
		template<typename T>
		Matrix4x4_T<T> ortho_lh(T const w, T const h, T const zn, T const zf);

		/// 右手系正射投影矩阵
		template<typename T>
		Matrix4x4_T<T> ortho_rh(T const w, T const h, T const zn, T const zf);
	}
}

#include <Math/Vector2.hpp>
#include <Math/Vector3.hpp>
#include <Math/Vector4.hpp>
#include <Math/Matrix4x4.hpp>
#include <Math/AABBox.hpp>
#include <Math/Sphere.hpp>
#include <Math/Color.hpp>
#include <Math/Plane.hpp>
#include <Math/Frustum.hpp>
#include <Math/Size.hpp>
#include <Math/Rect.hpp>
#include <Math/Ray.hpp>
#include <Math/Quaternion.hpp>
#include <Math/Math.inl>

#endif // Forge_Math_hpp__