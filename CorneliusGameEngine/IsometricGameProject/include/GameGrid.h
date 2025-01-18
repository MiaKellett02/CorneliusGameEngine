#pragma once

//Project includes.
#include "IsometricTilemap.h"

//Library includes.

//Class definition.
class GameGrid {
public:
	//Constructor and destructor.
	GameGrid() = default;

	GameGrid(int a_gridWidth, int a_gridHeight) {
		m_isometricTilemap = IsometricTilemap(a_gridWidth, a_gridHeight);
	}

	~GameGrid();

	//Getters and setters.
	IsometricTilemap& GetTilemap() {
		return m_isometricTilemap;
	}

private:
	IsometricTilemap m_isometricTilemap;
};