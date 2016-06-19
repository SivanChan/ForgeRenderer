/********************************************************************
	created:	2013/10/14
	created:	2013/10/14   23:55
	filename: 	Math.inl
	author:		Sivan
	purpose:	参考文献：《3D数学基础：图形与游戏开发》
	                      《Real-time Rendering Third Edition》
*********************************************************************/

#include <Math/Math.hpp>

namespace Forge
{
	namespace Math
	{
		/** 相交测试*/

		// 球 - 球
		template<typename T>
		bool intersect(Sphere_T<T> const & lhs, Sphere_T<T> const & rhs)
		{
			return squared_length(lhs.Center() - rhs.Center()) <= sqr(lhs.Radius() + rhs.Radius());
		}
		template bool intersect(Sphere const & lhs, Sphere const & rhs);

		// 球 - 面
		template<typename T>
		bool intersect(Sphere_T<T> const & s, Plane_T<T> const & p)
		{
			return ( std::abs(p.GetDistance(s.Center())) <= s.Radius() );
		}
		template bool intersect(Sphere const & s, Plane const & p);

		// 球 - 包围盒
		template<typename T>
		bool intersect(Sphere_T<T> const & s, AABBox_T<T> const & b)
		{
			if (b.IsNull()) return false;
			if (b.IsInfinite()) return true;

			/**
			查找离包围盒最近的点，如果两点距离小于半径，则相交
			*/
			Vector3_T<T> const & center = s.Center();
			Vector3_T<T> const & min = b.Min();
			Vector3_T<T> const & max = b.Max();

			T d = 0;
			for (int i = 0; i < 3; ++i)
			{
				if ( center.ptr()[i] < min.ptr()[i] )
				{
					d += sqr(center.ptr()[i] - min.ptr()[i]); 
				}
				else if ( center.ptr()[i] > max.ptr()[i] )
				{
					d += sqr(center.ptr()[i] - max.ptr()[i]);
				}
			}
			return d <= sqr(s.Radius());
		}
		template bool intersect(Sphere const & lhs, AABBox const & rhs);

		// 球 - 点
		template<typename T>
		bool intersect(Sphere_T<T> const & s, Vector3_T<T> const & p)
		{
			return (squared_length(p - s.Center()) <= sqr(s.Radius())) ? true : false;
		}
		template bool intersect(Sphere const & lhs, float3 const & p);

		// 包围盒 - 包围盒
		template<typename T>
		bool intersect(AABBox_T<T> const & lhs, AABBox_T<T> const & rhs)
		{
			Vector3_T<T> const t = rhs.Center() - lhs.Center();
			Vector3_T<T> const e = rhs.HalfSize() - lhs.HalfSize();
			return ( std::abs(t.x()) <= e.x() && std::abs(t.y()) <= e.y() && std::abs(t.z()) <= e.z() );
		}
		template bool intersect(AABBox const & lhs, AABBox const & rhs);

		// 包围盒 - 点
		template<typename T>
		bool intersect(AABBox_T<T> const & b, Vector3_T<T> const & p)
		{
			return ( in_bound(p.x(), b.Min().x(), b.Max().x()) &&
				in_bound(p.y(), b.Min().y(), b.Max().y()) &&
				in_bound(p.z(), b.Min().z(), b.Max().z()) );
		}
		template bool intersect(AABBox const & lhs, float3 const & rhs);

		// 射线 - 面
		template<typename T>
		std::pair<bool,T> intersect(Ray_T<T> const & r, Plane_T<T> const & p)
		{
			// 面法线和射线点积为零，射线与面平行
			T nd = dot_product(p.Normal(), r.Direction());
			if ( std::abs(nd) < std::numeric_limits<T>::epsilon())
			{
				// 射线与面平行
				return std::pair<bool, T>(false, 0.0f);
			}
			else
			{
				/*
				t = ( - n·p0 + n·p1)/(n·u);
				*/
				T nod = dot_product(p.Normal(), r.Origin()) + p.d();
				T t = -(nod/nd);
				return std::pair<bool,T>(t >= 0, t);
			}
		}
		template std::pair<bool,float> intersect(Ray const & lhs, Plane const & rhs);

