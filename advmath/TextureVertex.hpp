#pragma once

#include "Vec2.hpp"
#include "Vec3.hpp"

using fatpound::math::Vef2;
using fatpound::math::Vef3;

class TextureVertex
{
public:
	TextureVertex(const Vef3& in_pos, const Vef2& in_texCoord)
		:
		pos(in_pos),
		texCoord(in_texCoord)
	{

	}


public:
	TextureVertex InterpolateTo(const TextureVertex& dest, float splitRatio) const
	{
		return TextureVertex{
			pos.InterpolateTo(dest.pos, splitRatio),
			texCoord.InterpolateTo(dest.texCoord, splitRatio)
		};
	}

	TextureVertex  operator +  (const TextureVertex& rhs) const
	{
		TextureVertex tex(*this);

		tex += rhs;

		return tex;
	}
	TextureVertex  operator -  (const TextureVertex& rhs) const
	{
		TextureVertex tex(*this);

		tex -= rhs;

		return tex;
	}
	TextureVertex  operator *  (float rhs) const
	{
		TextureVertex tex(*this);

		tex *= rhs;

		return tex;
	}
	TextureVertex  operator /  (float rhs) const
	{
		TextureVertex tex(*this);

		tex /= rhs;

		return tex;
	}

	TextureVertex& operator += (const TextureVertex& rhs)
	{
		pos += rhs.pos;
		texCoord += rhs.texCoord;

		return *this;
	}
	TextureVertex& operator -= (const TextureVertex& rhs)
	{
		pos -= rhs.pos;
		texCoord -= rhs.texCoord;

		return *this;
	}
	TextureVertex& operator *= (float rhs)
	{
		pos *= rhs;
		texCoord *= rhs;

		return *this;
	}
	TextureVertex& operator /= (float rhs)
	{
		pos /= rhs;
		texCoord /= rhs;

		return *this;
	}


public:
	Vef3 pos;
	Vef2 texCoord;
};
