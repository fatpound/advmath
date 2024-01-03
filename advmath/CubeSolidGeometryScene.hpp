#pragma once

#include "FatMath.hpp"
#include "Scene.hpp"
#include "Cube.hpp"
#include "Mat3.hpp"
#include "Pipeline.hpp"
#include "SolidGeometryEffect.hpp"

class CubeSolidGeometryScene : public Scene
{
public:
    typedef Pipeline<SolidGeometryEffect> Pipeline;
    typedef Pipeline::Vertex Vertex;


public:
    CubeSolidGeometryScene(Graphics& gfx)
        :
        Scene(L"Colored cube geometry solid face scene"),
        itlist(Cube::GeneratePlain<Vertex>()),
        pipeline(gfx)
    {
        pipeline.effect.geometryshader.BindColors(
            { Red, Green, Blue, Magenta, Yellow, Cyan }
        );
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
    }
    virtual void Draw() override
    {
        pipeline.BeginFrame();

        const Maf3 rot = Maf3::RotationAroundX(theta_x) * Maf3::RotationAroundY(theta_y) * Maf3::RotationAroundZ(theta_z);
        const Vef3 trans = { 0.0f,0.0f,offset_z };

        pipeline.effect.vertexshader.BindRotation(rot);
        pipeline.effect.vertexshader.BindTranslation(trans);

        pipeline.Draw(itlist);
    }


private:
    IndexedTriangleList<Vertex> itlist;
    Pipeline pipeline;

    static constexpr float dTheta = std::numbers::pi_v<float>;

    float offset_z = 2.0f;
    float theta_x = 0.0f;
    float theta_y = 0.0f;
    float theta_z = 0.0f;
};