		// 射线 - 球 From OGRE
		template<typename T>
		std::pair<bool,T> intersect(Ray_T<T> const & r, Sphere_T<T> const & s)
		{
			// 计算射线起点是否在球内
			Vector3_T<T> const & oc = r.Origin() - s.Center();
			if ( squared_length(oc) <= sqr(s.Radius()) )
			{
				return std::pair<bool,T>(true,(T)0);
			}

			T a = dot_product(r.Direction(), r.Direction());
			T b = 2 * dot_product(oc, r.Direction());
			T c = dot_product(oc, oc) - sqr(s.Radius());
			T d = sqr(b) - (4 * a * c);
			if (d < 0)
			{
				return std::pair<bool, T>(false, 0.0f);
			} 
			else
			{
				// d = 0 一个交点 d > 0 两个交点
				T t = (-b - std::sqrt(d)) / (2 * a);
				if ( t < 0 )
					t = ( -b + std::sqrt(d) ) / (2 * a);
				return std::pair<bool, T>(true, t);
			}
		}
		template std::pair<bool,float> intersect(Ray const & lhs, Sphere const & rhs);

		// 射线 - 包围盒 From Gameplay
		template<typename T>
		std::pair<bool,T> intersect(Ray_T<T> const & r, AABBox_T<T> const & b)
		{
			if (b.IsNull()) return std::pair<bool,T>(false,(T)0);
			if (b.IsInfinite()) return std::pair<bool,T>(true,(T)0);

			// 射线起点是否在包围盒内
			if ( r.Origin() > b.Min() && r.Origin() < b.Max() )
			{
				return std::pair<bool,T>(true,(T)0);
			}
	
			T fNear;
			T fFar;
			T min;
			T max;
			bool hit = false;

			// x轴
			T div = 1.0f / r.Direction().x();
			min = div ? (b.Min().x() - r.Origin().x()) * div : (b.Max().x() - r.Origin().x()) * div;
			max = div ? (b.Max().x() - r.Origin().x()) * div : (b.Min().x() - r.Origin().x()) * div;

			fNear = min;
			fFar = max;

			if ( fNear > fFar || fFar < 0.0f )
			{
				return std::pair<bool,T>(false,(T)0);
			}

			// y
			div = 1.0f / r.Direction().y();
			min = div ? (b.Min().y() - r.Origin().y()) * div : (b.Max().y() - r.Origin().y()) * div;
			max = div ? (b.Max().y() - r.Origin().y()) * div : (b.Min().y() - r.Origin().y()) * div;

			if ( min > fNear ) fNear = min;
			if ( max < fFar ) fFar = max;

			if ( fNear > fFar || fFar < 0.0f )
			{
				return std::pair<bool,T>(false,(T)0);
			}

			// z
			div = 1.0f / r.Direction().z();
			min = div ? (b.Min().z() - r.Origin().z()) * div : (b.Max().z() - r.Origin().z()) * div;
			max = div ? (b.Max().z() - r.Origin().z()) * div : (b.Min().z() - r.Origin().z()) * div;

			if ( min > fNear ) fNear = min;
			if ( max < fFar ) fFar = max;

			if ( fNear > fFar || fFar < 0.0f )
			{
				return std::pair<bool,T>(false,(T)0);
			}
			return std::pair<bool,T>(true,fNear);
		}
		template std::pair<bool,float> intersect(Ray const & lhs, AABBox const & rhs);

		// 面 - 包围盒
		template<typename T>
		BoundIntersection intersect(Plane_T<T> const & p, AABBox_T<T> const & b)
		{
			if (b.IsNull()) return BI_Outside;
			if (b.IsInfinite()) return BI_Intersecting;

			Vector3_T<T> c = (b.Min() + b.Max()) / 2.0;
			Vector3_T<T> h = (b.Max() - b.Min()) / 2.0;
			Vector3_T<T> n = p.Normal();

			T e = h.x() * std::abs(n.x()) + h.y() * std::abs(n.y()) + h.z() * std::abs(n.z());
			T s = dot_product( c, p.Normal() ) + p.d();

			if ( s - e > 0 ) return BI_Outside;
			if ( s + e < 0 ) return BI_Inside;

			return BI_Intersecting;
		}
		template BoundIntersection intersect(Plane const & lhs, AABBox const & rhs);


		// 平截头体 - 包围盒
		template<typename T>
		BoundIntersection intersect(Frustum_T<T> const & f, AABBox_T<T> const & b)
		{
			Vector3_T<T> const & min = b.Min();
			Vector3_T<T> const & max = b.Max();

			bool intersect = false;
			for (int i=0; i<6; ++i)
			{
				Plane_T<T> const & plane = f.Plane((Frustum_T<T>::FrustumPlane)i);
				Vector3_T<T> v0( plane.a() < 0 ? min.x() : max.x(),
					plane.b() < 0 ? min.y() : max.y(),
					plane.c() < 0 ? min.z() : max.z() );
				Vector3_T<T> v1( plane.a() < 0 ? max.x() : min.x(),
					plane.b() < 0 ? max.y() : min.y(),
					plane.c() < 0 ? max.z() : min.z() );

				if ( (dot_product( plane.Normal(), v0 ) + plane.d()) < 0 )
					return BI_Outside;
				if ( (dot_product( plane.Normal(), v1 ) + plane.d()) < 0 )
					intersect = true; 
			}
			return intersect ? BI_Intersecting : BI_Inside;
		}
		template BoundIntersection intersect(Frustum const & f, AABBox const & b);

