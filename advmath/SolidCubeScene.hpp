#pragma once

#include "Scene.hpp"
#include "Cube.hpp"
#include "CubeScreenTransformer.hpp"

class SolidCubeScene : public Scene
{
public:
	SolidCubeScene() = default;


public:
	virtual void Update(Keyboard& kbd, Mouse& mouse, float deltaTime) override
	{
		if (kbd.KeyIsPressed('Q'))
		{
			theta_x = fatpound::math::wrap_angle(theta_x + deltaTheta * deltaTime);
		}
		if (kbd.KeyIsPressed('W'))
		{
			theta_y = fatpound::math::wrap_angle(theta_y + deltaTheta * deltaTime);
		}
		if (kbd.KeyIsPressed('E'))
		{
			theta_z = fatpound::math::wrap_angle(theta_z + deltaTheta * deltaTime);
		}

		if (kbd.KeyIsPressed('A'))
		{
			theta_x = fatpound::math::wrap_angle(theta_x - deltaTheta * deltaTime);
		}
		if (kbd.KeyIsPressed('S'))
		{
			theta_y = fatpound::math::wrap_angle(theta_y - deltaTheta * deltaTime);
		}
		if (kbd.KeyIsPressed('D'))
		{
			theta_z = fatpound::math::wrap_angle(theta_z - deltaTheta * deltaTime);
		}

		if (kbd.KeyIsPressed('R'))
		{
			offset_z += 2.0f * deltaTime;
		}
		if (kbd.KeyIsPressed('F'))
		{
			offset_z -= 2.0f * deltaTime;
		}
	}
	virtual void Draw(Graphics& gfx) const
	{
		IndexedTriangleList triangles = cube.GetTriangles();
		const Maf3& rotater = Maf3::RotationAroundX(theta_x) * Maf3::RotationAroundY(theta_y) * Maf3::RotationAroundZ(theta_z);

		for (auto& vertex : triangles.vertices)
		{
			vertex *= rotater;
			vertex += Vef3{ 0.0f, 0.0f, offset_z };
		}

		for (size_t i = 0ui64, end = triangles.indices.size() / 3ui64; i < end; ++i)
		{
			const Vef3& v0 = triangles.vertices[triangles.indices[i * 3ui64]];
			const Vef3& v1 = triangles.vertices[triangles.indices[i * 3ui64 + 1ui64]];
			const Vef3& v2 = triangles.vertices[triangles.indices[i * 3ui64 + 2ui64]];

			triangles.cullFlags[i] = (v1 - v0) % (v2 - v0) * v0 >= 0.0f;
		}

		for (auto& vertex : triangles.vertices)
		{
			cst.Transform(vertex);
		}

		for (size_t i = 0ui64, end = triangles.indices.size() / 3i64; i < end; ++i)
		{
			if (!triangles.cullFlags[i])
			{
				gfx.DrawTriangle(
					triangles.vertices[triangles.indices[i * 3ui64]],
					triangles.vertices[triangles.indices[i * 3ui64 + 1ui64]],
					triangles.vertices[triangles.indices[i * 3ui64 + 2ui64]],
					colors[i]
				);
			}
		}
	}


private:
	static constexpr float deltaTheta = std::numbers::pi_v<float>;

	static constexpr std::array<Color, 12> colors = {
		colors::White,
		colors::Blue,
		colors::Cyan,
		colors::Gray,
		colors::Green,
		colors::Magenta,
		colors::LightGray,
		colors::Red,
		colors::Yellow,
		colors::White,
		colors::Blue,
		colors::Cyan
	};

	CubeScreenTransformer cst;
	Cube cube = Cube(1.0f);

	float offset_z = 2.0f;
	float theta_x = 0.0f;
	float theta_y = 0.0f;
	float theta_z = 0.0f;
};