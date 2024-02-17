#include "CameraController.hpp"

CameraController::CameraController(Mouse& in_mouse, const Keyboard& in_kbd, Camera& in_camera)
    :
    mouse(in_mouse),
	kbd(in_kbd),
    camera(in_camera)
{

}

void CameraController::Update(float deltaTime)
{
	if (kbd.KeyIsPressed('Q'))
	{
		camera.SetAngle(camera.GetAngle() + rotationSpeed * deltaTime);
	}
	if (kbd.KeyIsPressed('E'))
	{
		camera.SetAngle(camera.GetAngle() - rotationSpeed * deltaTime);
	}

    while ( ! mouse.IsEmpty() )
    {
        const auto e = mouse.Read();

        switch (e.GetType())
        {
        case Mouse::Event::Type::LPress:
            engaged = true;
            lastPosition = e.GetPosVef2();
            break;

        case Mouse::Event::Type::LRelease:
            engaged = false;
            break;

        case Mouse::Event::Type::WheelUp:
            camera.SetScale(camera.GetScale() * zoomFactor);
            break;

        case Mouse::Event::Type::WheelDown:
            camera.SetScale(camera.GetScale() / zoomFactor);
            break;

        default:
            break;
        }
    }

    if (engaged)
    {
        const Vef2 currentPosition = mouse.GetPosVef2();
        Vef2 deltaPosition = currentPosition - lastPosition;

        deltaPosition.x = -deltaPosition.x;
		deltaPosition.RotateBy( -camera.GetAngle() );
        camera.MoveBy(deltaPosition / camera.GetScale());

        lastPosition = currentPosition;
    }
}