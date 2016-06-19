/********************************************************************
	created:	2013/03/19
	created:	19:3:2013   12:44
	filename: 	Vector3.hpp
	author:		Sivan
	purpose:	三维向量模板
*********************************************************************/

#ifndef Vector3_hpp__
#define Vector3_hpp__

#pragma once

namespace Forge
{
	template<typename T>
	class Vector3_T
	{
	public:
		typedef T                  value_type;
		typedef Vector3_T<T>       this_type;
		typedef value_type &       reference;
		typedef value_type const & const_reference;

		template<typename U>
		friend class Vector3_T;

	public:
		Vector3_T() : x_(T(0)), y_(T(0)), z_(T(0))
		{
		}

		explicit Vector3_T(T const & x, T const & y, T const & z)
			: x_(x), y_(y), z_(z)
		{
		}

		template<typename U>
		explicit Vector3_T(U const * rhs)
			: x_(rhs[0]), y_(rhs[1]), z_(rhs[2])
		{
		}

		template<typename U>
		explicit Vector3_T(Vector3_T<U> const & rhs)
			: x_(rhs.x_), y_(rhs.y_), z_(rhs.z_)
		{
		}

		reference x()
		{
			return x_;
		}

		reference y()
		{
			return y_;
		}

		reference z()
		{
			return z_;
		}
		 
		const_reference x() const
		{
			return x_;
		}

		const_reference y() const
		{
			return y_;
		}

		const_reference z() const
		{
			return z_;
		}

		// 操作符
		// ==
		template<typename U>
		bool operator == (Vector3_T<U> const & rhs) const
		{
			return (x_ == rhs.x_ && y_ == rhs.y_ && z_ == rhs.z_);
		}
		// !=
		template<typename U>
		bool operator != (Vector3_T<U> const & rhs) const
		{
			return !(operator == (rhs))
		}
		// =
		template<typename U>
		this_type const & operator = (Vector3_T<U> const & rhs)
		{
			if (this != &rhs)
			{
				x_ = rhs.x_;
				y_ = rhs.y_;
				z_ = rhs.z_;
			}
			return *this;
		}
		// +=
		template<typename U>
		this_type const & operator += (Vector3_T<U> const & rhs)
		{
			x_ += rhs.x_;
			y_ += rhs.y_;
			z_ += rhs.z_;
			return *this;
		}
		// -=
		template<typename U>
		this_type const & operator -= (Vector3_T<U> const & rhs)
		{
			x_ -= rhs.x_;
			y_ -= rhs.y_;
			z_ -= rhs.z_;
			return *this;
		}
		// *=
		this_type const & operator *= (T const & rhs)
		{
			x_ *= rhs;
			y_ *= rhs;
			z_ *= rhs;
			return *this;
		}
		template<typename U>
		this_type const & operator *= (Vector3_T<U> const & rhs)
		{
			x_ *= rhs.x_;
			y_ *= rhs.y_;
			z_ *= rhs.z_;
			return *this;
		}

		// /=
		template<typename U>
		this_type const & operator /= (U const & rhs)
		{
			return this->operator *= (1.0f / rhs);
		}
		template<typename U>
		this_type const & operator /= (Vector3_T<U> const & rhs)
		{
			x_ /= rhs.x_;
			y_ /= rhs.y_;
			z_ /= rhs.z_;
			return *this;
		}

		// 一元操作符
		this_type const operator + () const
		{
			return *this;
		}
		this_type const operator - () const
		{
			return this_type(-x_, -y_, -z_);
		}

		// 二元操作符
		// +
		template<typename U>
		this_type const operator + (Vector3_T<U> const & rhs) const
		{
			return this_type(x_ + rhs.x_, y_ + rhs.y_, z_ + rhs.z_);
		}
		// -
		template<typename U>
		this_type const operator - (Vector3_T<U> const & rhs) const
		{
			return this_type(x_ - rhs.x_, y_ - rhs.y_, z_ - rhs.z_);
		}
		// *
		template<typename U>
		this_type const operator * (U const rhs) const
		{
			return this_type(static_cast<T>(x_*rhs), static_cast<T>(y_*rhs), static_cast<T>(z_*rhs));
		}

