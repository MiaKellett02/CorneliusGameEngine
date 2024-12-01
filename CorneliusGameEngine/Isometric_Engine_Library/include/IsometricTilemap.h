#pragma once

//Library includes.
#include <vector>
#include <array>
#include <string>

//Project includes.
#include "Renderer.h"

//Class defintion.
class IsometricTilemap {
public:
	//Constructor and destructor.
	IsometricTilemap() {}
	IsometricTilemap(int a_width, int a_height, int a_tilesToReserve = 10) {
		m_width = a_width;
		m_height = a_height;

		//Reserve space for some tiles in the tile vector.
		m_tiles.reserve(10);

		//Construct the tilemap and default to the first tile available.
		m_tileMap = std::vector<int>(a_width * a_height, 0);
	}

	//Functions.
	void AddTile(const std::string& a_tileID, Renderer& a_renderer) {
		m_tiles.push_back(a_tileID);
		a_renderer.CreateTexture(a_tileID, a_tileID);
	}

	const std::string& GetTileTextureFromIndex(int a_index) {
		return m_tiles[a_index];
	}

	int GetWidth() {
		return m_width;
	}

	int GetHeight() {
		return m_height;
	}

	std::vector<int>& GetTilemapList() {
		return m_tileMap;
	}

private:
	std::vector<int> m_tileMap;
	std::vector<std::string> m_tiles;

	int m_width;
	int m_height;
};