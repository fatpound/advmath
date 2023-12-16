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
	TextureVertex InterpolateTo(const TextureVertex& dest, float alpha) const
	{
		return TextureVertex{
			pos.InterpolateTo(dest.pos, alpha),
			texCoord.InterpolateTo(dest.texCoord, alpha)
		};
	}


public:
	Vef3 pos;
	Vef2 texCoord;
};
