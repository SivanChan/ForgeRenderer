/********************************************************************
	created:	2013/04/16
	created:	16:4:2013   20:57
	filename: 	Vector4.hpp
	author:		Sivan
	purpose:	四维向量模板
*********************************************************************/

#ifndef Vector4_hpp__
#define Vector4_hpp__

#pragma once

namespace Forge
{
	template<typename T>
	class Vector4_T
	{
	public:
		typedef T                  value_type;
		typedef Vector4_T<T>       this_type;
		typedef value_type &       reference;
		typedef value_type const & const_reference;

		template<typename U>
		friend class Vector4_T;

	public:
		Vector4_T() : x_(T(0)), y_(T(0)), z_(T(0)), w_(T(0))
		{
		}

		explicit Vector4_T(T const & x, T const & y, T const & z, T const & w)
			: x_(x), y_(y), z_(z), w_(w)
		{
		}

		template<typename U>
		explicit Vector4_T(U const * rhs)
			: x_(rhs[0]), y_(rhs[1]), z_(rhs[2]), w_(rhs[3])
		{
		}

		template<typename U>
		explicit Vector4_T(Vector4_T<U> const & rhs)
			: x_(rhs.x_), y_(rhs.y_), z_(rhs.z_), w_(rhs.w_)
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

		reference w()
		{
			return w_;
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

		const_reference w() const
		{
			return w_;
		}

		// 操作符
		// ==
		template<typename U>
		bool operator == (Vector4_T<U> const & rhs) const
		{
			return (x_ == rhs.x_ && y_ == rhs.y_ && z_ == rhs.z_ && w_ == rhs.w_);
		}
		// !=
		template<typename U>
		bool operator != (Vector4_T<U> const & rhs) const
		{
			return !(operator == (rhs));
		}
		// =
		template<typename U>
		this_type const & operator = (Vector4_T<U> const & rhs)
		{
			if (this != &rhs)
			{
				x_ = rhs.x_;
				y_ = rhs.y_;
				z_ = rhs.z_;
				w_ = rhs.w_;
			}
			return *this;
		}
		// +=
		template<typename U>
		this_type const & operator += (Vector4_T<U> const & rhs)
		{
			x_ += rhs.x_;
			y_ += rhs.y_;
			z_ += rhs.z_;
			w_ += rhs.w_;
			return *this;
		}
		// -=
		template<typename U>
		this_type const & operator -= (Vector4_T<U> const & rhs)
		{
			x_ -= rhs.x_;
			y_ -= rhs.y_;
			z_ -= rhs.z_;
			w_ -= rhs.w_;
			return *this;
		}
		// *=
		this_type const & operator *= (T const & rhs)
		{
			x_ *= rhs;
			y_ *= rhs;
			z_ *= rhs;
			w_ *= rhs;
			return *this;
		}
		template<typename U>
		this_type const & operator *= (Vector4_T<U> const & rhs)
		{
			x_ *= rhs.x_;
			y_ *= rhs.y_;
			z_ *= rhs.z_;
			w_ *= rhs.w_;
			return *this;
		}

		// /=
		template<typename U>
		this_type const & operator /= (U const & rhs)
		{
			return this->operator *= (1.0f / rhs);
		}
		template<typename U>
		this_type const & operator /= (Vector4_T<U> const & rhs)
		{
			x_ /= rhs.x_;
			y_ /= rhs.y_;
			z_ /= rhs.z_;
			w_ /= rhs.w_;
			return *this;
		}

		// 一元操作符
		this_type const operator + () const
		{
			return *this;
		}
		this_type const operator - () const
		{
			return this_type(-x_, -y_, -z_, -w_);
		}

		// 二元操作符
		// +
		template<typename U>
		this_type const operator + (Vector4_T<U> const & rhs) const
		{
			return this_type(x_ + rhs.x_, y_ + rhs.y_, z_ + rhs.z_, w_ + rhs.w_);
		}
		// -
		template<typename U>
		this_type const operator - (Vector4_T<U> const & rhs) const
		{
			return this_type(x_ - rhs.x_, y_ - rhs.y_, z_ - rhs.z_, w_ - rhs.w_);
		}
		// *
		template<typename U>
		this_type const operator * (U const rhs) const
		{
			return this_type(static_cast<T>(x_*rhs), static_cast<T>(y_*rhs), static_cast<T>(z_*rhs), static_cast<T>(w_*rhs));
		}
		template<typename U>
		this_type const operator * (Vector4_T<U> const & rhs) const
		{
			return this_type(x_ * rhs.x_, y_ * rhs.y_, z_ * rhs.z_, w_ * rhs.w_);
		}

		// /
		template<typename U>
		this_type const operator / (U const rhs) const
		{
			return this->operator *(1.0f / rhs)
		}
		template<typename U>
		this_type const operator / (Vector4_T<U> const & rhs) const
		{
			return this_type(x_ / rhs.x_, y_ / rhs.y_, z_ / rhs.z_, w_ / rhs.w_);
		}

		reference operator [] (size_t const i)
		{
			assert( i < 4 );
			return *(&x_ + i);
		}

		const_reference operator [] (size_t const i) const
		{
			assert( i < 4 );
			return *(&x_ + i);
		}

		inline bool operator < (Vector4_T const & rhs) const
		{
			if ( x_ < rhs.x_ && y_ < rhs.y_ && z_ < rhs.z_ && w_ < rhs.w_ )
				return true;
			return false;
		}

		inline bool operator <= (Vector4_T const & rhs) const
		{
			if ( x_ <= rhs.x_ && y_ <= rhs.y_ && z_ <= rhs.z_ && w_ <= rhs.w_ )
				return true;
			return false;
		}

		inline bool operator > (Vector4_T const & rhs) const
		{
			if ( x_ > rhs.x_ && y_ > rhs.y_ && z_ > rhs.z_ && w_ > rhs.w_ )
				return true;
			return false;
		}

		inline bool operator >= (Vector4_T const & rhs) const
		{
			if ( x_ >= rhs.x_ && y_ >= rhs.y_ && z_ >= rhs.z_ && w_ >= rhs.w_ )
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

		void Assign(T const & x, T const & y, T const & z, T const & w)
		{
			x_ = x; y_ = y; z_ = z; w_ = w;
		}

		void MakeZero()
		{
			x_ = T(0);
			y_ = T(0);
			z_ = T(0);
			w_ = T(0);
		}

		void MakeNormalize()
		{
			*this = Math::normalize(*this);
		}

		void MakeCeil(Vector4_T const & rhs)
		{
			if ( rhs.x_ > x_ ) x_ = rhs.x_;
			if ( rhs.y_ > y_ ) y_ = rhs.y_;
			if ( rhs.z_ > z_ ) z_ = rhs.z_;
			if ( rhs.w_ > w_ ) w_ = rhs.w_;
		}

		void MakeFloor(Vector4_T const & rhs)
		{
			if ( rhs.x_ < x_ ) x_ = rhs.x_;
			if ( rhs.y_ < y_ ) y_ = rhs.y_;
			if ( rhs.z_ < z_ ) z_ = rhs.z_;
			if ( rhs.w_ < w_ ) w_ = rhs.w_;
		}

		void Swap(Vector4_T & rhs)
		{
			std::swap(this->x_, rhs.x_);
			std::swap(this->y_, rhs.y_);
			std::swap(this->z_, rhs.z_);
			std::swap(this->w_, rhs.w_);
		}

	private:
		T x_, y_, z_, w_;
	};

	typedef Vector4_T<int32_t>  int4;
	typedef Vector4_T<uint32_t> uint4;
	typedef Vector4_T<float>    float4;
	typedef Vector4_T<double>   double4;
}

#endif // Vector4_hpp__