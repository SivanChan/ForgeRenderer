/********************************************************************
	created:	2013/03/19
	created:	19:3:2013   12:48
	filename: 	Matrix4x4.hpp
	author:		Sivan
	purpose:	4¡Á4¾ØÕó
*********************************************************************/

#ifndef Matrix4x4_hpp__
#define Matrix4x4_hpp__

#pragma once

namespace Forge
{
	template<typename T>
	class Matrix4x4_T
	{
	public:
		typedef T            value_type;
		typedef Matrix4x4_T<T> this_type;
		typedef T &          reference;
		typedef T const &    const_reference;

		template<typename U>
		friend class Matrix4x4_T;

		enum { row_num = 4, col_num = 4 };
		enum { elem_num = row_num * col_num };

	public:
		Matrix4x4_T()
			: m11(0), m12(0), m13(0), m14(0), 
			  m21(0), m22(0), m23(0), m24(0),
			  m31(0), m32(0), m33(0), m34(0),
			  m41(0), m42(0), m43(0), m44(0)
		{
		}

		Matrix4x4_T(
			T _11, T _12, T _13, T _14,
			T _21, T _22, T _23, T _24,
			T _31, T _32, T _33, T _34,
			T _41, T _42, T _43, T _44 )
			: m11(_11), m12(_12), m13(_13), m14(_14),
			  m21(_21), m22(_22), m23(_23), m24(_24),
			  m31(_31), m32(_32), m33(_33), m34(_34),
			  m41(_41), m42(_42), m43(_43), m44(_44)
		{
		}

		template<typename U>
		explicit Matrix4x4_T(U const * rhs)
			: m11(rhs[0]),  m12(rhs[1]),  m13(rhs[2]),  m14(rhs[3]),
			  m21(rhs[4]),  m22(rhs[5]),  m23(rhs[6]),  m24(rhs[7]),
			  m31(rhs[8]),  m32(rhs[9]),  m33(rhs[10]), m34(rhs[11]),
			  m41(rhs[12]), m42(rhs[13]), m43(rhs[14]), m44(rhs[15])
		{
		}

		template<typename U>
		explicit Matrix4x4_T(Matrix4x4_T<U> const & rhs)
			: m11(rhs.m11), m12(rhs.m12), m13(rhs.m13), m14(rhs.m14),
			  m21(rhs.m21), m22(rhs.m22), m23(rhs.m23), m24(rhs.m24),
			  m31(rhs.m31), m32(rhs.m32), m33(rhs.m33), m34(rhs.m34),
			  m41(rhs.m41), m42(rhs.m43), m43(rhs.m43), m44(rhs.m44)
		{

		}

