#pragma once

#include "FatMath.hpp"

namespace fatpound::math
{
    template <typename T>
    class Vec2
    {
    public:
        Vec2()
        {

        }
        Vec2(const Vec2<T>& vec)
            :
            Vec2<T>(vec.x, vec.y)
        {

        }

        Vec2(T in_x, T in_y)
            :
            x(in_x),
            y(in_y)
        {

        }


    public:
        template <typename T2>
        explicit operator Vec2<T2>() const
        {
            return{ static_cast<T2>(x), static_cast<T2>(y) };
        }

        Vec2<T>  InterpolateTo(const Vec2<T>& dest, T splitRatio) const
        {
            return *this + (dest - *this) * splitRatio;
        }
        Vec2<T>  GetNormalized() const
        {
            Vec2<T> norm = *this;

            norm.Normalize();

            return norm;
        }
        Vec2<T>  GetRotated(T angle) const
        {
            Vec2<T> vec(*this);

            vec.RotateBy(angle);

            return vec;
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

        static T line_slope(const Vec2<T>& v0, const Vec2<T>& v1)
        {
            return fatpound::math::line_slope(v0.x, v1.x, v0.y, v1.y);
        }

        T LenSq() const
        {
            return fatpound::math::sq( *this );
        }
        T Len() const
        {
            return std::sqrt(LenSq());
        }

        T        operator *  (const Vec2<T>& rhs) const
        {
            return x * rhs.x + y * rhs.y;
        }
        Vec2<T>  operator -  ()                const
        {
            return Vec2(-x, -y);
        }

        Vec2<T>  operator +  (const Vec2<T>& rhs) const
        {
            Vec2<T> vec(*this);

            vec += rhs;

            return vec;
        }
        Vec2<T>  operator -  (const Vec2<T>& rhs) const
        {
            Vec2<T> vec(*this);

            vec -= rhs;

            return vec;
        }
        Vec2<T>  operator *  (const      T & rhs) const
        {
            Vec2<T> vec(*this);

            vec *= rhs;

            return vec;
        }
        Vec2<T>  operator /  (const      T & rhs) const
        {
            Vec2<T> vec(*this);

            vec /= rhs;

            return vec;
        }

        Vec2<T>& operator  = (const Vec2<T>& rhs)
        {
            x = rhs.x;
            y = rhs.y;

            return *this;
        }
        Vec2<T>& operator += (const Vec2<T>& rhs)
        {
            x += rhs.x;
            y += rhs.y;

            return *this;
        }
        Vec2<T>& operator -= (const Vec2<T>& rhs)
        {
            x -= rhs.x;
            y -= rhs.y;

            return *this;
        }
        Vec2<T>& operator *= (const      T & rhs)
        {
            x *= rhs;
            y *= rhs;

            return *this;
        }
        Vec2<T>& operator /= (const      T & rhs)
        {
            x /= rhs;
            y /= rhs;

            return *this;
        }

        bool  operator == (const Vec2<T>& rhs) const
        {
            return x == rhs.x && y == rhs.y;
        }
        bool  operator != (const Vec2<T>& rhs) const
        {
            return !(*this == rhs);
        }


    public:
        T x;
        T y;
    };


    typedef Vec2<int>    Vei2;
    typedef Vec2<float>  Vef2;
    typedef Vec2<double> Ved2;
}