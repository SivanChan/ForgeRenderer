/********************************************************************
	created:	2014/05/11
	created:	2014/5/11   22:07
	filename: 	Sphere.hpp
	author:		Sivan
	purpose:	ÇòÌå
*********************************************************************/

#ifndef Forge_Sphere_hpp__
#define Forge_Sphere_hpp__

#pragma once

#include <Math/Vector3.hpp>

namespace Forge
{
	template<typename T>
	class Sphere_T
	{
	public:
		typedef T                  value_type;
		typedef value_type &       reference;
		typedef value_type const & const_reference;

	public:
		Sphere_T()
		{
		}

		Sphere_T(Vector3_T<T> const & center, T const & radius)
			: center_(center), radius_(radius)
		{
		}

		Vector3_T<T> & Center()
		{
			return center_;
		}

		Vector3_T<T> const & Center() const
		{
			return center_;
		}

		T & Radius()
		{
			return radius_;
		}

		T const & Radius() const
		{
			return radius_;
		}

		bool Intersects(Vector3_T<T> const & rhs) const
		{
			return Math::intersect(*this, rhs);
		}		

		bool Intersects(Sphere_T<T> const & s) const
		{
			return Math::intersect(*this, s);
		}

		bool Intersects(Plane_T<T> const & p) const
		{
			return Math::intersect(*this, p);
		}

		bool Intersects(AABBox_T<T> const & b) const
		{
			return Math::intersect(*this, b);
		}

		BoundIntersection Intersects(Frustum_T<T> const & f) const
		{
			return Math::intersect(*this, f);
		}

		bool operator == (Sphere_T const & rhs)
		{
			return (center_ == rhs.center_) && (radius_ == rhs.radius_);
		}

	private:
		Vector3_T<T> center_;
		T            radius_;
	};

	typedef Sphere_T<float> Sphere;
}

#endif // Forge_Sphere_hpp__