		// 平截头体 - 球
		template<typename T>
		BoundIntersection intersect(Frustum_T<T> const & f, Sphere_T<T> const & s)
		{
			bool intersect = false;
			for (int i=0; i<6; ++i)
			{
				Plane_T<T> const & plane = f.Plane((Frustum_T<T>::FrustumPlane)i);
				T d = dot_product( plane.Normal(), s.Center() ) + plane.d();
				if ( d <= -s.Radius() )
				{
					return BI_Outside;
				}
				if ( d > s.Radius() )
				{
					intersect = true;
				}
			}

			return intersect ? BI_Intersecting : BI_Inside;
		}
		template BoundIntersection intersect(Frustum const & f, Sphere const & s);

		// 平截头体 - 点
		template<typename T>
		bool intersect(Frustum_T<T> const & f, Vector3_T<T> const & p)
		{
			for (int i=0; i<6; ++i)
			{
				Plane_T<T> const & plane = f.Plane((Frustum_T<T>::FrustumPlane)i);
				if (dot_product(plane.Normal(), p) + plane.d() < 0)
				{
					return false;
				}
			}
			return true;
		}
		template bool intersect(Frustum const & f, float3 const & p);

		//////////////////////////////////////////////////////////////////////////
		/// 三维向量
		template<typename T>
		Vector3_T<T> transform_quaternion(Vector3_T<T> const & v, Quaternion_T<T> const & q)
		{
			//return v + cross_product( q.v(), v ) * q.w() * T(2) + ( cross_product( q.v(), cross_product( q.v(), v ) ) ) * T(2);
			return v + cross_product(q.v(), cross_product(q.v(), v) + v * q.w()) * T(2);
		}
		template float3 transform_quaternion(float3 const & v, Quaternion const & q);
		
		/** 四元数 */

		// 共轭
		template<typename T>
		Quaternion_T<T> conjugate(Quaternion_T<T> const & rhs)
		{
			return Quaternion_T<T>(-rhs.x(), -rhs.y(), -rhs.z(), rhs.w());
		}
		template Quaternion conjugate(Quaternion const & rhs);

		// 绕轴旋转角度
		template<typename T>
		Quaternion_T<T> rotation_axis(Vector3_T<T> const & v, T const & angle)
		{
			T angle_over2 = angle * 0.5f;
			T sin_angle_over2 = std::sin(angle_over2);
			T cos_angle_over2 = std::cos(angle_over2);

			if ( squared_length(v) < std::numeric_limits<T>::epsilon() )
			{
				return Quaternion_T<T>( cos_angle_over2, sin_angle_over2, sin_angle_over2, sin_angle_over2 );
			}
			else
			{
				return Quaternion_T<T>( normalize(v) * sin_angle_over2, cos_angle_over2 );
			}
		}
		template Quaternion rotation_axis(float3 const & v, float const & angle);


		template <typename T>
		Quaternion_T<T> inverse( Quaternion_T<T> const & rhs )
		{
			T const norm = squared_length(rhs);
			if ( norm > 0.0f )
			{
				T inv = 1.0f / norm;
				return Quaternion_T<T>( rhs.w() * inv , -rhs.x() * inv, -rhs.y() * inv, -rhs.z() * inv );
			}
			else
			{
				return Quaternion_T<T>::Identity();
			}
		}
		template Quaternion inverse( Quaternion const & q );


		/** 矩阵 */
		template<typename T>
		Matrix4x4_T<T> transpose(Matrix4x4_T<T> const & m)
		{
			return Matrix4x4_T<T>(
				m(0, 0), m(1, 0), m(2, 0), m(3, 0),
				m(0, 1), m(1, 1), m(2, 1), m(3, 1),
				m(0, 2), m(1, 2), m(2, 2), m(3, 2),
				m(0, 3), m(1, 3), m(2, 3), m(3, 3));
		}
		template float4x4 transpose(float4x4 const & m);

