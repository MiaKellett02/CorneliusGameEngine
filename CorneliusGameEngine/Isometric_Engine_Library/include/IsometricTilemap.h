#pragma once

//Library includes.
#include <vector>
#include <array>
#include <string>

//Project includes.
#include "Renderer.h"
#include "Colour.h"

//Class defintion.
class IsometricTilemap {
public:
	//Structs
	struct Tile {
		Colour tint;
		int textureID;

		Tile(Colour col, int texId) {
			tint = col;
			textureID = texId;
		}
	};

	//Constructor and destructor.
	IsometricTilemap() = default;

	IsometricTilemap(int a_width, int a_height, int a_tilesToReserve = 10) {
		m_width = a_width;
		m_height = a_height;

		//Reserve space for some tiles in the tile vector.
		m_tileSprites.reserve(a_tilesToReserve);

		//Construct the tilemap and default to the first tile available.
		Tile defaultTile = Tile(Colour(255, 255, 255), 0);
		m_tileMap = std::vector<Tile>(a_width * a_height, defaultTile);
	}

	//Functions.
	void AddNewTileSprite(const std::string& a_tileID, Renderer& a_renderer) {
		m_tileSprites.push_back(a_tileID);
		a_renderer.CreateTexture(a_tileID, a_tileID);
	}

	const std::string& GetTileTextureFromIndex(int a_index) {
		return m_tileSprites[a_index];
	}

	int GetWidth() {
		return m_width;
	}

	int GetHeight() {
		return m_height;
	}

	std::vector<Tile>& GetTilemapList() {
		return m_tileMap;
	}

private:
	std::vector<Tile> m_tileMap;
	std::vector<std::string> m_tileSprites;

	int m_width;
	int m_height;
};