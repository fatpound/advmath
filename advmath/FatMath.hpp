#pragma once

#include <cmath>

#include <numbers>

namespace fatpound::math
{
	template <typename T>
	inline auto sq(const T& x)
	{
		return x * x;
	}

	template <typename T>
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