		template<typename T>
		Matrix4x4_T<T> to_matrix(Quaternion_T<T> const & rhs)
		{
			/*
				《3D数学基础：图形与游戏开发》 P167 （左手坐标系）
				[ 1 - 2*y2 - 2*z2  2*x*y + 2*w*z     2*x*z - 2*w*y    0]
				[ 2*x*y - 2*w*z    1 - 2*x2 - 2*z2   2*y*z + 2*w*x    0]
				[ 2*x*z + 2*w*y    2*y*z - 2*w*x     1 - 2*x2 - 2*y2  0]
				[ 0                0                 0                1]
			*/

			T const x2(rhs.x() + rhs.x());
			T const y2(rhs.y() + rhs.y());
			T const z2(rhs.z() + rhs.z());

			T const xx2(rhs.x() * x2), xy2(rhs.x() * y2), xz2(rhs.x() * z2);
			T const yy2(rhs.y() * y2), yz2(rhs.y() * z2), zz2(rhs.z() * z2);
			T const wx2(rhs.w() * x2), wy2(rhs.w() * y2), wz2(rhs.w() * z2);

			return Matrix4x4_T<T>(
				1 - yy2 - zz2,	xy2 + wz2,		xz2 - wy2,		0,
				xy2 - wz2,		1 - xx2 - zz2,	yz2 + wx2,		0,
				xz2 + wy2,		yz2 - wx2,		1 - xx2 - yy2,	0,
				0,				0,				0,				1);
		}
		template float4x4 to_matrix(Quaternion const & rhs);

		template<typename T>
		T minor(Matrix4x4_T<T> const & m, size_t const r0, size_t const r1, size_t const r2,
			size_t const c0, size_t const c1, size_t const c2)
		{
			return m(r0,c0) * ( m(r1,c1) * m(r2,c2) - m(r2,c1) * m(r1,c2) ) -
				   m(r0,c1) * ( m(r1,c0) * m(r2,c2) - m(r2,c0) * m(r1,c2) ) +
				   m(r0,c2) * ( m(r1,c0) * m(r2,c1) - m(r2,c0) * m(r1,c1) );
		}
		template float minor(float4x4 const & m, float const ro, float const r1, float const r2, float const co, float const c1, float const c2);

		template<typename T>
		T determinant(Matrix4x4_T<T> const & m)
		{
			return m(0,0) * minor(m, 1, 2, 3, 1, 2, 3) -
				   m(0,1) * minor(m, 1, 2, 3, 0, 2, 3) +
				   m(0,2) * minor(m, 1, 2, 3, 0, 1, 3) -
				   m(0,3) * minor(m, 1, 2, 3, 0, 1, 2);
		}
		template float determinant(float4x4 const & m);

		template<typename T>
		Matrix4x4_T<T> inverse(Matrix4x4_T<T> const & m)
		{
			// 1.求行列式值
			T det(determinant(m));
			if ( !(std::abs(det) <= std::numeric_limits<T>::epsilon()) )
			{
				// 2.求伴随矩阵
				T div_det(T(1)/det);
				return Matrix4x4_T<T>( 
					+div_det * minor( m, 1, 2, 3, 1, 2, 3 ), 
					-div_det * minor( m, 0, 2, 3, 1, 2, 3 ), 
					+div_det * minor( m, 0, 1, 3, 1, 2, 3 ), 
					-div_det * minor( m, 0, 1, 2, 1, 2, 3 ),

					-div_det * minor( m, 1, 2, 3, 0, 2, 3 ), 
					+div_det * minor( m, 0, 2, 3, 0, 2, 3 ), 
					-div_det * minor( m, 0, 1, 3, 0, 2, 3 ), 
					+div_det * minor( m, 0, 1, 2, 0, 2, 3 ),

					+div_det * minor( m, 1, 2, 3, 0, 1, 3 ),
					-div_det * minor( m, 0, 2, 3, 0, 1, 3 ), 
					+div_det * minor( m, 0, 1, 3, 0, 1, 3 ), 
					-div_det * minor( m, 0, 1, 2, 0, 1, 3 ),

					-div_det * minor( m, 1, 2, 3, 0, 1, 2 ),
					+div_det * minor( m, 0, 2, 3, 0, 1, 2 ), 
					-div_det * minor( m, 0, 1, 3, 0, 1, 2 ), 
					+div_det * minor( m, 0, 1, 2, 0, 1, 2 )
															);
			} 
			else
			{
				return m;
			}
		}
		template float4x4 inverse(float4x4 const & m);

