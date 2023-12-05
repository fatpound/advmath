#pragma once

#include "Camera.hpp"
#include "Mouse.h"
#include "Keyboard.h"

#include <numbers>

class CameraController
{
public:
    CameraController(Mouse& in_mouse, const Keyboard& in_kbd, Camera& in_camera);


public:
    void Update(float dt);


private:
    static constexpr float zoomFactor = 1.05f;
	static constexpr float rotationSpeed = std::numbers::pi_v<float> / 6.0f;
	
    Camera& camera;
    Mouse& mouse;
	const Keyboard& kbd;

    Vef2 lastPosition = {0.0f, 0.0f};

    bool engaged = false;
};