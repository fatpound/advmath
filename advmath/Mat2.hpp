#pragma once

#include "Vec2.hpp"

namespace fatpound::math
{
    template <typename T>
    class Mat2
    {
    public:
        static Mat2<T> Scaler(T factor)
        {
            return Mat2<T>{
                factor,            static_cast<T>(0),
                static_cast<T>(0), factor
            };
        }
        static Mat2<T> Identity()
        {
            return Scaler(static_cast<T>(1));
        }
        static Mat2<T> YFlipper()
        {
            return Mat2<T>{
                static_cast<T>(1), static_cast<T>(0),
                static_cast<T>(0), static_cast<T>(-1)
            };
        }
        static Mat2<T> Rotater(T theta)
        {
            const auto sint = std::sin(theta);
            const auto cost = std::cos(theta);

            return Mat2<T>{
                cost, -sint,
                sint,  cost
            };
        }

        Vec2<T>  operator *  (const Vec2<T>& vec) const
        {
            return Vec2<T>{
                cells[0][0] * vec.x + cells[0][1] * vec.y,
                cells[1][0] * vec.x + cells[1][1] * vec.y
            };
        }
        Mat2<T>  operator *  (const Mat2<T>& rhs) const
        {
            return Mat2<T>{
                cells[0][0] * rhs.cells[0][0] + cells[0][1] * rhs.cells[1][0], cells[0][0] * rhs.cells[0][1] + cells[0][1] * rhs.cells[1][1],
                cells[1][0] * rhs.cells[0][0] + cells[1][1] * rhs.cells[1][0], cells[1][0] * rhs.cells[0][1] + cells[1][1] * rhs.cells[1][1]
            };
        }
        Mat2<T>& operator *= (const Mat2<T>& rhs)
        {
            *this = *this * rhs;

            return *this;
        }


    public:
        T cells[2][2];


    protected:


    private:
    };

    typedef Mat2<float> Maf2;
    typedef Mat2<double> Mad2;
}

using fatpound::math::Maf2;