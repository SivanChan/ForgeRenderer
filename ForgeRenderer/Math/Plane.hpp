/********************************************************************
	created:	2014/05/11
	created:	2014/5/11   14:18
	filename: 	Plane.hpp
	author:		Sivan
	purpose:	三维空间平面
				平面方程       ax + by + cz + d = 0
				法向量         (a,b,c)
				原点到平面距离 d
*********************************************************************/

#ifndef Forge_Plane_hpp__
#define Forge_Plane_hpp__

#pragma once

#include <Math/Vector3.hpp>
#include <Math/Vector4.hpp>

namespace Forge
{
	template<typename T>
	class Plane_T
	{
	public:
		typedef T                    value_type;
		typedef Plane_T<T>           this_type;
		typedef value_type &         reference;
		typedef value_type const &   const_reference;

		template<typename U>
		friend class Plane_T;

	public:
		Plane_T()
		{
		}

		Plane_T(T const & a, T const & b, T const & c, T const & d)
			: plane_(a,b,c,d)
		{
		}

		Plane_T(Plane_T<T> const & rhs)
			: plane_(rhs.plane_)
		{
		}

		explicit Plane_T(T const * rhs)
			: plane_(rhs)
		{
		}

		template<typename U>
		explicit Plane_T(Plane_T<U> const & rhs)
			: plane_(rhs.plane_)
		{
		}

		explicit Plane_T(Vector4_T<T> const & rhs)
			: plane_(rhs)
		{
		}

		reference a()
		{
			return plane_.x();
		}

		const_reference a() const
		{
			return plane_.x();
		}

		reference b()
		{
			return plane_.y();
		}

		const_reference b() const
		{
			return plane_.y();
		}

		reference c()
		{
			return plane_.z();
		}

		const_reference c() const
		{
			return plane_.z();
		}

		reference d()
		{
			return plane_.w();
		}

		const_reference d() const
		{
			return plane_.w();
		}

		Plane_T operator * (T const rhs) const
		{
			return Plane_T<T>(plane_ * rhs);
		}

		Plane_T<T> & operator = (Plane_T<T> const & rhs)
		{
			plane_ = rhs.plane_;
			return *this;
		}

		Plane_T<T> & operator = (Vector4_T<T> const & rhs)
		{
			plane_.x() = rhs.x();
			plane_.y() = rhs.y();
			plane_.z() = rhs.z();
			plane_.w() = rhs.w();
			return *this;
		}

		// 三点确定面
		Plane_T(Vector3_T<T> const & pt_a, Vector3_T<T> const & pt_b, Vector3_T<T> const & pt_c)
		{
			Vector3_T<T> normal = Math::cross_product(pt_b - pt_a, pt_c - pt_a);
			normal.MakeNormalize();

			T d = -normal * pt_a;
			plane_ = Vector4_T(normal.x(), normal.y(), normal.z(), d);
		}

		// 法线和平面上一点
		Plane_T(Vector3_T<T> const & normal, Vector3_T<T> const & point)
		{
			Vector3_T<T> nor = normal;
			nor.MakeNormalize();

			T d = -nor * point;
			plane_ = Vector4_T(nor.x(), nor.y(), nor.z(), d);
		}

		Vector3_T<T> const Normal() const
		{
			Vector3_T<T> normal(this->a(), this->b(), this->c());
			//normal().MakeNormalize();
			return normal;
		}

		T GetDistance(Vector3_T<T> const & p) const
		{
			return ( Math::dot_product(this->Normal(), p) + this->d() );
		}

		void MakeNormalize()
		{
			*this = Math::normalize(*this);
		}

		bool operator == (Plane_T<T> const & rhs)
		{
			return plane_ == rhs.plane_;
		}

		std::pair<bool,T> Intersects(Ray_T<T> const & rhs) const
		{
			return Math::intersect(rhs, *this);
		}

		bool Intersects(Sphere_T<T> const & rhs) const
		{
			return Math::intersect(rhs, *this);
		}

		BoundIntersection Intersects(AABBox_T<T> const & rhs) const
		{
			return Math::intersect(*this, rhs);
		}

	private:
		Vector4_T<T> plane_;
	};

	typedef Plane_T<float> Plane;
}

#endif // Forge_Plane_hpp__
