#pragma once

#include "Vec3.hpp"

namespace fatpound::math
{
    template <typename T>
    class Mat3
    {
    public:
        static Mat3<T> Scaler(T factor)
        {
            return Mat3<T>{
                factor,            static_cast<T>(0), static_cast<T>(0),
                static_cast<T>(0), factor,            static_cast<T>(0),
                static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)
            };
        }
        static Mat3<T> ScalerIndependent(T x, T y) // W, H
        {
            return Mat3<T>{
                static_cast<T>(x), static_cast<T>(0), static_cast<T>(0),
                static_cast<T>(0), static_cast<T>(y), static_cast<T>(0),
                static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)
            };
        }
        static Mat3<T> Identity()
        {
            return Scaler(static_cast<T>(1));
        }
        static Mat3<T> YFlipper()
        {
            return Mat3<T>{
                static_cast<T>(1), static_cast<T>( 0), static_cast<T>(0),
                static_cast<T>(0), static_cast<T>(-1), static_cast<T>(0),
                static_cast<T>(0), static_cast<T>( 0), static_cast<T>(1)
            };
        }
        static Mat3<T> Rotater(T theta)
        {
            const auto sint = std::sin(theta);
            const auto cost = std::cos(theta);

            return Mat3<T>{
                cost,              -sint,             static_cast<T>(0),
                sint,               cost,             static_cast<T>(0),
                static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)
            };
        }
        static Mat3<T> Translater(const Vec2<T>& vec)
        {
            return Translater(vec.x, vec.y);
        }
        static Mat3<T> Translater(T x, T y)
        {
            return Mat3<T>{
                static_cast<T>(1), static_cast<T>(0), x,
                static_cast<T>(0), static_cast<T>(1), y,
                static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)
            };
        }

        Vec2<T>  operator *  (const Vec2<T>& vec) const
        {
            return Vec2<T>(*this * static_cast<Vec3<T>>(vec));
        }
        Vec3<T>  operator *  (const Vec3<T>& vec) const
        {
            return Vec3<T>{
                cells[0][0] * vec.x + cells[0][1] * vec.y + cells[0][2] * vec.w,
                cells[1][0] * vec.x + cells[1][1] * vec.y + cells[1][2] * vec.w,
                cells[2][0] * vec.x + cells[2][1] * vec.y + cells[2][2] * vec.w
            };
        }
        Mat3<T>  operator *  (const Mat3<T>& rhs) const
        {
            return Mat3<T>{
                cells[0][0] * rhs.cells[0][0] + cells[0][1] * rhs.cells[1][0] + cells[0][2] * rhs.cells[2][0],    cells[0][0] * rhs.cells[0][1] + cells[0][1] * rhs.cells[1][1] + cells[0][2] * rhs.cells[2][1],     cells[0][0] * rhs.cells[0][2] + cells[0][1] * rhs.cells[1][2] + cells[0][2] * rhs.cells[2][2],
                cells[1][0] * rhs.cells[0][0] + cells[1][1] * rhs.cells[1][0] + cells[1][2] * rhs.cells[2][0],    cells[1][0] * rhs.cells[0][1] + cells[1][1] * rhs.cells[1][1] + cells[1][2] * rhs.cells[2][1],     cells[1][0] * rhs.cells[0][2] + cells[1][1] * rhs.cells[1][2] + cells[1][2] * rhs.cells[2][2],
                cells[2][0] * rhs.cells[0][0] + cells[2][1] * rhs.cells[1][0] + cells[2][2] * rhs.cells[2][0],    cells[2][0] * rhs.cells[0][1] + cells[2][1] * rhs.cells[1][1] + cells[2][2] * rhs.cells[2][1],     cells[2][0] * rhs.cells[0][2] + cells[2][1] * rhs.cells[1][2] + cells[2][2] * rhs.cells[2][2]
            };
        }


    public:
        T cells[3][3];


    protected:


    private:
    };

    typedef Mat3<float> Maf3;
    typedef Mat3<double> Mad3;
}

using fatpound::math::Maf3;