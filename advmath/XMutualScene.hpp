#pragma once

#include "FatMath.hpp"
#include "Scene.hpp"
#include "XQuads.hpp"
#include "CubeScreenTransformer.hpp"
#include "Mat3.hpp"

class XMutualScene : public Scene
{
public:
    XMutualScene() = default;


public:
    virtual void Update(Keyboard& kbd, Mouse& mouse, float dt) override
    {
        if (kbd.KeyIsPressed('Q'))
        {
            theta_x = fatpound::math::wrap_angle(theta_x + dTheta * dt);
        }
        if (kbd.KeyIsPressed('W'))
        {
            theta_y = fatpound::math::wrap_angle(theta_y + dTheta * dt);
        }
        if (kbd.KeyIsPressed('E'))
        {
            theta_z = fatpound::math::wrap_angle(theta_z + dTheta * dt);
        }

        if (kbd.KeyIsPressed('A'))
        {
            theta_x = fatpound::math::wrap_angle(theta_x - dTheta * dt);
        }
        if (kbd.KeyIsPressed('S'))
        {
            theta_y = fatpound::math::wrap_angle(theta_y - dTheta * dt);
        }
        if (kbd.KeyIsPressed('D'))
        {
            theta_z = fatpound::math::wrap_angle(theta_z - dTheta * dt);
        }

        if (kbd.KeyIsPressed('R'))
        {
            offset_z += 2.0f * dt;
        }
        if (kbd.KeyIsPressed('F'))
        {
            offset_z -= 2.0f * dt;
        }
    }
    virtual void Draw(Graphics& gfx) const override
    {
        auto triangles = hex.GetTriangles();
        
        const Maf3 rot = Maf3::RotationAroundX(theta_x) * Maf3::RotationAroundY(theta_y) * Maf3::RotationAroundZ(theta_z);

        for (auto& v : triangles.vertices)
        {
            v *= rot;
            v += { 0.0f, 0.0f, offset_z };
        }
        
        for (size_t i = 0, end = triangles.indices.size() / 3; i < end; i++)
        {
            const Vef3& v0 = triangles.vertices[triangles.indices[i * 3]];
            const Vef3& v1 = triangles.vertices[triangles.indices[i * 3 + 1]];
            const Vef3& v2 = triangles.vertices[triangles.indices[i * 3 + 2]];

            triangles.cullFlags[i] = (v1 - v0) % (v2 - v0) * v0 > 0.0f;
        }
        
        for (auto& v : triangles.vertices)
        {
            cst.Transform(v);
        }

        for (size_t i = 0, end = triangles.indices.size() / 3; i < end; i++)
        {
            if ( ! triangles.cullFlags[i] )
            {
                gfx.DrawTriangle(
                    triangles.vertices[triangles.indices[i * 3]],
                    triangles.vertices[triangles.indices[i * 3 + 1]],
                    triangles.vertices[triangles.indices[i * 3 + 2]],
                    colors[i]
                );
            }
        }
    }


private:
    CubeScreenTransformer cst;
    XQuads hex = XQuads(1.0f);

    static constexpr float dTheta = std::numbers::pi_v<float>;

    float offset_z = 2.0f;
    float theta_x = 0.0f;
    float theta_y = 0.0f;
    float theta_z = 0.0f;
};