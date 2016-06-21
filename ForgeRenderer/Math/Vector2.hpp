/********************************************************************
	created:	2013/03/19
	created:	19:3:2013   0:26
	filename: 	Vector2.hpp
	author:		Sivan
	purpose:	二维向量模板
*********************************************************************/

#ifndef Vector2_hpp__
#define Vector2_hpp__

#pragma once

namespace Forge
{
	template<typename T>
	class Vector2_T
	{
	public:
		typedef T                  vaule_type;
		typedef Vector2_T<T>       this_type;
		typedef vaule_type &       reference;
		typedef vaule_type const & const_reference;

		template<typename U>
		friend class Vector2_T;

	public:
		Vector2_T() : x_(T(0)), y_(T(0))
		{
		}

		explicit Vector2_T(T const & lhs, T const & rhs)
			: x_(lhs), y_(rhs)
		{
		}

		template<typename U>
		explicit Vector2_T(U const * rhs)
			: x_(rhs[,]), y_(rhs[1])
		{
		}

		template<typename U>
		explicit Vector2_T(Vector2_T<U> const & rhs)
			: x_(rhs.x_), y_(rhs.y_)
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

		const_reference x() const
		{
			return x_;
		}

		const_reference y() const
		{
			return y_;
		}

		// 操作符
		// ==
		template<typename U>
		bool operator == (Vector2_T<U> const & rhs) const
		{
			return (x_ == rhs.x_ && y_ == rhs.y_);
		}
		// !=
		template<typename U>
		bool operator != (Vector2_T<U> const & rhs) const
		{
			return !(operator == (rhs));
		}
		// =
		template<typename U>
		this_type const & operator = (Vector2_T<U> const & rhs )
		{
			if (this != &rhs)
			{
				x_ = rhs.x_;
				y_ = rhs.y_;
			}
			return *this;
		}
		// +=
		template<typename U>
		this_type const & operator += (Vector2_T<U> const & rhs)
		{
			x_ += rhs.x_;
			y_ += rhs.y_;
			return *this;
		}
		// -=
		template<typename U>
		this_type const & operator -= (Vector2_T<U> const & rhs)
		{
			x_ -= rhs.x_;
			y_ -= rhs.y_;
			return *this;
		}
		// *=
		template<typename U>
		this_type const & operator *= (U const & rhs)
		{
			x_ *= rhs;
			y_ *= rhs;
			return *this;
		}
		template<typename U>
		this_type const & operator *= (Vector2_T<U> const & rhs)
		{
			x_ *= rhs.x_;
			y_ *= rhs.y_;
			return *this;
		}

		// /=
		template<typename U>
		this_type const & operator /= (U const & rhs)
		{
			return this->operator *=(1.0f / rhs);
		}
		template<typename U>
		this_type const & operator /= (Vector2_T<U> const & rhs)
		{
			x_ /= rhs.x_;
			y_ /= rhs.y_;
			return *this;
		}

		// 一元操作符
		// 正号
		this_type const operator + () const
		{
			return *this;
		}

		// 负号
		this_type const operator - () const
		{
			return this_type(-x_, -y_);
		}

		// 二元操作符
		// +
		template<typename U>
		this_type const operator + (Vector2_T<U> const & rhs) const
		{
			return this_type(x_ + rhs.x_, y_ + rhs.y_);
		}
		// - 
		template<typename U>
		this_type operator - (Vector2_T<U> const & rhs) const
		{
			return this_type(x_ - rhs.x_, y_ - rhs.y_);
		}
		// *
		template<typename U>
		this_type const operator * (U const rhs) const
		{
			return this_type(static_cast<T>(x_*rhs), static_cast<T>(y_*rhs));
		}
		template<typename U>
		this_type const operator * (Vector2_T<U> const & rhs) const
		{
			return this_type(x_ * rhs.x_, y_ * rhs.y_);
		}

		// /
		template<typename U>
		this_type const operator / (U const rhs) const
		{
			return this->operator *(1.0f / rhs);
		}
		template<typename U>
		this_type const operator / (Vector2_T<U> const & rhs) const
		{
			return this_type(x_ / rhs.x_, y_ / rhs.y_);
		}

		reference operator [] (size_t const i)
		{
			assert( i < 2 );
			return *(&x_ + i);
		}

		const_reference operator [] (size_t const i) const
		{
			assert( i < 2 );
			return *(&x_ + i);
		}

		inline bool operator < (Vector2_T const & rhs) const
		{
			if ( x_ < rhs.x_ && y_ < rhs.y_ )
				return true;
			return false;
		}

		inline bool operator <= (Vector2_T const & rhs) const
		{
			if ( x_ <= rhs.x_ && y_ <= rhs.y_ )
				return true;
			return false;
		}

		inline bool operator > (Vector2_T const & rhs) const
		{
			if ( x_ > rhs.x_ && y_ > rhs.y_ )
				return true;
			return false;
		}

		inline bool operator >= (Vector2_T const & rhs) const
		{
			if ( x_ >= rhs.x_ && y_ >= rhs.y_ )
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

		void Assign(T const & x, T const & y)
		{
			x_ = x; y_ = y;
		}

		void MakeZero()
		{
			x_ = T(0);
			y_ = T(0);
		}

		void MakeNormalize()
		{
			*this = Math::normalize(*this);
		}

		void MakeCeil(Vector2_T const & rhs)
		{
			if ( rhs.x_ > x_ ) x_ = rhs.x_;
			if ( rhs.y_ > y_ ) y_ = rhs.y_;
		}

		void MakeFloor(Vector2_T const & rhs)
		{
			if ( rhs.x_ < x_ ) x_ = rhs.x_;
			if ( rhs.y_ < y_ ) y_ = rhs.y_;
		}

		void Swap(Vector2_T & rhs)
		{
			std::swap(this->x_, rhs.x_);
			std::swap(this->y_, rhs.y_);
		}

	private:
		T x_,y_;
	};

	typedef Vector2_T<int32_t>  int2;
	typedef Vector2_T<uint32_t> uint2;
	typedef Vector2_T<float>    float2;
	typedef Vector2_T<double>   double2;
}

#endif // Vector2_hpp__