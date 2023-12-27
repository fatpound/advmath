#pragma once

#include "FatMath.hpp"
#include "Scene.hpp"
#include "Plane.hpp"
#include "Mat3.hpp"
#include "WaveVertexTextureEffect.hpp"

class VertexWaveScene : public Scene
{
public:
    typedef Pipeline<WaveVertexTextureEffect> Pipeline;
    typedef Pipeline::Vertex Vertex;


public:
    VertexWaveScene(Graphics& gfx)
        :
        Scene(L"Test Plane Rippling VS"),
        itlist(Plane::GenerateSkinned<Vertex>(20)),
        pipeline(gfx)
    {
        pipeline.effect.pixelshader.BindTexture(L"Images\\sauron-eye-100x100.png");
    }


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

        time += dt;
    }
    virtual void Draw() override
    {
        pipeline.BeginFrame();

        const Maf3 rot = Maf3::RotationAroundX(theta_x) * Maf3::RotationAroundY(theta_y) * Maf3::RotationAroundZ(theta_z);
        const Vef3 trans = Vef3{ 0.0f,0.0f,offset_z };

        pipeline.effect.vertexshader.BindRotation(rot);
        pipeline.effect.vertexshader.BindTranslation(trans);
        pipeline.effect.vertexshader.SetTime(time);

        pipeline.Draw(itlist);
    }


private:
    static constexpr float dTheta = std::numbers::pi_v<float>;

    IndexedTriangleList<Vertex> itlist;
    Pipeline pipeline;

    float offset_z = 2.0f;
    float theta_x = 0.0f;
    float theta_y = 0.0f;
    float theta_z = 0.0f;

    float time = 0.0f;
};