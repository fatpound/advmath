#pragma once

#include "Vec3.hpp"

namespace fatpound::math
{
    template <typename T>
    class Mat3
    {
    public:
        Mat3<T>& operator = (const Mat3<T>& rhs)
        {
            cells[0][0] = rhs.cells[0][0];
            cells[0][1] = rhs.cells[0][1];
            cells[0][2] = rhs.cells[0][2];

            cells[1][0] = rhs.cells[1][0];
            cells[1][1] = rhs.cells[1][1];
            cells[1][2] = rhs.cells[1][2];

            cells[2][0] = rhs.cells[2][0];
            cells[2][1] = rhs.cells[2][1];
            cells[2][2] = rhs.cells[2][2];

            return *this;
        }


    public:
        static Mat3<T> Scaling(T factor)
        {
            return Mat3<T>{
                factor,            static_cast<T>(0), static_cast<T>(0),
                static_cast<T>(0), factor,            static_cast<T>(0),
                static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)
            };
        }
        static Mat3<T> Identity()
        {
            return Scaler(static_cast<T>(1));
        }
        static Mat3<T> RotationAroundZ(T theta)
        {
            const auto sint = std::sin(theta);
            const auto cost = std::cos(theta);

            return Mat3<T>{
                cost,              -sint,             static_cast<T>(0),
                sint,               cost,             static_cast<T>(0),
                static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)
            };
        }
        static Mat3<T> RotationAroundY(T theta)
        {
            const auto sint = std::sin(theta);
            const auto cost = std::cos(theta);

            return Mat3<T>{
                cost,              static_cast<T>(0), -sint,
                static_cast<T>(0), static_cast<T>(1), static_cast<T>(0),
                sint,              static_cast<T>(0),  cost
            };
        }
        static Mat3<T> RotationAroundX(T theta)
        {
            const auto sint = std::sin(theta);
            const auto cost = std::cos(theta);

            return Mat3<T>{
                static_cast<T>(1), static_cast<T>(0), static_cast<T>(0),
                static_cast<T>(0),  cost,             sint,
                static_cast<T>(0), -sint,             cost
            };
        }

        Mat3<T>  operator *  (T factor) const
        {
            Mat3<T> result = *this;

            return result *= factor;
        }
        Mat3<T>  operator *  (const Mat3<T>& rhs) const
        {
            return Mat3<T>{
                cells[0][0] * rhs.cells[0][0] + cells[0][1] * rhs.cells[1][0] + cells[0][2] * rhs.cells[2][0],    cells[0][0] * rhs.cells[0][1] + cells[0][1] * rhs.cells[1][1] + cells[0][2] * rhs.cells[2][1],     cells[0][0] * rhs.cells[0][2] + cells[0][1] * rhs.cells[1][2] + cells[0][2] * rhs.cells[2][2],
                cells[1][0] * rhs.cells[0][0] + cells[1][1] * rhs.cells[1][0] + cells[1][2] * rhs.cells[2][0],    cells[1][0] * rhs.cells[0][1] + cells[1][1] * rhs.cells[1][1] + cells[1][2] * rhs.cells[2][1],     cells[1][0] * rhs.cells[0][2] + cells[1][1] * rhs.cells[1][2] + cells[1][2] * rhs.cells[2][2],
                cells[2][0] * rhs.cells[0][0] + cells[2][1] * rhs.cells[1][0] + cells[2][2] * rhs.cells[2][0],    cells[2][0] * rhs.cells[0][1] + cells[2][1] * rhs.cells[1][1] + cells[2][2] * rhs.cells[2][1],     cells[2][0] * rhs.cells[0][2] + cells[2][1] * rhs.cells[1][2] + cells[2][2] * rhs.cells[2][2]
            };
        }
        Mat3<T>& operator *= (T factor)
        {
            cells[0][0] *= factor;
            cells[0][1] *= factor;
            cells[0][2] *= factor;

            cells[1][0] *= factor;
            cells[1][1] *= factor;
            cells[1][2] *= factor;

            cells[2][0] *= factor;
            cells[2][1] *= factor;
            cells[2][2] *= factor;

            return *this;
        }
        Mat3<T>& operator *= (const Mat3<T>& rhs)
        {
            *this = *this * rhs;

            return *this;
        }


    public:
        T cells[3][3];


    protected:


    private:
    };


    template <typename T>
    Vec3<T>& operator *= (Vec3<T>& lhs, const Mat3<T>& rhs)
    {
        lhs = lhs * rhs;

        return lhs;
    }

    template <typename T>
    Vec3<T>  operator * (const Vec3<T>& lhs, const Mat3<T>& rhs)
    {
        return Vec3<T>{
            lhs.x * rhs.cells[0][0] + lhs.y * rhs.cells[1][0] + lhs.z * rhs.cells[2][0],
            lhs.x * rhs.cells[0][1] + lhs.y * rhs.cells[1][1] + lhs.z * rhs.cells[2][1],
            lhs.x * rhs.cells[0][2] + lhs.y * rhs.cells[1][2] + lhs.z * rhs.cells[2][2]
        };
    }

    typedef Mat3<float> Maf3;
    typedef Mat3<double> Mad3;
}