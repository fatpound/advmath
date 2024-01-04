#pragma once

#include "FatMath.hpp"
#include "Scene.hpp"
#include "Cube.hpp"
#include "Mat3.hpp"
#include "Pipeline.hpp"
#include "VertexFlatEffect.hpp"

class CubeFlatIndependentScene : public Scene
{
public:
    typedef Pipeline<VertexFlatEffect> Pipeline;
    typedef Pipeline::Vertex Vertex;


public:
    CubeFlatIndependentScene(Graphics& gfx)
        :
        Scene(L"Cube flat vertex scene"),
        itlist(Cube::GenerateIndependentFacesNormals<Vertex>()),
        pipeline(gfx)
    {

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

        if (kbd.KeyIsPressed('U'))
        {
            phi_x = fatpound::math::wrap_angle(phi_x + dTheta * dt);
        }
        if (kbd.KeyIsPressed('I'))
        {
            phi_y = fatpound::math::wrap_angle(phi_y + dTheta * dt);
        }
        if (kbd.KeyIsPressed('O'))
        {
            phi_z = fatpound::math::wrap_angle(phi_z + dTheta * dt);
        }

        if (kbd.KeyIsPressed('J'))
        {
            phi_x = fatpound::math::wrap_angle(phi_x - dTheta * dt);
        }
        if (kbd.KeyIsPressed('K'))
        {
            phi_y = fatpound::math::wrap_angle(phi_y - dTheta * dt);
        }
        if (kbd.KeyIsPressed('L'))
        {
            phi_z = fatpound::math::wrap_angle(phi_z - dTheta * dt);
        }

        if (kbd.KeyIsPressed('R'))
        {
            offset_z += 0.2f * dt;
        }
        if (kbd.KeyIsPressed('F'))
        {
            offset_z -= 0.2f * dt;
        }
    }
    virtual void Draw() override
    {
        pipeline.BeginFrame();

        const Maf3 rot = Maf3::RotationAroundX(theta_x) * Maf3::RotationAroundY(theta_y) * Maf3::RotationAroundZ(theta_z);
        const Maf3 rot_phi = Maf3::RotationAroundX(phi_x) * Maf3::RotationAroundY(phi_y) * Maf3::RotationAroundZ(phi_z);
        const Vef3 trans = { 0.0f,0.0f,offset_z };

        pipeline.effect.vertexshader.BindRotation(rot);
        pipeline.effect.vertexshader.BindTranslation(trans);
        pipeline.effect.vertexshader.SetLightDirection(light_dir * rot_phi);

        pipeline.Draw(itlist);
    }


private:
    IndexedTriangleList<Vertex> itlist;
    Pipeline pipeline;

    Vef3 light_dir = { 0.2f, -0.5f, 1.0f };

    static constexpr float dTheta = std::numbers::pi_v<float>;

    float offset_z = 2.0f;

    float theta_x = 0.0f;
    float theta_y = 0.0f;
    float theta_z = 0.0f;

    float phi_x = 0.0f;
    float phi_y = 0.0f;
    float phi_z = 0.0f;
};