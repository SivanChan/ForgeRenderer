/********************************************************************
	created:	2014/05/17
	created:	2014/5/17   10:02
	filename: 	Frustum.hpp
	author:		Sivan	
	purpose:	½ØÍ·Ìå
				From¡¶Fast Extraction of viewing frustum planes from the world-view-projection matrix¡·
				http://dlwt.csdn.net/fd.php?i=829151500811855&s=30e61abcc393181aa09f0a9010bc6010
*********************************************************************/

#ifndef Forge_Frustum_hpp__
#define Forge_Frustum_hpp__

#pragma once

#include <array> 

namespace Forge
{
	template<typename T>
	class Frustum_T
	{
	public:
		enum FrustumPlane
		{
			FP_Near   = 0,
			FP_Far    = 1,
			FP_Left   = 2,
			FP_Right  = 3,
			FP_Top    = 4,
			FP_Bottom = 5
		};

		enum FrustumCorner
		{
			FC_LeftBottomNear  = 0,
			FC_RightBottomNear = 1,
			FC_LeftTopNear     = 2,
			FC_RightTopNear    = 3,
			FC_LeftBottomFar   = 4,
			FC_RightBottomFar  = 5,
			FC_LeftTopFar      = 6,
			FC_RightTopFar     = 7
		};

		/// view proj matrix
		void FromMatrix(Matrix4x4_T<T> const & mat);

		Plane_T<T> & Plane(FrustumPlane index)
		{
			return planes_[index];
		}

		Plane_T<T> const & Plane(FrustumPlane index) const
		{
			return planes_[index];
		}

		BoundIntersection Intersect(AABBox_T<T> const & rhs) const
		{
			return Math::intersect( *this, rhs );
		}

		BoundIntersection Intersect(Sphere_T<T> const & rhs) const
		{
			return Math::intersect( *this, rhs );
		}

		bool Intersect(Vector3_T<T> const & rhs) const
		{
			return Math::intersect( *this, rhs );
		}

	private:
		typedef std::array<Plane_T<T>,6> FrustumPlanes;
		FrustumPlanes planes_;

		typedef std::array<Vector3_T<T>,8> FrustumCorners;
		FrustumCorners corners_;
	};

	// DirectX mode
	template<typename T>
	void Frustum_T<T>::FromMatrix( Matrix4x4_T<T> const & mat )
	{
		Vector4_T<T> const & column1(mat.Column(0));
		Vector4_T<T> const & column2(mat.Column(1));
		Vector4_T<T> const & column3(mat.Column(2));
		Vector4_T<T> const & column4(mat.Column(3));

		planes_[FP_Near]   = column3;
		planes_[FP_Far]    = column4 - column3;
		planes_[FP_Left]   = column4 + column1;
		planes_[FP_Right]  = column4 - column1;
		planes_[FP_Top]    = column4 - column2;
		planes_[FP_Bottom] = column4 + column2;

		// normalize normals
		for (auto it = planes_.begin(); it != planes_.end(); ++it)
		{
			(*it).MakeNormalize();
		}
	}

	typedef Frustum_T<float> Frustum;
}

#endif // Forge_Frustum_hpp__
