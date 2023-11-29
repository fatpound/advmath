#pragma once

#include "Camera.hpp"
#include "Mouse.h"

class CameraController
{
public:
    CameraController(Mouse& in_mouse, Camera& in_camera);


public:
    void Update(float dt);


private:
    static constexpr float zoomFactor = 1.05f;

    Camera& camera;
    Mouse& mouse;

    Vef2 lastPosition = {0.0f, 0.0f};

    bool engaged = false;
};