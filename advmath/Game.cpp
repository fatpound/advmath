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
#include "MainWindow.hpp"
#include "Game.hpp"
#include "SolidCubeScene.hpp"
#include "TexturedCubeScene.hpp"
#include "TexturedWrappedCubeScene.hpp"
#include "ConcaveHexahedronScene.hpp"
#include "ConcaveHexahedronWireScene.hpp"
#include "XMutualScene.hpp"

#include <sstream>

Game::Game( MainWindow& wnd )
    :
    wnd( wnd ),
    gfx( wnd )
{
    scenes.push_back(std::make_unique<SolidCubeScene>());
    scenes.push_back(std::make_unique<TexturedCubeScene>(1.0f));
    scenes.push_back(std::make_unique<TexturedCubeScene>(2.0f));
    scenes.push_back(std::make_unique<TexturedWrappedCubeScene>(2.0f));
    scenes.push_back(std::make_unique<TexturedWrappedCubeScene>(6.0f));
    scenes.push_back(std::make_unique<ConcaveHexahedronScene>());
    scenes.push_back(std::make_unique<ConcaveHexahedronWireScene>());
    scenes.push_back(std::make_unique<XMutualScene>());

    currentScene = scenes.begin();

    OutputSceneName();
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
        const std::wstring eMsg = e.GetFullMessage() + L"\n\nException caught at Windows message loop.";

        wnd.ShowMessageBox(
            e.GetExceptionType(),
            eMsg,
            MB_ICONERROR
        );
    }
    catch (const std::exception& e)
    {
        // need to convert std::exception what() string from narrow to wide string
        const std::string whatStr(e.what());
        const std::wstring eMsg = std::wstring(whatStr.begin(), whatStr.end()) + L"\n\nException caught at Windows message loop.";

        wnd.ShowMessageBox(
            L"Unhandled STL Exception",
            eMsg,
            MB_ICONERROR
        );
    }
    catch (...)
    {
        wnd.ShowMessageBox(
            L"Unhandled Non-STL Exception",
            L"\n\nException caught at Windows message loop.",
            MB_ICONERROR
        );
    }
}

void Game::UpdateModel()
{
    const float deltaTime = timer.Mark();
    //totalTime += deltaTime;

    while ( ! wnd.kbd.KeyIsEmpty() )
    {
        const Keyboard::Event event = wnd.kbd.ReadKey();

        if (event.GetCode() == VK_TAB && event.IsPress())
        {
            CycleScenes();
        }
        else if (event.GetCode() == VK_ESCAPE && event.IsPress())
        {
            wnd.Kill();
        }
    }

    (*currentScene)->Update(wnd.kbd, wnd.mouse, deltaTime);
}

void Game::CycleScenes()
{
    if (++currentScene == scenes.end())
    {
        currentScene = scenes.begin();
    }

    OutputSceneName();
}

void Game::OutputSceneName() const
{
    std::wstringstream ss;

    const std::wstring sceneName = (*currentScene)->GetName();
    const std::wstring stars(sceneName.size() + 4, '*');

    ss << stars << '\n'
        << "* " << sceneName << " *" << '\n'
        << stars << std::endl;

    OutputDebugString(ss.str().c_str());
}

void Game::ComposeFrame()
{
    (*currentScene)->Draw(gfx);
}