		// ²Ù×÷·û
		// ==
		template<typename U>
		bool operator == (Matrix4x4_T<U> const & rhs)
		{
			if (
				 m11 != rhs.m11 || m12 != rhs.m12 || m13 != rhs.m13 || m14 != rhs.m14 ||
				 m21 != rhs.m21 || m22 != rhs.m22 || m23 != rhs.m23 || m24 != rhs.m24 ||
				 m31 != rhs.m31 || m32 != rhs.m32 || m33 != rhs.m33 || m34 != rhs.m34 ||
				 m41 != rhs.m41 || m42 != rhs.m42 || m43 != rhs.m43 || m44 != rhs.m44
				)
			{
				return false;
			}
			return true;
		}
		// !=
		template<typename U>
		bool operator != (Matrix4x4_T<U> const & rhs)
		{
			return !(operator == (rhs));
		}
		// =
		template<typename U>
		this_type & operator = (Matrix4x4_T<U> const & rhs)
		{
			if (this != &rhs)
			{
				m11 = rhs.m11; m12 = rhs.m12; m13 = rhs.m13; m14 = rhs.m14;
				m21 = rhs.m21; m22 = rhs.m22; m23 = rhs.m23; m24 = rhs.m24;
				m31 = rhs.m31; m32 = rhs.m32; m33 = rhs.m33; m34 = rhs.m34;
				m41 = rhs.m41; m42 = rhs.m42; m43 = rhs.m43; m44 = rhs.m44;
			}
			return *this;
		}
		// +=
		template<typename U>
		this_type & operator += (Matrix4x4_T<U> const & rhs)
		{
			m11 += rhs.m11; m12 += rhs.m12; m13 += rhs.m13; m14 += rhs.m14;
			m21 += rhs.m21; m22 += rhs.m22; m23 += rhs.m23; m24 += rhs.m24;
			m31 += rhs.m31; m32 += rhs.m32; m33 += rhs.m33; m34 += rhs.m34;
			m41 += rhs.m41; m42 += rhs.m42; m43 += rhs.m43; m44 += rhs.m44;
			return *this;
		}
		// -=
		template<typename U>
		this_type & operator -= (Matrix4x4_T<U> const & rhs)
		{
			m11 -= rhs.m11; m12 -= rhs.m12; m13 -= rhs.m13; m14 -= rhs.m14;
			m21 -= rhs.m21; m22 -= rhs.m22; m23 -= rhs.m23; m24 -= rhs.m24;
			m31 -= rhs.m31; m32 -= rhs.m32; m33 -= rhs.m33; m34 -= rhs.m34;
			m41 -= rhs.m41; m42 -= rhs.m42; m43 -= rhs.m43; m44 -= rhs.m44;
			return *this;
		}
		// *=
		template<typename U>
		this_type & operator *= (U const & rhs)
		{
			m11 *= rhs; m12 *= rhs; m13 *= rhs; m14 *= rhs;
			m21 *= rhs; m22 *= rhs; m23 *= rhs; m24 *= rhs;
			m31 *= rhs; m32 *= rhs; m33 *= rhs; m34 *= rhs;
			m41 *= rhs; m42 *= rhs; m43 *= rhs; m44 *= rhs;
			return *this;
		}
		this_type & operator *= (Matrix4x4_T<T> const & rhs)
		{
			m11 = m11 * rhs.m11 + m12 * rhs.m21 + m13 * rhs.m31 + m14 * rhs.m41;
			m12 = m11 * rhs.m12 + m12 * rhs.m22 + m13 * rhs.m32 + m14 * rhs.m42;
			m13 = m11 * rhs.m13 + m12 * rhs.m23 + m13 * rhs.m33 + m14 * rhs.m43;
			m14 = m11 * rhs.m14 + m12 * rhs.m24 + m13 * rhs.m34 + m14 * rhs.m44;

			m21 = m21 * rhs.m11 + m22 * rhs.m21 + m23 * rhs.m31 + m24 * rhs.m41;
			m22 = m21 * rhs.m12 + m22 * rhs.m22 + m23 * rhs.m32 + m24 * rhs.m42;
			m23 = m21 * rhs.m13 + m22 * rhs.m23 + m23 * rhs.m33 + m24 * rhs.m43;
			m24 = m21 * rhs.m14 + m22 * rhs.m24 + m23 * rhs.m34 + m24 * rhs.m44;

			m31 = m31 * rhs.m11 + m32 * rhs.m21 + m33 * rhs.m31 + m34 * rhs.m41;
			m32 = m31 * rhs.m12 + m32 * rhs.m22 + m33 * rhs.m32 + m34 * rhs.m42;
			m33 = m31 * rhs.m13 + m32 * rhs.m23 + m33 * rhs.m33 + m34 * rhs.m43;
			m34 = m31 * rhs.m14 + m32 * rhs.m24 + m33 * rhs.m34 + m34 * rhs.m44;

			m41 = m41 * rhs.m11 + m42 * rhs.m21 + m43 * rhs.m31 + m44 * rhs.m41;
			m42 = m41 * rhs.m12 + m42 * rhs.m22 + m43 * rhs.m32 + m44 * rhs.m42;
			m43 = m41 * rhs.m13 + m42 * rhs.m23 + m43 * rhs.m33 + m44 * rhs.m43;
			m44 = m41 * rhs.m14 + m42 * rhs.m24 + m43 * rhs.m34 + m44 * rhs.m44;

			return *this;
		}
		// /=
		template<typename U>
		this_type & operator /= (U const & rhs)
		{
			return this->operator *= (1.0f / rhs);
		}