		template<typename T>
		Matrix4x4_T<T> transformation(Vector3_T<T> const & pos, Vector3_T<T> const & scale, Quaternion_T<T> const & orientation)
		{
			Matrix4x4_T<T> m;
			m = to_matrix(orientation);

			Matrix4x4_T<T> out;
			out(0,0) = m(0,0) * scale.x(); out(0,1) = m(0,1) * scale.y(); out(0,2) = m(0,2) * scale.z();
			out(1,0) = m(1,0) * scale.x(); out(1,1) = m(1,1) * scale.y(); out(1,2) = m(1,2) * scale.z();
			out(2,0) = m(2,0) * scale.x(); out(2,1) = m(2,1) * scale.y(); out(2,2) = m(2,2) * scale.z();

			out(3,0) = pos.x(); out(3,1) = pos.y(); out(3,2) = pos.z();
			out(0,3) = 0.0f;    out(1,3) = 0.0f;    out(2,3) = 0.0f; out(3,3) = 1.0f;

			return out;
		}
		template float4x4 transformation(float3 const & pos, float3 const & scale, Quaternion const & orientation);
	
		/** From DirectX 3D SDK*/
		template<typename T>
		Matrix4x4_T<T> look_at_lh(Vector3_T<T> const & eye, Vector3_T<T> const & at, Vector3_T<T> const & up)
		{
			Vector3_T<T> zaxis(normalize(at - eye));
			Vector3_T<T> xaxis(normalize(cross_product(up,zaxis)));
			Vector3_T<T> yaxis(cross_product(zaxis, xaxis));

			return Matrix4x4_T<T>( xaxis.x(), yaxis.x(), zaxis.x(), 0,
				                 xaxis.y(), yaxis.y(), zaxis.y(), 0,
								 xaxis.z(), yaxis.z(), zaxis.z(), 0,
								 -dot_product(xaxis,eye), -dot_product(yaxis,eye), -dot_product(zaxis,eye), 1 );
		}
		template float4x4 look_at_lh(float3 const & eye, float3 const & at, float3 const & up);

		template<typename T>
		Matrix4x4_T<T> look_at_rh(Vector3_T<T> const & eye, Vector3_T<T> const & at, Vector3_T<T> const & up)
		{
			Vector3_T<T> zaxis(normalize(eye - at));
			Vector3_T<T> xaxis(normalize(cross_product(up,zaxis)));
			Vector3_T<T> yaxis(cross_product(zaxis, xaxis));

			return Matrix4x4_T<T>( xaxis.x(), yaxis.x(), zaxis.x(), 0,
								 xaxis.y(), yaxis.y(), zaxis.y(), 0,
								 xaxis.z(), yaxis.z(), zaxis.z(), 0,
								 -dot_product(xaxis,eye), -dot_product(yaxis,eye), -dot_product(zaxis,eye), 1 );
		}
		template float4x4 look_at_rh(float3 const & eye, float3 const & at, float3 const & up);

		template<typename T>
		Matrix4x4_T<T> perspective_fov_lh(T const fov, T const aspect, T const zn, T const zf)
		{
			T const yscale(T(1) / std::tan(fov / 2.0f));
			T const xscale(yscale / aspect);
			T const q(zf / (zf - zn));
			return Matrix4x4_T<T>(
				xscale, 0,      0,             0,
				0,      yscale, 0,             0,
				0,      0,      q,             1,
				0,      0,      -zn*q,         0 );
		}
		template float4x4 perspective_fov_lh(float const fov, float const aspect, float const zn, float const zf);

		template<typename T>
		Matrix4x4_T<T> perspective_fov_rh(T const fov, T const aspect, T const zn, T const zf)
		{
			T const yscale(T(1) / std::tan(fov / 2.0f));
			T const xscale(yscale / aspect);
			T const q(zf / (zn - zf));
			return Matrix4x4_T<T>(
				xscale, 0, 0, 0,
				0, yscale, 0, 0,
				0, 0, q, -1,
				0, 0, zn*q, 0
				);
		}
		template float4x4 perspective_fov_rh(float const fov, float const aspect, float const zn, float const zf);

		template<typename T>
		Matrix4x4_T<T> ortho_lh(T const w, T const h, T const zn, T const zf)
		{
			return Matrix4x4_T<T>(
				2/w, 0, 0, 0,
				0, 2/h, 0, 0,
				0, 0, 1/(zf-zn), 0,
				0, 0, -zn/(zf-zn), 1);
		}
		template float4x4 ortho_lh(float const w, float const h, float const zn, float const zf);

		template<typename T>
		Matrix4x4_T<T> ortho_rh(T const w, T const h, T const zn, T const zf)
		{
			return Matrix4x4_T<T>(
				2/w, 0, 0, 0,
				0, 2/h, 0, 0,
				0, 0, 1/(zn-zf), 0,
				0, 0, zn/(zn-zf), 1);
		}
		template float4x4 ortho_rh(float const w, float const h, float const zn, float const zf);
	}
}