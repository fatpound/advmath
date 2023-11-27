#pragma once

#include "Vec2.hpp"

namespace fatpound::math
{
    template <typename T>
    class Vec3
    {
    public:
        Vec3(const Vec3& vec)
            :
            Vec3(vec.x, vec.y)
        {

        }

        Vec3(T in_x, T in_y)
            :
            x(in_x),
            y(in_y)
        {

        }
        Vec3(T in_x, T in_y, T in_w)
            :
            x(in_x),
            y(in_y),
            w(in_w)
        {

        }
        explicit Vec3(const Vec2<T>& v2)
            :
            Vec3(v2.x, v2.y)
        {

        }


    public:
        template <typename T2>
        explicit operator Vec3<T2>() const
        {
            return{ static_cast<T2>(x), static_cast<T2>(y) };
        }
        explicit operator Vec2<T>() const
        {
            return Vec2<T>{ x, y };
        }
        Vec3<T>& Normalize()
        {
            const T length = Len();

            x /= length;
            y /= length;

            return *this;
        }
        Vec3<T>& RotateBy(T angle)
        {
            const T cosTheta = std::cos(angle);
            const T sinTheta = std::sin(angle);

            const T new_x = x * cosTheta - y * sinTheta;

            y = x * sinTheta + y * cosTheta;
            x = new_x;

            return *this;
        }
        Vec3<T>  GetNormalized() const
        {
            Vec3<T> norm = *this;
            norm.Normalize();
            return norm;
        }
        Vec3<T>  GetRotated(T angle) const
        {
            return Vec3<T>(*this).RotateBy(angle);
        }

        T LenSq() const
        {
            return x * x + y * y;
        }
        T Len() const
        {
            return std::sqrt(LenSq());
        }

        T        operator *  (const Vec3& rhs) const
        {
            return x * rhs.x + y * rhs.y;
        }
        Vec3<T>  operator -  ()                const
        {
            return Vec3(-x, -y);
        }

        Vec3<T>  operator +  (const Vec3& rhs) const
        {
            return Vec3(*this) += rhs;
        }
        Vec3<T>  operator -  (const Vec3& rhs) const
        {
            return Vec3(*this) -= rhs;
        }
        Vec3<T>  operator *  (const    T& rhs) const
        {
            return Vec3(*this) *= rhs;
        }
        Vec3<T>  operator /  (const    T& rhs) const
        {
            return Vec3(*this) /= rhs;
        }

        Vec3<T>& operator  = (const Vec3& rhs)
        {
            x = rhs.x;
            y = rhs.y;
            w = rhs.w;

            return *this;
        }
        Vec3<T>& operator += (const Vec3& rhs)
        {
            x += rhs.x;
            y += rhs.y;

            return *this;
        }
        Vec3<T>& operator -= (const Vec3& rhs)
        {
            x -= rhs.x;
            y -= rhs.y;

            return *this;
        }
        Vec3<T>& operator *= (const    T& rhs)
        {
            x *= rhs;
            y *= rhs;

            return *this;
        }
        Vec3<T>& operator /= (const    T& rhs)
        {
            x /= rhs;
            y /= rhs;

            return *this;
        }

        bool  operator == (const Vec3& rhs) const
        {
            return x == rhs.x && y == rhs.y;
        }
        bool  operator != (const Vec3& rhs) const
        {
            return !(*this == rhs);
        }


    public:
        T x;
        T y;
        T w = static_cast<T>(1);
    };

    typedef Vec3<int>    Vei3;
    typedef Vec3<float>  Vef3;
    typedef Vec3<double> Ved3;
}

using fatpound::math::Vef3;