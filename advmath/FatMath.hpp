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

        const T modded = fmod(theta, twoPi);

        return modded > std::numbers::pi_v<T>
            ? modded - twoPi
            : modded
            ;
    }
}