		template<typename U>
		this_type const operator * (Vector3_T<U> const & rhs) const
		{
			return this_type(x_ * rhs.x_, y_ * rhs.y_, z_ * rhs.z_);
		}
		// /
		template<typename U>
		this_type const operator / (U const rhs) const
		{
			return this->operator * (1.0f / rhs);
		}
		template<typename U>
		this_type const operator / (Vector3_T<U> const & rhs) const
		{
			return this_type(x_ / rhs.x_, y_ / rhs.y_, z_ / rhs.z_);
		}

		reference operator [] (size_t const i)
		{
			assert( i < 3 );
			return *(&x_ + i);
		}

		const_reference operator [] (size_t const i) const
		{
			assert( i < 3 );
			return *(&x_ + i);
		}

		inline bool operator < (Vector3_T const & rhs) const
		{
			if ( x_ < rhs.x_ && y_ < rhs.y_ && z_ < rhs.z_ )
				return true;
			return false;
		}

		inline bool operator <= (Vector3_T const & rhs) const
		{
			if ( x_ <= rhs.x_ && y_ <= rhs.y_ && z_ <= rhs.z_ )
				return true;
			return false;
		}

		inline bool operator > (Vector3_T const & rhs) const
		{
			if ( x_ > rhs.x_ && y_ > rhs.y_ && z_ > rhs.z_ )
				return true;
			return false;
		}

		inline bool operator >= (Vector3_T const & rhs) const
		{
			if ( x_ >= rhs.x_ && y_ >= rhs.y_ && z_ >= rhs.z_ )
				return true;
			return false;
		}

		T * ptr()
		{
			return &x_;
		}

		T const * ptr() const
		{
			return &x_;
		}

		void Assign(T const & x, T const & y, T const & z)
		{
			x_ = x; y_ = y; z_ = z;
		}

		void MakeZero()
		{
			x_ = T(0);
			y_ = T(0);
			z_ = T(0);
		}

		void MakeNormalize()
		{
			*this = Math::normalize(*this);
		}

		void MakeCeil(Vector3_T const & rhs)
		{
			if ( rhs.x_ > x_ ) x_ = rhs.x_;
			if ( rhs.y_ > y_ ) y_ = rhs.y_;
			if ( rhs.z_ > z_ ) z_ = rhs.z_;
		}

		void MakeFloor(Vector3_T const & rhs)
		{
			if ( rhs.x_ < x_ ) x_ = rhs.x_;
			if ( rhs.y_ < y_ ) y_ = rhs.y_;
			if ( rhs.z_ < z_ ) z_ = rhs.z_;
		}

		void Swap(Vector3_T & rhs)
		{
			std::swap(this->x_, rhs.x_);
			std::swap(this->y_, rhs.y_);
			std::swap(this->z_, rhs.z_);
		}

		static this_type const & ZERO()
		{
			static Vector3_T const out(0, 0, 0);
			return out;
		}

		static this_type const & UINT_X()
		{
			static Vector3_T const out(1.0, 0, 0);
			return out;
		}

		static this_type const & UINT_Y()
		{
			static Vector3_T const out(0, 1.0, 0);
			return out;
		}

		static this_type const & UINT_Z()
		{
			static Vector3_T const out(0, 0, 1.0);
			return out;
		}

	private:
		T x_,y_,z_;
	};

	typedef Vector3_T<int32_t>  int3;
	typedef Vector3_T<uint32_t> uint3;
	typedef Vector3_T<float>    float3;
	typedef Vector3_T<double>   double3;

	namespace Math
	{
		float3 const UINT_X = float3(1.0f, 0.0f, 0.0f);
		float3 const UINT_Y = float3(0.0f, 1.0f, 0.0f);
		float3 const UINT_Z = float3(0.0f, 0.0f, 1.0f);
	}
}

#endif // Vector3_hpp__