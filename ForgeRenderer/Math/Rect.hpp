/********************************************************************
	created:	2014/05/11
	created:	2014/5/11   10:20
	filename: 	Rect.hpp
	author:		Sivan
	purpose:	¾ØÐÎ
*********************************************************************/

#ifndef Forge_Rect_hpp__
#define Forge_Rect_hpp__

#pragma once

#include <Math/Vector4.hpp>
#include <Math/Size.hpp>

namespace Forge
{
	template<typename T>
	class Rect_T
	{
	public:
		typedef T                 value_type;
		typedef Rect_T<T>         this_type;
		typedef T &               reference;
		typedef T const &         const_reference;

		template<typename U>
		friend class Rect_T;

	public:
		Rect_T()
		{
		}

		Rect_T(T const & left, T const & top, T const & right, T const & bottom)
			: rect_(left,top,right,bottom)
		{
		}

		Rect_T(Rect_T<T> const & rhs)
			: rect_(rhs.rect_)
		{
		}

		explicit Rect_T(T const * rhs)
			: rect_(rhs)
		{
		}

		template<typename U>
		explicit Rect_T(Rect_T<U> const & rhs)
			: rect_(rhs.rect_)
		{
		}

		reference left()
		{
			return rect_.x();
		}

		const_reference left() const
		{
			return rect_.x();
		}

		reference top()
		{
			return rect_.y();
		}

		const_reference top() const
		{
			return rect_.y();
		}

		reference right()
		{
			return rect_.z();
		}

		const_reference right() const
		{
			return rect_.z();
		}

		reference bottom()
		{
			return rect_.w();
		}

		const_reference bottom() const
		{
			return rect_.w();
		}

		T Width() const
		{
			return (this->right() - this->left());
		}

		T Height() const
		{
			return (this->bottom() - this->top());
		}

		Size_T<T> const Size() const
		{
			return Size_T<T>(this->Width(), this->Height());
		}

		T Area() const
		{
			return Width() * Height();
		}

		Vector2_T<T> const Center() const
		{
			return Vector2_T<T>( (this->left() + this->right())/2.0,
				(this->top() + this->bottom())/2.0 );
		}

		bool IsValid() const
		{
			return ((this->right() >= this->left()) && (this->bottom() >= this->top()));
		}

		bool IsEmpty() const
		{
			return ((this->left() == this->right()) && (this->top() == this->bottom()));
		}

		bool IsPointInRect(Vector2_T<T> const & rhs) const
		{
			return ( Math::in_bound(rhs.x(), this->left(), this->right()) &&
				     Math::in_bound(rhs.y(), this->top(), this->bottom()) );
		}

		bool operator == (Rect_T<T> const & rhs) const
		{
			return rect_ == rhs.rect_;
		}

		bool operator != (Rect_T<T> const & rhs) const
		{
			return rect_ != rhs.rect_;
		}

		template<typename U>
		this_type & operator = (Rect_T<U> const & rhs)
		{
			if (this != &rhs)
			{
				rect_ = rhs.rect_;
			}
			return *this;
		}

		template<typename U>
		this_type const & operator &= (Rect_T<U> const & rhs)
		{
			this->left()   = std::max(this->left(), rhs.left());
			this->top()    = std::max(this->top(), rhs.top());
			this->right()  = std::min(this->right(), rhs.right());
			this->bottom() = std::min(this->bottom(), rhs.bottom());
			return *this;
		}

		template<typename U>
		this_type const & operator |= (Rect_T<U> const & rhs)
		{
			this->left()   = std::min(this->left(), rhs.left());
			this->top()    = std::min(this->top(), rhs.top());
			this->right()  = std::max(this->right(), rhs.right());
			this->bottom() = std::max(this->bottom(), rhs.bottom());
			return *this;
		}

		// Æ½ÒÆ
		template<typename U>
		this_type const & operator += (Vector2_T<U> const & rhs)
		{
			this->left()   += rhs.x();
			this->right()  += rhs.x();
			this->top()    += rhs.y();
			this->bottom() += rhs.y();
			return *this;
		}

		template<typename U>
		this_type operator + (Vector2_T<U> const & rhs) const
		{
			return Rect_T<T>(this->left() + rhs.x(), this->top() + rhs.y(),
				this->right() + rhs.x(), this->bottom() + rhs.y() );
		}

		template<typename U>
		this_type const & operator -= (Vector2_T<U> const & rhs)
		{
			this->left()   -= rhs.x();
			this->right()  -= rhs.x();
			this->top()    -= rhs.y();
			this->bottom() -= rhs.y();
			return *this;
		}

		template<typename U>
		this_type operator - (Vector2_T<U> const & rhs) const
		{
			return Rect_T<T>(this->left() - rhs.x(), this->top() - rhs.y(),
				this->right() - rhs.x(), this->bottom() - rhs.y() );
		}

		this_type const operator + () const
		{
			return *this;
		}

		this_type const operator - () const
		{
			return Rect_T<T>(-this->left(), -this->top(), -this->right(), -this->bottom());	
		}

		bool operator < (Rect_T<T> const & rhs) const
		{
			return this->Area() < rhs.Area();
		}

	private:
		Vector4_T<T> rect_;
	};

	typedef Rect_T<float> Rectf;
}

#endif // Forge_Rect_hpp__
