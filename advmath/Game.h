/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Star.hpp"
#include "CoordinateTransformer.hpp"
#include "Camera.hpp"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator = ( const Game& ) = delete;


public:
	void Go();


private:
	void ComposeFrame();
    void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/


private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
    static constexpr size_t starCount = 100ui64;
    static constexpr size_t maxFlareCount = 10;
    static constexpr size_t minFlareCount = 3;

    static constexpr float worldWidth = 3000.0f;
    static constexpr float worldHeight = 1000.0f;

    static constexpr float meanFlares = 6.5f;
    static constexpr float devFlares = 2.0f;

    static constexpr float meanStarRadius = 160.0f;
    static constexpr float devStarRadius = 90.0f;
    static constexpr float maxStarRadius = 300.0f;
    static constexpr float minStarRadius = 40.0f;

    static constexpr float meanStarInnerRatio = 0.4f;
    static constexpr float devStarInnerRatio = 0.25f;
    static constexpr float maxStarInnerRatio = 0.8f;
    static constexpr float minStarInnerRatio = 0.15f;

    std::vector<Star> stars;

    CoordinateTransformer coordinateTransformer;
    Camera camera;
	/********************************/
};