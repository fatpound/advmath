/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "Star.hpp"

#include <random>
#include <array>

Game::Game( MainWindow& wnd )
    :
    wnd( wnd ),
    gfx( wnd ),
    coordinateTransformer( gfx ),
    camera( coordinateTransformer ),
    cameraCtrl( wnd.mouse, camera )
{
    std::default_random_engine drng(std::random_device{}());

    const std::array<Color, 6> colors = { color::Red, color::Green, color::Blue, color::Cyan, color::Yellow, color::Magenta };
    std::uniform_int_distribution<size_t> colorDist(0ui64, 5ui64);

    std::uniform_real_distribution<float> xDist(-worldWidth / 2.0f, worldWidth / 2.0f);
    std::uniform_real_distribution<float> yDist(-worldWidth / 2.0f, worldWidth / 2.0f);
	std::uniform_real_distribution<float> phaseDist(0.0f, 2.0f * std::numbers::pi_v<float>);
    std::uniform_real_distribution<float> rotationSpeedDist(minRotationSpeed, maxRotationSpeed);

    std::normal_distribution<float> radiusDist(meanStarRadius, devStarRadius);
    std::normal_distribution<float> ratioDist(meanStarInnerRatio, devStarInnerRatio);
    std::normal_distribution<float> flareCountDist(meanFlares, devFlares);
	std::normal_distribution<float> colorFrequencyDist(meanColorFrequency, devColorFrequency);

    while (stars.size() < starCount)
    {
        const Vef2 position = { xDist(drng), yDist(drng) };
        const float radius = std::clamp(radiusDist(drng), minStarRadius, maxStarRadius);

        if (std::any_of(stars.cbegin(), stars.cend(), [&](const Star& existingStar) {return (existingStar.GetPos() - position).Len() < (radius + existingStar.GetRadius()); }))
        {
            continue;
        }

        const Color color = colors[colorDist(drng)];
        const size_t flareCount = std::clamp(static_cast<size_t>(flareCountDist(drng)), minFlareCount, maxFlareCount);
        const float ratio = std::clamp(ratioDist(drng), minStarInnerRatio, maxStarInnerRatio);
        const float rotationSpeed = rotationSpeedDist(drng);
		const float colorFrequency = std::clamp(colorFrequencyDist(drng), minColorFrequency, maxColorFrequency);
		const float colorPhase = phaseDist(drng);

        stars.emplace_back(position, radius, ratio, flareCount, color, rotationSpeed, colorFrequency, colorPhase);
    }
}

void Game::Go()
{
    try
    {
        while (wnd.ProcessMessage())
        {
            gfx.BeginFrame();
            UpdateModel();
            ComposeFrame();
            gfx.EndFrame();
        }
    }
    catch (const ChiliException& e)
    {
        const std::wstring eMsg = e.GetFullMessage() +
            L"\n\nException caught at Windows message loop.";
        wnd.ShowMessageBox(e.GetExceptionType(), eMsg, MB_ICONERROR);
    }
    catch (const std::exception& e)
    {
        // need to convert std::exception what() string from narrow to wide string
        const std::string whatStr(e.what());
        const std::wstring eMsg = std::wstring(whatStr.begin(), whatStr.end()) +
            L"\n\nException caught at Windows message loop.";
        wnd.ShowMessageBox(L"Unhandled STL Exception", eMsg, MB_ICONERROR);
    }
    catch (...)
    {
        wnd.ShowMessageBox(L"Unhandled Non-STL Exception",
            L"\n\nException caught at Windows message loop.", MB_ICONERROR);
    }
}

void Game::UpdateModel()
{
    const float deltaTime = frameTimer.Mark();

    totalTime += deltaTime;

    for (auto& star : stars)
    {
        star.Update(deltaTime);
    }

    cameraCtrl.Update(deltaTime);
}

void Game::ComposeFrame()
{
    for (const auto& star : stars)
    {
        camera.Draw(star.GetDrawable());
    }
}