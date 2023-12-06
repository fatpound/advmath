#pragma once

#include "Vec2.hpp"

namespace fatpound::math
{
	template <typename T>
	class Vec3 : public Vec2<T>
	{
	public:
		Vec3()
		{

		}
		Vec3(const Vec3<T>& vec)
			:
			Vec3<T>(vec.x, vec.y, vec.z)
		{

		}

		Vec3(T in_x, T in_y, T in_z)
			:
			Vec2<T>(in_x, in_y),
			z(in_z)
		{

		}


	public:
		template <typename T2>
		explicit operator Vec3<T2>() const
		{
			return{ static_cast<T2>(this->x), static_cast<T2>(this->y), static_cast<T2>(z) };
		}

		Vec3<T>  GetNormalized() const
		{
			Vec3<T> norm = *this;

			norm.Normalize();

			return norm;
		}
		Vec3<T>  GetRotated(T angle) const
		{
			Vec3<T> vec(*this);

			vec.RotateBy(angle);

			return vec;
		}
		Vec3<T>& Normalize()
		{
			const T length = Len();

			this->x /= length;
			this->y /= length;
			z /= length;

			return *this;
		}
		Vec3<T>& RotateBy(T angle)
		{
			const T cosTheta = std::cos(angle);
			const T sinTheta = std::sin(angle);

			const T new_x = this->x * cosTheta - this->y * sinTheta;

			this->y = this->x * sinTheta + this->y * cosTheta;
			this->x = new_x;

			return *this;
		}

		T LenSq() const
		{
			return fatpound::math::sq( *this );
		}
		T Len() const
		{
			return static_cast<T>(std::sqrt(LenSq()));
		}

		T        operator *  (const Vec3<T>& rhs) const
		{
			return this->x * rhs.x + this->y * rhs.y + z * rhs.z;
		}
		Vec3<T>  operator -  ()                const
		{
			return Vec3<T>(-this->x, -this->y, -z);
		}

		Vec3<T>  operator +  (const Vec3<T>& rhs) const
		{
			Vec3<T> vec(*this);

			vec += rhs;

			return vec;
		}
		Vec3<T>  operator -  (const Vec3<T>& rhs) const
		{
			Vec3<T> vec(*this);

			vec -= rhs;

			return vec;
		}
		Vec3<T>  operator *  (const      T & rhs) const
		{
			Vec3<T> vec(*this);

			vec *= rhs;

			return vec;
		}
		Vec3<T>  operator /  (const      T & rhs) const
		{
			Vec3<T> vec(*this);

			vec /= rhs;

			return vec;
		}
		Vec3<T>  operator %  (const Vec3<T>& rhs) const
		{
			return Vec3<T>(
				this->y * rhs.z - this->z * rhs.y,
				this->z * rhs.x - this->x * rhs.z,
				this->x * rhs.y - this->y * rhs.x
			);
		}

		Vec3<T>& operator  = (const Vec3<T> rhs)
		{
			this->x = rhs.x;
			this->y = rhs.y;
			z = rhs.z;

			return *this;
		}
		Vec3<T>& operator += (const Vec3<T>& rhs)
		{
			this->x += rhs.x;
			this->y += rhs.y;
			z += rhs.z;

			return *this;
		}
		Vec3<T>& operator -= (const Vec3<T>& rhs)
		{
			this->x -= rhs.x;
			this->y -= rhs.y;
			z -= rhs.z;

			return *this;
		}
		Vec3<T>& operator *= (const      T & rhs)
		{
			this->x *= rhs;
			this->y *= rhs;
			z *= rhs;

			return *this;
		}
		Vec3<T>& operator /= (const      T & rhs)
		{
			this->x /= rhs;
			this->y /= rhs;
			z /= rhs;

			return *this;
		}

		bool  operator == (const Vec3<T>& rhs) const
		{
			return this->x == rhs.x && this->y == rhs.y;
		}
		bool  operator != (const Vec3<T>& rhs) const
		{
			return !(*this == rhs);
		}


	public:
		T z;


	protected:


	private:
	};

	typedef Vec3<int>    Vei3;
	typedef Vec3<float>  Vef3;
	typedef Vec3<double> Ved3;
}