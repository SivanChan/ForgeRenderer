/********************************************************************
	created:	2014/05/17
	created:	2014/5/17   10:00
	filename: 	Ray.hpp
	author:		Sivan
	purpose:	…‰œﬂ
*********************************************************************/

#ifndef Forge_Ray_hpp__
#define Forge_Ray_hpp__

#pragma once

namespace Forge
{
	template<typename T>
	class Ray_T
	{
	public:
		Ray_T()
			: origin_(0,0,0), direction_(0,0,1)
		{
		}

		Ray_T(Vector3_T<T> const & origin, Vector3_T<T> const & direction)
			: origin_(origin), direction_(direction)
		{
		}

		Ray_T(Ray_T const & rhs)
			: origin_(rhs.origin_), direction_(rhs.direction_)
		{
		}

		Vector3_T<T> & Origin()
		{
			return origin_;
		}

		Vector3_T<T> const & Origin() const
		{
			return origin_;
		}

		Vector3_T<T> & Direction()
		{
			return direction_;
		}

		Vector3_T<T> const & Direction() const
		{
			return direction_;
		}

		Vector3_T<T> GetPoint(T t) const
		{
			return Vector3_T<T>(origin_ + (direction_ * t));
		}

		Vector3_T<T> operator* (T t) const
		{
			return GetPoint(t);
		}

		std::pair<bool,T> Intersect(Plane_T<T> const & rhs) const
		{
			return Math::intersect( *this, rhs );
		}

		std::pair<bool,T> Intersect(Sphere_T<T> const & rhs) const
		{
			return Math::intersect( *this, rhs );
		}

		std::pair<bool,T> Intersect(AABBox_T<T> const & rhs) const
		{
			return Math::intersect( *this, rhs );
		}

	private:
		Vector3_T<T> origin_;
		Vector3_T<T> direction_;
	};

	typedef Ray_T<float> Ray;
}

#endif // Forge_Ray_hpp__