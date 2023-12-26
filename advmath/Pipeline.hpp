#pragma once

#include "FatMath.hpp"
#include "FatWin.hpp"
#include "Graphics.hpp"
#include "Triangle.hpp"
#include "IndexedTriangleList.hpp"
#include "CubeScreenTransformer.hpp"
#include "Mat3.hpp"

#include <algorithm>

class Pipeline
{
public:
    class Vertex
    {
    public:
        Vertex() = default;
        Vertex(const Vef3& pos)
            :
            pos(pos)
        {}

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


public:
    Pipeline(Graphics& in_gfx)
        :
        gfx(in_gfx)
    {

    }


public:
    void Draw(IndexedTriangleList<Vertex>& triList)
    {
        ProcessVertices(triList.vertices, triList.indices);
    }
    void BindRotation(const Maf3& in_rotation)
    {
        rotation = in_rotation;
    }
    void BindTranslation(const Vef3& in_translation)
    {
        translation = in_translation;
    }
    void BindTexture(const std::wstring& filename)
    {
        pTexture = std::make_unique<Surface>(Surface::FromFile(filename));
    }


private:
    void ProcessVertices(const std::vector<Vertex>& vertices, const std::vector<size_t>& indices)
    {
        std::vector<Vertex> verticesOut;

        for (const auto& v : vertices)
        {
            verticesOut.emplace_back(v.pos * rotation + translation, v.tc);
        }

        AssembleTriangles(verticesOut, indices);
    }

    void AssembleTriangles(const std::vector<Vertex>& vertices, const std::vector<size_t>& indices)
    {
        for (size_t i = 0, end = indices.size() / 3; i < end; i++)
        {
            const auto& v0 = vertices[indices[i * 3]];
            const auto& v1 = vertices[indices[i * 3 + 1]];
            const auto& v2 = vertices[indices[i * 3 + 2]];

            if ((v1.pos - v0.pos) % (v2.pos - v0.pos) * v0.pos <= 0.0f)
            {
                // process 3 vertices into a triangle
                ProcessTriangle(v0, v1, v2);
            }
        }
    }
    void ProcessTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
    {
        PostProcessTriangleVertices(Triangle<Vertex>{ v0, v1, v2 });
    }
    void PostProcessTriangleVertices(Triangle<Vertex> triangle)
    {
        cst.Transform(triangle.v0.pos);
        cst.Transform(triangle.v1.pos);
        cst.Transform(triangle.v2.pos);

        DrawTriangle(triangle);
    }

    void DrawTriangle(const Triangle<Vertex>& triangle)
    {
        const Vertex* pv0 = &triangle.v0;
        const Vertex* pv1 = &triangle.v1;
        const Vertex* pv2 = &triangle.v2;

        if (pv1->pos.y < pv0->pos.y)
        {
            std::swap(pv0, pv1);
        }
        if (pv2->pos.y < pv1->pos.y)
        {
            std::swap(pv1, pv2);
        }
        if (pv1->pos.y < pv0->pos.y)
        {
            std::swap(pv0, pv1);
        }

        if (pv0->pos.y == pv1->pos.y)
        {
            if (pv1->pos.x < pv0->pos.x)
            {
                std::swap(pv0, pv1);
            }

            DrawFlatTopTriangle(*pv0, *pv1, *pv2);
        }
        else if (pv1->pos.y == pv2->pos.y)
        {
            if (pv2->pos.x < pv1->pos.x)
            {
                std::swap(pv1, pv2);
            }

            DrawFlatBottomTriangle(*pv0, *pv1, *pv2);
        }
        else
        {
            const float splitRatio = fatpound::math::line_split_ratio(pv0->pos.y, pv1->pos.y, pv2->pos.y);

            const Vertex vi = fatpound::math::interpolate(*pv0, *pv2, splitRatio);

            if (pv1->pos.x < vi.pos.x)
            {
                DrawFlatBottomTriangle(*pv0, *pv1, vi);
                DrawFlatTopTriangle(*pv1, vi, *pv2);
            }
            else
            {
                DrawFlatBottomTriangle(*pv0, vi, *pv1);
                DrawFlatTopTriangle(vi, *pv1, *pv2);
            }
        }
    }

    void DrawFlatTopTriangle(const Vertex& it0, const Vertex& it1, const Vertex& it2)
    {
        const float deltaY = it2.pos.y - it0.pos.y;
        const auto dit0 = (it2 - it0) / deltaY;
        const auto dit1 = (it2 - it1) / deltaY;

        Vertex itEdge1 = it1;

        DrawFlatTriangle(it0, it1, it2, dit0, dit1, itEdge1);
    }
    void DrawFlatBottomTriangle(const Vertex& it0, const Vertex& it1, const Vertex& it2)
    {
        const float deltaY = it2.pos.y - it0.pos.y;
        const auto dit0 = (it1 - it0) / deltaY;
        const auto dit1 = (it2 - it0) / deltaY;

        Vertex itEdge1 = it0;

        DrawFlatTriangle(it0, it1, it2, dit0, dit1, itEdge1);
    }
    void DrawFlatTriangle(const Vertex& it0, const Vertex& it1, const Vertex& it2, const Vertex& dv0, const Vertex& dv1, Vertex itEdge1)
    {
        Vertex itEdge0 = it0;

        const int yStart = static_cast<int>(std::ceil(it0.pos.y - 0.5f));
        const int yEnd   = static_cast<int>(std::ceil(it2.pos.y - 0.5f));

        itEdge0 += dv0 * (static_cast<float>(yStart) + 0.5f - it0.pos.y);
        itEdge1 += dv1 * (static_cast<float>(yStart) + 0.5f - it0.pos.y);

        const float textureWidth  = static_cast<float>(pTexture->GetWidth());
        const float textureHeight = static_cast<float>(pTexture->GetHeight());
        const Vef2 textureClamper = Vef2(textureWidth - 1.0f, textureHeight - 1.0f);

        for (int y = yStart; y < yEnd; ++y, itEdge0 += dv0, itEdge1 += dv1)
        {
            const int xStart = static_cast<int>(std::ceil(itEdge0.pos.x - 0.5f));
            const int xEnd = static_cast<int>(std::ceil(itEdge1.pos.x - 0.5f));

            const Vef2 deltaTexCoordLine = (itEdge1.tc - itEdge0.tc) / (itEdge1.pos.x - itEdge0.pos.x);

            Vef2 itTexCoordLine = itEdge0.tc + deltaTexCoordLine * (static_cast<float>(xStart) + 0.5f - itEdge0.pos.x);

            for (int x = xStart; x < xEnd; ++x, itTexCoordLine += deltaTexCoordLine)
            {
                gfx.PutPixel(
                    x,
                    y,
                    pTexture->GetPixel(
                        static_cast<int>(std::min(itTexCoordLine.x * textureWidth,  textureClamper.x)),
                        static_cast<int>(std::min(itTexCoordLine.y * textureHeight, textureClamper.y))
                    )
                );
            }
        }
    }


private:
    std::unique_ptr<Surface> pTexture;

    Graphics& gfx;
    CubeScreenTransformer cst;
    Maf3 rotation;
    Vef3 translation;
};