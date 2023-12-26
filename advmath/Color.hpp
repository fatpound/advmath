/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Color.h																			  *
*	Copyright 2016 PlanetChili <http://www.planetchili.net>								  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#pragma once

#include "Vec3.hpp"

#include <iostream>
#include <array>

namespace fatpound::color
{
    class Color
    {
    public:
        constexpr Color() = default;
        constexpr ~Color() noexcept = default;
        constexpr Color(const Color& src) noexcept
            :
            dword(src.dword)
        {

        }
        constexpr Color(Color&& src) noexcept = default;
        constexpr Color& operator = (const Color& src) noexcept
        {
            dword = src.dword;

            return *this;
        }
        constexpr Color& operator = (Color&& src) noexcept = default;

        constexpr Color(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha = 0xFFu)
        {
            dword = static_cast<uint32_t>(alpha) << 24u
                | static_cast<uint32_t>(r) << 16u
                | static_cast<uint32_t>(g) << 8u
                | static_cast<uint32_t>(b);
        }
        constexpr Color(int r, int g, int b)
            :
            Color(static_cast<unsigned char>(r), static_cast<unsigned char>(g), static_cast<unsigned char>(b))
        {

        }
        constexpr Color(uint32_t dw)
            :
            dword(dw | 0xFF'00'00'00u)
        {

        }
        constexpr Color(Color col, unsigned char alpha)
            :
            Color((static_cast<uint32_t>(alpha) << 24u) | col.dword)
        {

        }

        explicit Color(const Vef3& floatColor)
            :
            Color(static_cast<unsigned char>(floatColor.x), static_cast<unsigned char>(floatColor.y), static_cast<unsigned char>(floatColor.z))
        {

        }
        

    public:
        void SetAlpha(unsigned char x)
        {
            dword = (dword & 0x00'FF'FF'FFu) | (uint32_t(x) << 24u);
        }
        void SetR(unsigned char r)
        {
            dword = (dword & 0xFF'00'FF'FFu) | (uint32_t(r) << 16u);
        }
        void SetG(unsigned char g)
        {
            dword = (dword & 0xFF'FF'00'FFu) | (uint32_t(g) << 8u);
        }
        void SetB(unsigned char b)
        {
            dword = (dword & 0xFF'FF'FF'00u) | uint32_t(b);
        }

        constexpr unsigned char GetA() const
        {
            return dword >> 24u;
        }
        constexpr unsigned char GetR() const
        {
            return (dword >> 16u) & 0xFFu;
        }
        constexpr unsigned char GetG() const
        {
            return (dword >> 8u) & 0xFFu;
        }
        constexpr unsigned char GetB() const
        {
            return dword & 0xFFu;
        }

        explicit operator Vef3() const
        {
            return Vef3{ static_cast<float>(GetR()), static_cast<float>(GetG()), static_cast<float>(GetB()) };
        }

        bool operator == (const Color src) const
        {
            return dword == src.dword;
        }


    public:
        uint32_t dword = 0xFF'FF'FF'FFu;


    protected:


    private:
    };


    static constexpr Color MakeRGB(unsigned char r, unsigned char g, unsigned char b)
    {
        return (r << 16u) | (g << 8u) | b;
    }

    static constexpr Color Black = MakeRGB(0u, 0u, 0u);
    static constexpr Color Gray = MakeRGB(128u, 128u, 128u);
    static constexpr Color LightGray = MakeRGB(192u, 192u, 192u);
    static constexpr Color White = MakeRGB(255u, 255u, 255u);

    static constexpr Color Red = MakeRGB(255u, 0u, 0u);
    static constexpr Color Green = MakeRGB(0u, 255u, 0u);
    static constexpr Color Blue = MakeRGB(0u, 0u, 255u);
    static constexpr Color Yellow = MakeRGB(255u, 255u, 0u);
    static constexpr Color Cyan = MakeRGB(0u, 255u, 255u);
    static constexpr Color Magenta = MakeRGB(255u, 0u, 255u);

    static constexpr std::array<Color, 12> colors = {
        White,
        Blue,
        Cyan,
        Gray,
        Green,
        Magenta,
        LightGray,
        Red,
        Yellow,
        White,
        Blue,
        Cyan
    };
}