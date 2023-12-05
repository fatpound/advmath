#pragma once

#include "FatMath.hpp"

namespace fatpound::math
{
    template <typename T>
    class Vec2
    {
    public:
        Vec2(const Vec2& vec)
            :
            Vec2(vec.x, vec.y)
        {

        }

        Vec2(T in_x, T in_y)
            :
            x(in_x),
            y(in_y)
        {

        }


    public:
        template <typename T2> explicit operator Vec2<T2>() const
        {
            return{ (T2)x,(T2)y };
        }
        T LenSq() const
        {
            return x * x + y * y;
        }
        T Len() const
        {
            return std::sqrt(LenSq());
        }
        Vec2<T>& Normalize()
        {
            const T length = Len();

            x /= length;
            y /= length;

            return *this;
        }
        Vec2<T>& RotateBy(T angle)
        {
            const T cosTheta = std::cos(angle);
            const T sinTheta = std::sin(angle);

            const T new_x = x * cosTheta - y * sinTheta;

            y = x * sinTheta + y * cosTheta;
            x = new_x;

            return *this;
        }
        Vec2<T>  GetNormalized() const
        {
            Vec2<T> norm = *this;
            norm.Normalize();
            return norm;
        }
        Vec2<T>  GetRotated(T angle) const
        {
            return Vec2<T>(*this).RotateBy(angle);
        }

        T     operator *  (const Vec2& rhs) const
        {
            return x * rhs.x + y * rhs.y;
        }
        Vec2  operator -  ()                const
        {
            return Vec2(-x, -y);
        }

        Vec2  operator +  (const Vec2& rhs) const
        {
            return Vec2(*this) += rhs;
        }
        Vec2  operator -  (const Vec2& rhs) const
        {
            return Vec2(*this) -= rhs;
        }
        Vec2  operator *  (const    T& rhs) const
        {
            return Vec2(*this) *= rhs;
        }
        Vec2  operator /  (const    T& rhs) const
        {
            return Vec2(*this) /= rhs;
        }

        Vec2& operator  = (const Vec2& rhs)
        {
            x = rhs.x;
            y = rhs.y;
            return *this;
        }
        Vec2& operator += (const Vec2& rhs)
        {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }
        Vec2& operator -= (const Vec2& rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }
        Vec2& operator *= (const    T& rhs)
        {
            x *= rhs;
            y *= rhs;
            return *this;
        }
        Vec2& operator /= (const    T& rhs)
        {
            x /= rhs;
            y /= rhs;
            return *this;
        }

        bool  operator == (const Vec2& rhs) const
        {
            return x == rhs.x && y == rhs.y;
        }
        bool  operator != (const Vec2& rhs) const
        {
            return ! (*this == rhs);
        }


    public:
        T x;
        T y;
    };

    typedef Vec2<int>    Vei2;
    typedef Vec2<float>  Vef2;
    typedef Vec2<double> Ved2;
}

using fatpound::math::Vef2;