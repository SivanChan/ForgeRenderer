/********************************************************************
	created:	2013/11/06
	created:	6:11:2013   21:37
	filename: 	AABBox_T.hpp
	author:		Sivan	
	purpose:	Axia Aligned Bounding Box 
	            轴对齐矩形边界框 左手坐标系

				   6-----7		   y  z
				  /|    /|		   | /
				 / |   / |		   |/
				2-----3  |		   *------x
				|  4--|--5		  
				| /   | /		 
				|/    |/		
				0-----1
*********************************************************************/

#ifndef Forge_AABBox_hpp__
#define Forge_AABBox_hpp__

#pragma once

#include <Math/Vector3.hpp>

namespace Forge
{
	template<class T>
	class AABBox_T
	{
	public:
		AABBox_T() 
		{
			SetNull();
		}

		AABBox_T(Vector3_T<T> const & min, Vector3_T<T> const & max)
			: min_(min), max_(max)
		{
		}

		AABBox_T(AABBox_T<T> const & rhs)
			: min_(rhs.min_) , max_(rhs.max_)
		{
		}

		// 赋值
		AABBox_T<T> & operator = (AABBox_T<T> const & rhs)
		{
			if ( this != &rhs )
			{
				min_ = rhs.min_;
				max_ = rhs.max_;
			}
			return *this;
		}

		// 操作符  
		// < 的定义为this完全在rhs内部
		bool operator < (AABBox_T<T> const & rhs) const
		{
			return ( min_ > rhs.min_ && max_ < rhs.max_ );
		}

		bool operator <= (AABBox_T<T> const & rhs) const
		{
			return ( min_ >= rhs.min_ && max_ <= rhs.max_ );
		}

		bool operator > (AABBox_T<T> const & rhs) const
		{
			return ( min_ < rhs.min_ && max_ > rhs.max_ );
		}

		bool operator >= (AABBox_T<T> const & rhs) const
		{
			return ( min_ <= rhs.min_ && max_ >= rhs.max_ );
		}

		Vector3_T<T> const & Min() const
		{
			return min_;
		}

		Vector3_T<T> & Min()
		{
			return min_;
		}

		Vector3_T<T> const & Max() const
		{
			return max_;
		}

		Vector3_T<T> & Max()
		{
			return max_;
		}

		T Width() const
		{
			return max_.x() - min_.x();
		}

		T Height() const
		{
			return max_.y() - min_.y();
		}

		T Depth() const
		{
			return max_.z() - min_.z();
		}

		bool IsEmpty() const
		{
			return min_ == max_;
		}

		Vector3_T<T> Center() const
		{
			return (min_ + max_) * 0.5f;
		}

		Vector3_T<T> Size() const
		{
			return max_ - min_;
		}

		Vector3_T<T> HalfSize() const
		{
			return (max_ - min_) * 0.5f;
		}

		Vector3_T<T> Corner(uint8_t index) const
		{
			assert(index < 8);
			return Vector3_T<T>( (index & 1UL) ? max_.x() : min_.x(),
				(index & 2UL) ? max_.y() : min_.y(),
				(index & 4UL) ? max_.z() : min_.z() );
		}

		void Merge(AABBox_T<T> const & rhs)
		{
			max_.MakeCeil( rhs.max_ );
			min_.MakeFloor( rhs.min_ );
		}

		bool Intersects(AABBox_T<T> const & rhs) const
		{
			return Math::intersect( *this, rhs );
		}

		bool Intersects(Vector3_T<T> const & rhs) const
		{
			return Math::intersect( *this, rhs );
		}

		bool IsNull() const
		{
			return min_.x() == (std::numeric_limits<T>::max)();
		}

		void SetNull()
		{
			max_ = Vector3_T<T>(-(std::numeric_limits<T>::min)(), -(std::numeric_limits<T>::min)(), -(std::numeric_limits<T>::min)());
			min_ = Vector3_T<T>((std::numeric_limits<T>::max)(), (std::numeric_limits<T>::max)(), (std::numeric_limits<T>::max)());
		}

		bool IsInfinite() const
		{
			return max_.x() == (std::numeric_limits<T>::max)();
		}

		void SetInfinite()
		{
			min_ = Vector3_T<T>(-(std::numeric_limits<T>::min)(), -(std::numeric_limits<T>::min)(), -(std::numeric_limits<T>::min)());
			max_ = Vector3_T<T>((std::numeric_limits<T>::max)(), (std::numeric_limits<T>::max)(), (std::numeric_limits<T>::max)());
		}

	private:
		Vector3_T<T> min_;
		Vector3_T<T> max_;
	};

	typedef AABBox_T<float> AABBox;
}

#endif // Forge_AABBox_hpp__