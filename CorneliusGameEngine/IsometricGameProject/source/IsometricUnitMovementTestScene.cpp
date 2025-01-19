#include "IsometricUnitMovementTestScene.h"
#include "Logging.h"

IsometricUnitMovementTestScene::~IsometricUnitMovementTestScene()
{
}

void IsometricUnitMovementTestScene::SetupScene()
{
	//Add the gamegrid tilemaps to the scene list to render.
	m_sceneTilemaps.push_back(m_gameGrid.GetEnvironmentTilemap());
}

void IsometricUnitMovementTestScene::UpdateScene(double a_deltaTime)
{
	//Get the position of the mouse and use that to get the isometric coordinate it is hovering over..
	Vector2Int mousePos = Application::Instance()->GetRenderer().GetMousePosition();
	Vector2 mousePosFloat = Vector2(mousePos.x, mousePos.y);
	Vector2Int mouseIsoPos = Application::Instance()->GetRenderer().GetIsometricGridPosFromScreenCoords(mousePosFloat);
	//CorneliusEngine::Log(("MouseCoords = (" + std::to_string(mouseIsoPos.x) + ", " + std::to_string(mouseIsoPos.y) + ")"));


	//Brighten the highlighted tile and make the others dark.
	Colour white(255, 255, 255);
	Colour grey(100, 100, 100);
	std::vector<IsometricTilemap::Tile> isoTiles = m_gameGrid.GetEnvironmentTilemap()->GetTilemapList();
	for (int y = 0; y < m_gameGrid.GetEnvironmentTilemap()->GetHeight(); y++) {
		for (int x = 0; x < m_gameGrid.GetEnvironmentTilemap()->GetWidth(); x++) {
			int tileAccessIndex = x + y * m_gameGrid.GetEnvironmentTilemap()->GetWidth();

			if (x == mouseIsoPos.x && y == mouseIsoPos.y) {
				//Make this bright white.
				m_gameGrid.GetEnvironmentTilemap()->GetTilemapList()[tileAccessIndex].tint = white;
			}
			else {
				//Make this grey.
				m_gameGrid.GetEnvironmentTilemap()->GetTilemapList()[tileAccessIndex].tint = grey;
			}
		}
	}
}

void IsometricUnitMovementTestScene::ShutdownScene()
{
}