		// ÕıºÅ
		this_type const operator + () const
		{
			return *this;
		}
		// ¸ººÅ
		this_type const operator - () const
		{
			return this_type( -m11, -m12, -m13, -m14,
							  -m21, -m22, -m23, -m24,
							  -m31, -m32, -m33, -m34,
							  -m41, -m42, -m43, -m44);
		}
		// +
		template<typename U>
		this_type operator + (Matrix4x4_T<U> const & rhs) const
		{
			return this_type( m11 + rhs.m11, m12 + rhs.m12, m13 + rhs.m13, m14 + rhs.m14,
							  m21 + rhs.m21, m22 + rhs.m22, m23 + rhs.m23, m24 + rhs.m24,
							  m31 + rhs.m31, m32 + rhs.m32, m33 + rhs.m33, m34 + rhs.m34,
				              m41 + rhs.m41, m42 + rhs.m42, m43 + rhs.m43, m44 + rhs.m44 );
		}
		// -
		template<typename U>
		this_type operator - (Matrix4x4_T<U> const & rhs) const
		{
			return this_type( m11 - rhs.m11, m12 - rhs.m12, m13 - rhs.m13, m14 - rhs.m14,
							  m21 - rhs.m21, m22 - rhs.m22, m23 - rhs.m23, m24 - rhs.m24,
				              m31 - rhs.m31, m32 - rhs.m32, m33 - rhs.m33, m34 - rhs.m34,
				              m41 - rhs.m41, m42 - rhs.m42, m43 - rhs.m43, m44 - rhs.m44 );
		}
		// *
		template<typename U>
		this_type operator * (U const rhs) const
		{
			return this_type( m11 * rhs, m12 * rhs, m13 * rhs, m14 * rhs,
							  m21 * rhs, m22 * rhs, m23 * rhs, m24 * rhs,
							  m31 * rhs, m32 * rhs, m33 * rhs, m34 * rhs,
							  m41 * rhs, m42 * rhs, m43 * rhs, m44 * rhs );
		} 
		this_type operator * (Matrix4x4_T<T> const & rhs) const
		{
			return this_type(
				m11 * rhs.m11 + m12 * rhs.m21 + m13 * rhs.m31 + m14 * rhs.m41,
				m11 * rhs.m12 + m12 * rhs.m22 + m13 * rhs.m32 + m14 * rhs.m42,
				m11 * rhs.m13 + m12 * rhs.m23 + m13 * rhs.m33 + m14 * rhs.m43,
				m11 * rhs.m14 + m12 * rhs.m24 + m13 * rhs.m34 + m14 * rhs.m44,
				m21 * rhs.m11 + m22 * rhs.m21 + m23 * rhs.m31 + m24 * rhs.m41,
				m21 * rhs.m12 + m22 * rhs.m22 + m23 * rhs.m32 + m24 * rhs.m42,
				m21 * rhs.m13 + m22 * rhs.m23 + m23 * rhs.m33 + m24 * rhs.m43,
				m21 * rhs.m14 + m22 * rhs.m24 + m23 * rhs.m34 + m24 * rhs.m44,
				m31 * rhs.m11 + m32 * rhs.m21 + m33 * rhs.m31 + m34 * rhs.m41,
				m31 * rhs.m12 + m32 * rhs.m22 + m33 * rhs.m32 + m34 * rhs.m42,
				m31 * rhs.m13 + m32 * rhs.m23 + m33 * rhs.m33 + m34 * rhs.m43,
				m31 * rhs.m14 + m32 * rhs.m24 + m33 * rhs.m34 + m34 * rhs.m44,
				m41 * rhs.m11 + m42 * rhs.m21 + m43 * rhs.m31 + m44 * rhs.m41,
				m41 * rhs.m12 + m42 * rhs.m22 + m43 * rhs.m32 + m44 * rhs.m42,
				m41 * rhs.m13 + m42 * rhs.m23 + m43 * rhs.m33 + m44 * rhs.m43,
				m41 * rhs.m14 + m42 * rhs.m24 + m43 * rhs.m34 + m44 * rhs.m44
				);
		}
		// /
		template<typename U>
		this_type operator / (U const rhs) const
		{
			return this->operator * (1.0f / rhs);
		}

		reference operator()(size_t row, size_t col)
		{
			return m[row][col];
		}

		const_reference operator()(size_t row, size_t col) const
		{
			return m[row][col];
		}

		Vector4_T<T> const Row(size_t index) const
		{
			Vector4_T<T> result;
			for (size_t i = 0; i < index; ++i)
			{
				result[i] = m[index][i];
			}
			return result;
		}
	
		Vector4_T<T> const Column(size_t index) const
		{
			Vector4_T<T> result;
			for (size_t i = 0; i < index; ++i)
			{
				result[i] = m[i][index];
			}
			return result;
		}

		void MakeZero()
		{
			for (int i = 0; i != elem_num; ++i)
			{
				m_[i] = T(0);
			}
		}

		void MakeIdentity()
		{
			m11 = T(1); m12 = T(0); m13 = T(0); m14 = T(0);
			m21 = T(0); m22 = T(1); m23 = T(0); m24 = T(0);
			m31 = T(0); m32 = T(0); m33 = T(1); m34 = T(0);
			m41 = T(0); m42 = T(0); m43 = T(0); m44 = T(1);
		}

		static Matrix4x4_T const & Identity()
		{
			static Matrix4x4_T result(
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1 );
			return result;
		}

	private:
		union
		{
			struct 
			{
				T m11, m12, m13, m14;
				T m21, m22, m23, m24;
				T m31, m32, m33, m34;
				T m41, m42, m43, m44;
			};
			T m[row_num][col_num];
			T m_[elem_num];
		};
	};

	typedef Matrix4x4_T<int>    int4x4;
	typedef Matrix4x4_T<float>  float4x4;
	typedef Matrix4x4_T<double> double4x4;
}

#endif // Matrix4x4_hpp__