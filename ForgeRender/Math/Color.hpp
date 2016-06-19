/********************************************************************
	created:	2013/04/16
	created:	16:4:2013   21:42
	filename: 	Color.hpp
	author:		Sivan
	
	purpose:	ÑÕÉ«
*********************************************************************/

#ifndef Color_hpp__
#define Color_hpp__

#pragma once

#include <Math/Vector4.hpp>

namespace Forge
{
	template<typename T>
	class Color_T
	{
	public:
		typedef T                  value_type;
		typedef Color_T<T>         this_type;
		typedef value_type &       reference;
		typedef value_type const & const_reference;

	public:
		Color_T()
		{
		}

		explicit Color_T(T const * rhs) 
			: color_(rhs[0], rhs[1], rhs[2], rhs[3])
		{
		}

		Color_T(Vector4_T<T> const & rhs) 
			: color_(rhs)
		{
		}

		Color_T(Color_T const & rhs)
			: color_(rhs.color_)
		{
		}

		Color_T(T const & r, T const & g, T const & b, T const & a)
			: color_(r, g, b, a)
		{
		}

		reference r() { return color_.x(); }
		const_reference r() const { return color_.x(); }
		
		reference g() { return color_.y(); }
		const_reference g() const { return color_.y(); }

		reference b() { return color_.z(); }
		const_reference b() const { return color_.z(); }

		reference a() { return color_.w(); }
		const_reference a() const { return color_.w(); }

		void RGBA(uint8_t & r, uint8_t & g, uint8_t & b, uint8_t & a) const
		{
			r = static_cast<uint8_t>(Math::clamp(color_.x(), 0.0f, 1.0f) * 255 + 0.5f );
			g = static_cast<uint8_t>(Math::clamp(color_.y(), 0.0f, 1.0f) * 255 + 0.5f );
			b = static_cast<uint8_t>(Math::clamp(color_.z(), 0.0f, 1.0f) * 255 + 0.5f );
			a = static_cast<uint8_t>(Math::clamp(color_.w(), 0.0f, 1.0f) * 255 + 0.5f );
		}

		uint32_t ARGB() const
		{
			uint8_t r, g, b, a;
			this->RGBA(r, g, b, a);
			return (a << 24) | (r << 16) | (g << 8) | (b << 0);
		}

		uint32_t ABGR() const
		{
			uint8_t r, g, b, a;
			this->RGBA(r, g, b, a);
			return (a << 24) | (b << 16) | (g << 8) | (r << 0);
		}

		uint32_t RGBA() const
		{
			uint8_t r, g, b, a;
			this->RGBA(r, g, b, a);
			return (r << 24) | (g << 16) | (b << 8) | (a << 0);
		}

		uint32_t BGRA() const
		{
			uint8_t r, g, b, a;
			this->RGBA(r, g, b, a);
			return (b << 24) | (g << 16) | ( r << 8) | (a << 0);
		}

		Color_T operator + (Color_T const & rhs) const
		{
			return Color_T(this->color_ + rhs.color_);
		}

		Color_T operator - (Color_T const & rhs) const
		{
			return Color_T(this->color_ - rhs.color_);
		}

		template<typename T>
		Color_T operator * (T const rhs) const
		{
			return Color_T(this->color_ * rhs);
		}

		template<typename T>
		Color_T operator / (T const rhs) const
		{
			return this->operator * (1.0f / rhs);
		}

		Color_T & operator = (Color_T const & rhs)
		{
			if (this != &rhs)
			{
				this->color_ = rhs.color_;
			}
			return *this;
		}

		Color_T & operator += (Color_T const & rhs)
		{
			color_ += rhs.color_;
			return *this;
		}

		Color_T & operator -= (Color_T const & rhs)
		{
			color_ -= rhs.color_;
			return *this;
		}

		Color_T & operator *= (T const & rhs)
		{
			color_ *= rhs;
			return *this;
		}

		Color_T & operator /= (T const & rhs)
		{
			color_ /= rhs;
			return *this;
		}

		bool operator == (Color_T const & rhs)
		{
			return color_ == rhs.color_;
		}

		bool operator != (Color_T const & rhs)
		{
			return color_ != rhs.color_;
		}

		Color_T const operator +() const
		{
			return *this;
		}

		Color_T const operator -() const
		{
			return Color_T(-color_);
		}
		
	private:
		Vector4_T<T> color_;
	};

	typedef Color_T<float> Color;
}

#endif // Color_hpp__