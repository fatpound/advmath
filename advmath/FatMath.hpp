#pragma once

#include <cmath>

#include <numbers>
#include <concepts>

namespace fatpound::math
{
    template <typename T>
    concept Number = std::is_integral_v<T> || std::is_floating_point_v<T>;

    template <Number T>
    inline T sq(const T& x)
    {
        return x * x;
    }

    template <std::floating_point T>
    inline T wrap_angle(T theta)
    {
        const T twoPi = static_cast<T>(2) * std::numbers::pi_v<T>;

        const T modded = std::fmod(theta, twoPi);

        return modded > std::numbers::pi_v<T>
            ? modded - twoPi
            : modded
            ;
    }

    template <Number T>
    inline T line_split_ratio(T pos0, T pos1, T pos2)
    {
        return
            (pos1 - pos0)
            /
            (pos2 - pos0);
    }

    template <Number T>
    inline T line_slope(T x0, T x1, T y0, T y1)
    {
        return
            (x1 - x0)
            /
            (y1 - y0);
    }

    template <typename T>
    inline T interpolate(const T& src, const T& dst, float splitRatio)
    {
        return src + (dst - src) * splitRatio;
    }
}