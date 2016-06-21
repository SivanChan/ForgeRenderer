/********************************************************************
	created:	2014/05/17
	created:	2014/5/17   10:03
	filename: 	Quaternion.hpp
	author:		Sivan
	purpose:	四元数
				q = [cos(θ/2) sin(θ/2)n]
*********************************************************************/

#ifndef Forge_Quaternion_hpp__
#define Forge_Quaternion_hpp__

#pragma once

#include <Math/Vector4.hpp>

namespace Forge
{
	template<typename T>
	class Quaternion_T
	{
	public:
		typedef T               value_type;
		typedef Quaternion_T<T> this_type;

	public:
		Quaternion_T(T w, T x, T y, T z)
			: q_(x,y,z,w)
		{
		}

		explicit Quaternion_T(T const * rhs)
			: q_(rhs)
		{
		}

		Quaternion_T(Vector3_T<T> const & v, T s)
			: q_(v.x(), v.y(), v.z(), s)
		{
		}

		Quaternion_T(Quaternion_T const & rhs)
			: q_(rhs.q_)
		{
		}

		T & w()
		{
			return q_.w();
		}

		T const & w() const
		{
			return q_.w();
		}

		T & x()
		{
			return q_.x();
		}

		T const & x() const
		{
			return q_.x();
		}

		T & y()
		{
			return q_.y();
		}

		T const & y() const
		{
			return q_.y();
		}

		T & z()
		{
			return q_.z();
		}

		T const & z() const
		{
			return q_.z();
		}

		Vector3_T<T> v() const
		{
			return Vector3_T<T>(q_.x(), q_.y(), q_.z());
		}

		Quaternion_T const operator + () const
		{
			return *this;
		}

		Quaternion_T const operator - () const
		{
			return Quaternion_T(-q_);
		}

		Quaternion_T const operator + (Quaternion_T const & rhs) const
		{
			return Quaternion_T(q_ + rhs.q_);
		}

		Quaternion_T const operator - (Quaternion_T const & rhs)
		{
			return Quaternion_T(q_ - rhs.q_);
		}

		Quaternion_T const & operator += (Quaternion_T const & rhs)
		{
			q_ += rhs;
			return *this;
		}

		Quaternion_T const & operator -= (Quaternion_T const & rhs)
		{
			q_ -= rhs;
			return *this;
		}

		/*
			连接多个角位移
		*/
		Quaternion_T operator * (Quaternion_T const & rhs) const
		{
			return Math::cross_product( *this, rhs );
		}

		Quaternion_T operator * (T const rhs) const
		{
			//return Quaternion_T<T>( q_ * rhs );
			Quaternion_T out(Quaternion_T<T>::Identity());
			out.q_ = q_ * rhs;
			return out;
		}

		Quaternion_T const & operator *= (Quaternion_T const & rhs)
		{
			*this = Math::cross_product( *this, rhs );
			return *this;
		}

		Quaternion_T const & operator *= (T rhs)
		{
			q_ *= rhs;
			return *this;
		}

		Quaternion_T const & operator /= (T rhs)
		{
			assert( rhs != 0);
			q_ /= rhs;
			return *this;
		}

		bool operator == (Quaternion_T<T> const & rhs) const
		{
			return q_ == rhs.q_;
		}

		static Quaternion_T const & Identity()
		{
			static Quaternion_T const q(0, 0, 0, 1);
			return q;
		}

		void MakeNormalize()
		{
			*this = Math::normalize(*this);
		}

	private:
		Vector4_T<T> q_;
	};
	typedef Quaternion_T<float> Quaternion;
}

#endif // Forge_Quaternion_hpp__