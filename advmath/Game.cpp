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

using fatpound::math::Maf3;

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	cube(1.0f)
{

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
	const float deltaTime = ft.Mark();
	totalTime += deltaTime;

	if (wnd.kbd.KeyIsPressed('Q'))
	{
		theta_x += deltaTheta * deltaTime;
	}
	if (wnd.kbd.KeyIsPressed('W'))
	{
		theta_y += deltaTheta * deltaTime;
	}
	if (wnd.kbd.KeyIsPressed('E'))
	{
		theta_z += deltaTheta * deltaTime;
	}

	if (wnd.kbd.KeyIsPressed('A'))
	{
		theta_x -= deltaTheta * deltaTime;
	}
	if (wnd.kbd.KeyIsPressed('S'))
	{
		theta_y -= deltaTheta * deltaTime;
	}
	if (wnd.kbd.KeyIsPressed('D'))
	{
		theta_z -= deltaTheta * deltaTime;
	}
}

void Game::ComposeFrame()
{
	IndexedLineList lines = cube.GetLines();
	const Maf3 rotater = Maf3::RotationAroundX(theta_x) * Maf3::RotationAroundY(theta_y) * Maf3::RotationAroundZ(theta_z);

	for (auto& vertex : lines.vertices)
	{
		vertex *= rotater;
		vertex += Vef3{ 0.0f, 0.0f, 1.0f };
		cst.Transform(vertex);
	}

	for (auto it = lines.indices.cbegin(), end = lines.indices.cend(); it != end; std::advance(it, 2))
	{
		gfx.DrawLine(lines.vertices[*it], lines.vertices[*std::next(it)], colors::White);
	}
}