#pragma once

#include "FatMath.hpp"
#include "Scene.hpp"
#include "Cube.hpp"
#include "Mat3.hpp"
#include "Pipeline.hpp"
#include "VertexColorEffect.hpp"

class CubeVertexColorScene : public Scene
{
public:
    typedef Pipeline<VertexColorEffect> Pipeline;
    typedef Pipeline::Vertex Vertex;


public:
    CubeVertexColorScene(Graphics& gfx)
        :
        Scene(L"Colored cube vertex gradient scene"),
        itlist(Cube::GeneratePlain<Vertex>()),
        pipeline(gfx)
    {
        itlist.vertices[0].color = Vef3(Red);
        itlist.vertices[1].color = Vef3(Green);
        itlist.vertices[2].color = Vef3(Blue);
        itlist.vertices[3].color = Vef3(Yellow);
        itlist.vertices[4].color = Vef3(Cyan);
        itlist.vertices[5].color = Vef3(Magenta);
        itlist.vertices[6].color = Vef3(White);
        itlist.vertices[7].color = Vef3(Black);
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
        const Maf3 rot = Maf3::RotationAroundX(theta_x) * Maf3::RotationAroundY(theta_y) * Maf3::RotationAroundZ(theta_z);
        const Vef3 trans = Vef3( 0.0f,0.0f,offset_z );

        pipeline.BindRotation(rot);
        pipeline.BindTranslation(trans);

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
};