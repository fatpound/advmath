#pragma once

#include "Color.hpp"
#include "Vec3.hpp"
#include "Surface.hpp"

#include <cmath>

using fatpound::math::Vef2;
using fatpound::math::Vef3;

class TextureEffect
{
public:
    class Vertex
    {
    public:
        Vertex() = default;
        Vertex(const Vef3& pos)
            :
            pos(pos)
        {

        }

    public:
        Vertex(const Vef3& in_pos, const Vertex& src)
            :
            pos(in_pos),
            tc(src.tc)
        {

        }
        Vertex(const Vef3& in_pos, const Vef2& in_tc)
            :
            pos(in_pos),
            tc(in_tc)
        {

        }

    public:
        Vertex  operator +  (const Vertex& rhs) const
        {
            Vertex vertex(*this);

            vertex += rhs;

            return vertex;
        }
        Vertex  operator -  (const Vertex& rhs) const
        {
            Vertex vertex(*this);

            vertex -= rhs;

            return vertex;
        }
        Vertex  operator *  (float rhs) const
        {
            Vertex vertex(*this);

            vertex *= rhs;

            return vertex;
        }
        Vertex  operator /  (float rhs) const
        {
            Vertex vertex(*this);

            vertex /= rhs;

            return vertex;
        }

        Vertex& operator += (const Vertex& rhs)
        {
            pos += rhs.pos;
            tc += rhs.tc;

            return *this;
        }
        Vertex& operator -= (const Vertex& rhs)
        {
            pos -= rhs.pos;
            tc -= rhs.tc;

            return *this;
        }
        Vertex& operator *= (float rhs)
        {
            pos *= rhs;
            tc *= rhs;

            return *this;
        }
        Vertex& operator /= (float rhs)
        {
            pos /= rhs;
            tc /= rhs;

            return *this;
        }

    public:
        Vef3 pos;
        Vef2 tc;
    };
    class PixelShader
    {
    public:
        void BindTexture(const std::wstring& filename)
        {
            pTexture = std::make_unique<Surface>(Surface::FromFile(filename));

            tex_width   = static_cast<float>(pTexture->GetWidth());
            tex_height  = static_cast<float>(pTexture->GetHeight());
            tex_clamper = Vef2(tex_width - 1.0f, tex_height - 1.0f);
        }

        template<class Input>
        Color operator () (const Input& in) const
        {
            return pTexture->GetPixel(
                static_cast<unsigned int>(std::min(in.tc.x * tex_width  + 0.5f, tex_clamper.x)),
                static_cast<unsigned int>(std::min(in.tc.y * tex_height + 0.5f, tex_clamper.y))
            );
        }

    private:
        std::unique_ptr<Surface> pTexture;

        Vef2 tex_clamper;

        float tex_width;
        float tex_height;
    };


public:
    PixelShader pixelshader;
};