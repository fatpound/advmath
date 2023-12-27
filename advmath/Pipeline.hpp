#pragma once

#include "FatMath.hpp"
#include "FatWin.hpp"
#include "Graphics.hpp"
#include "Triangle.hpp"
#include "IndexedTriangleList.hpp"
#include "CubeScreenTransformer.hpp"
#include "Mat3.hpp"
#include "ZBuffer.hpp"

#include <algorithm>

/*

                    idx stream
         *----------------------------------*
         |                                  |
indexed  |                                  V                Perspective
triangle --> SPLIT --> VertexShader --> TriangleAssembly -->   Screen    --> TriangleRasterizer --> PixelShader --> PutPixel
list                                                         Transformer


*/

template <class Effect>
class Pipeline
{
public:
    typedef typename Effect::Vertex Vertex;
    typedef typename Effect::VertexShader::Output VSOut;


public:
    Pipeline(Graphics& in_gfx)
        :
        gfx(in_gfx),
        zbuffer(gfx.ScreenWidth, gfx.ScreenHeight)
    {

    }


public:
    Effect effect;


public:
    void Draw(IndexedTriangleList<Vertex>& triList)
    {
        ProcessVertices(triList.vertices, triList.indices);
    }
    void BeginFrame()
    {
        zbuffer.Clear();
    }


private:
    void ProcessVertices(const std::vector<Vertex>& vertices, const std::vector<size_t>& indices)
    {
        std::vector<VSOut> verticesOut(vertices.size());

        std::transform(
            vertices.begin(),
            vertices.end(),
            verticesOut.begin(),
            effect.vertexshader
        );

        AssembleTriangles(verticesOut, indices);
    }

    void AssembleTriangles(const std::vector<VSOut>& vertices, const std::vector<size_t>& indices)
    {
        for (size_t i = 0, end = indices.size() / 3; i < end; i++)
        {
            const auto& v0 = vertices[indices[i * 3]];
            const auto& v1 = vertices[indices[i * 3 + 1]];
            const auto& v2 = vertices[indices[i * 3 + 2]];

            if ((v1.pos - v0.pos) % (v2.pos - v0.pos) * v0.pos <= 0.0f)
            {
                ProcessTriangle(v0, v1, v2);
            }
        }
    }
    void ProcessTriangle(const VSOut& v0, const VSOut& v1, const VSOut& v2)
    {
        PostProcessTriangleVertices(Triangle<VSOut>{ v0, v1, v2 });
    }
    void PostProcessTriangleVertices(Triangle<VSOut> triangle)
    {
        cst.Transform(triangle.v0);
        cst.Transform(triangle.v1);
        cst.Transform(triangle.v2);

        DrawTriangle(triangle);
    }

    void DrawTriangle(const Triangle<VSOut>& triangle)
    {
        const VSOut* pv0 = &triangle.v0;
        const VSOut* pv1 = &triangle.v1;
        const VSOut* pv2 = &triangle.v2;

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

    void DrawFlatTopTriangle(const VSOut& it0, const VSOut& it1, const VSOut& it2)
    {
        const float deltaY = it2.pos.y - it0.pos.y;
        const auto dit0 = (it2 - it0) / deltaY;
        const auto dit1 = (it2 - it1) / deltaY;

        auto itEdge1 = it1;

        DrawFlatTriangle(it0, it1, it2, dit0, dit1, itEdge1);
    }
    void DrawFlatBottomTriangle(const VSOut& it0, const VSOut& it1, const VSOut& it2)
    {
        const float deltaY = it2.pos.y - it0.pos.y;
        const auto dit0 = (it1 - it0) / deltaY;
        const auto dit1 = (it2 - it0) / deltaY;

        auto itEdge1 = it0;

        DrawFlatTriangle(it0, it1, it2, dit0, dit1, itEdge1);
    }
    void DrawFlatTriangle(const VSOut& it0, const VSOut& it1, const VSOut& it2, const VSOut& dv0, const VSOut& dv1, VSOut itEdge1)
    {
        auto itEdge0 = it0;

        const int yStart = static_cast<int>(std::ceil(it0.pos.y - 0.5f));
        const int yEnd   = static_cast<int>(std::ceil(it2.pos.y - 0.5f));

        itEdge0 += dv0 * (static_cast<float>(yStart) + 0.5f - it0.pos.y);
        itEdge1 += dv1 * (static_cast<float>(yStart) + 0.5f - it0.pos.y);

        for (int y = yStart; y < yEnd; ++y, itEdge0 += dv0, itEdge1 += dv1)
        {
            const int xStart = static_cast<int>(std::ceil(itEdge0.pos.x - 0.5f));
            const int xEnd   = static_cast<int>(std::ceil(itEdge1.pos.x - 0.5f));

            auto iLine = itEdge0;

            const float dx = itEdge1.pos.x - itEdge0.pos.x;
            const auto diLine = (itEdge1 - iLine) / dx;

            iLine += diLine * (static_cast<float>(xStart) + 0.5f - itEdge0.pos.x);

            for (int x = xStart; x < xEnd; ++x, iLine += diLine)
            {
                const float z = 1.0f / iLine.pos.z;

                const auto attr = iLine * z;

                if (zbuffer.TestAndSet(x, y, z))
                {
                    gfx.PutPixel(x, y, effect.pixelshader(attr));
                }
            }
        }
    }


private:
    Graphics& gfx;
    CubeScreenTransformer cst;
    ZBuffer zbuffer;
};