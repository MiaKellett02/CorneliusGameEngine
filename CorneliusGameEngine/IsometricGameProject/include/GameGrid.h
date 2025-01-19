#pragma once

//Project includes.
#include "IsometricTilemap.h"
#include "Application.h"

//Library includes.

//Class definition.
class GameGrid {
public:
	//Constructor and destructor.
	GameGrid() = default;

	GameGrid(int a_gridWidth, int a_gridHeight, const std::string& a_defaultTileSprite) {
		m_environmentTilemap = IsometricTilemap("_environment", a_gridWidth, a_gridHeight);

		m_environmentTilemap.AddNewTileType("_default", a_defaultTileSprite, Application::Instance()->GetRenderer());

		//On each odd x and y tile, tint it bright red.
		Colour red = Colour(255, 0, 0);
		for (int y = 0; y < m_environmentTilemap.GetHeight(); y++) {
			for (int x = 0; x < m_environmentTilemap.GetWidth(); x++) {
				if (((x + 1) % 2 != 0 && (y + 1) % 2 != 0) || ((x + 1) % 2 == 0 && (y + 1) % 2 == 0)) {
					//m_environmentTilemap.GetTilemapList()[x + y * m_environmentTilemap.GetWidth()].tint = red;
				}
				int radius = 1;
				if (x + 1 >= (m_environmentTilemap.GetWidth() / 2) - radius &&
					x + 1 <= (m_environmentTilemap.GetWidth() / 2) + radius &&
					y + 1 >= (m_environmentTilemap.GetHeight() / 2) - radius &&
					y + 1 <= (m_environmentTilemap.GetHeight() / 2) + radius) {

				}
				else {
					m_environmentTilemap.GetTilemapList()[x + y * m_environmentTilemap.GetWidth()].tint.Darken(0.1f);
				}
			}
		}
	}

	~GameGrid();

	//Getters and setters.
	IsometricTilemap* GetEnvironmentTilemap() {
		return &m_environmentTilemap;
	}

private:
	IsometricTilemap m_environmentTilemap;
};