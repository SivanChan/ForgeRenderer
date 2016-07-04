/********************************************************************
	created:	2014/05/11
	created:	2014/5/11   9:00
	filename: 	Size.hpp
	author:		Sivan
	purpose:	¾ØÐÎ³ß´ç
*********************************************************************/

#ifndef Forge_Size_hpp__
#define Forge_Size_hpp__

#pragma once

#include <Math/Vector2.hpp>

namespace Forge
{
	template<typename T>
	class Size_T
	{
	public:
		typedef T                  value_type;
		typedef Size_T<T>          this_type;
		typedef value_type &       reference;
		typedef value_type const & const_reference;

		template<typename U>
		friend class Size_T;

	public:
		Size_T()
		{
		}

		Size_T(T const & width, T const & height)
			: size_(width, height)
		{
		}

		Size_T(Vector2_T<T> const & rhs)
			: size_(rhs)
		{
		}

		explicit Size_T(T const * rhs)
			: size_(rhs)
		{
		}

		template<typename U>
		explicit Size_T(Size_T<U> const & rhs)
			: size_(rhs.size_)
		{
		}

		reference cx()
		{
			return size_.x();
		}

		const_reference cx() const
		{
			return size_.x();
		}

		reference cy()
		{
			return size_.y();
		}

		const_reference cy() const
		{
			return size_.y();
		}

		template<typename U>
		this_type & operator = (Size_T<U> const & rhs)
		{
			if (this != &rhs)
			{
				size_ = rhs.size_;
			}
			return *this;
		}

		template<typename U>
		this_type const & operator += (Size_T<U> const & rhs)
		{
			size_ += rhs.size_;
			return *this;
		}

		template<typename U>
		this_type operator + (Size_T<U> const & rhs) const
		{
			return Size_T(this->cx() + rhs.cx(), this->cy() + rhs.cy());
		}

		template<typename U>
		this_type const & operator -= (Size_T<U> const & rhs)
		{
			size_ -= rhs.size_;
			return *this;
		}

		template<typename U>
		this_type operator - (Size_T<U> const & rhs) const
		{
			return Size_T(this->cx() - rhs.cx(), this->cy() - rhs.cy());
		}

		this_type & operator /= (T const & rhs)
		{
			size_.x() /= rhs;
			size_.y() /= rhs;
			return *this;
		}

		this_type operator / (T const & rhs) const
		{
			return Size_T<T>(this->cx()/rhs, this->cy()/rhs);
		}

		this_type & operator *= (T const & rhs)
		{
			size_.x() *= rhs;
			size_.y() *= rhs;
			return *this;
		}

		this_type operator * (T const & rhs) const
		{
			return Size_T<T>(this->cx()*rhs, this->cy()*rhs);
		}

		bool operator == (Size_T<T> const & rhs) const
		{
			return size_ == rhs.size_;
		}

		bool operator != (Size_T<T> const & rhs) const
		{
			return size_ != rhs.size_;
		}

		this_type const operator+() const
		{
			return *this;
		}

		this_type const operator-() const
		{
			return Size_T<T>(-size_.x(), -size_.y());
		}

		T Aera() const
		{
			return size_.x() * size_.y();
		}

	private:
		Vector2_T<T> size_;
	};

	typedef Size_T<float> Size;
}

#endif // Forge_Size_hpp__
