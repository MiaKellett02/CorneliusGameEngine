#include "IsometricUnitMovementTestScene.h"
#include "Logging.h"
#include "InputHandler.h"
#include "DjikstraPathfinding.h"
#include "Timer.h"

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
	Vector2Int mousePos = InputHandler::GetMousePosition();
	Vector2Int mouseIsoPos = Application::Instance()->GetRenderer().GetIsometricGridPosFromScreenCoords(mousePos, true);
	/*CorneliusEngine::Log(("IsoPos(" + std::to_string(mouseIsoPos.x) + ", " + std::to_string(mouseIsoPos.y) + ")") +
						 (" MousePos(" + std::to_string(mousePos.x) + ", " + std::to_string(mousePos.y) + ")") +
						 (" CamOffset(" + std::to_string(Application::Instance()->GetRenderer().GetCameraOffset().x) + ", " + std::to_string(Application::Instance()->GetRenderer().GetCameraOffset().y) + ")"));*/

						 //Get some colours.
	Colour white(255, 255, 255);
	Colour grey(100, 100, 100);
	Colour red(255, 0, 0);

	//Check mouse button states.
	bool leftButtonPressed = InputHandler::LeftMouseButtonPressed();
	bool rightButtonPressed = InputHandler::RightMouseButtonPressed();
	bool isValidPosition = m_gameGrid.GetEnvironmentTilemap()->IsValidPosition(mouseIsoPos);

	if (leftButtonPressed && isValidPosition) {
		if (selectedPosOne == UNSELECTED_VALUE) {
			selectedPosOne = mouseIsoPos;
			//m_gameGrid.GetEnvironmentTilemap()->GetTile(mouseIsoPos).tint = red;
		}
		else if (selectedPosTwo == UNSELECTED_VALUE && !(selectedPosTwo == selectedPosOne)) {
			selectedPosTwo = mouseIsoPos;
			//m_gameGrid.GetEnvironmentTilemap()->GetTile(mouseIsoPos).tint = red;
		}
	}
	else if (rightButtonPressed) {
		//Clear the selections
		selectedPosOne = UNSELECTED_VALUE;
		selectedPosTwo = UNSELECTED_VALUE;
		calculatedPath.clear();
	}

	if (selectedPosOne == selectedPosTwo && selectedPosOne != UNSELECTED_VALUE) {
		selectedPosTwo = UNSELECTED_VALUE;
	}

	//If the positions have been selected.
	if (selectedPosOne != UNSELECTED_VALUE && selectedPosTwo != UNSELECTED_VALUE && !(selectedPosTwo == selectedPosOne) && calculatedPath.size() <= 0) {
		Timer timer("Pathfinding Setup & Findpath Timer");

		//Calculate path between and colour the all the positions found.
		std::vector<CorneliusEngine::DjikstraPosition> allPositions;
		for (int y = 0; y < m_gameGrid.GetEnvironmentTilemap()->GetHeight(); y++) {
			for (int x = 0; x < m_gameGrid.GetEnvironmentTilemap()->GetWidth(); x++) {
				Vector2Int currentPos(x, y);
				CorneliusEngine::DjikstraPosition newPos;
				newPos.position = currentPos;
				allPositions.push_back(newPos);
			}
		}

		//Setup connections between all nodes.
		for (int y = 0; y < m_gameGrid.GetEnvironmentTilemap()->GetHeight(); y++) {
			for (int x = 0; x < m_gameGrid.GetEnvironmentTilemap()->GetWidth(); x++) {
				Vector2Int currentPos(x, y);
				int currentPosIndex = -1;
				for (int i = 0; i < allPositions.size(); i++) {
					if (allPositions[i].position == currentPos) {
						currentPosIndex = i;
						break;
					}
				}

				if (x > 0) {
					Vector2Int leftPos(x - 1, y);
					for (int i = 0; i < allPositions.size(); i++) {
						if (allPositions[i].position == leftPos) {
							allPositions[currentPosIndex].MakeConnection(&allPositions[i], 1);
							break;
						}
					}
				}
				if (y > 0) {
					Vector2Int downPos(x, y - 1);
					for (int i = 0; i < allPositions.size(); i++) {
						if (allPositions[i].position == downPos) {
							allPositions[currentPosIndex].MakeConnection(&allPositions[i], 1);
							break;
						}
					}
				}
				if (x < m_gameGrid.GetEnvironmentTilemap()->GetWidth()) {
					Vector2Int rightPos(x + 1, y);
					for (int i = 0; i < allPositions.size(); i++) {
						if (allPositions[i].position == rightPos) {
							allPositions[currentPosIndex].MakeConnection(&allPositions[i], 1);
							break;
						}
					}
				}

				if (y < m_gameGrid.GetEnvironmentTilemap()->GetHeight()) {
					Vector2Int upPos(x, y + 1);
					for (int i = 0; i < allPositions.size(); i++) {
						if (allPositions[i].position == upPos) {
							allPositions[currentPosIndex].MakeConnection(&allPositions[i], 1);
							break;
						}
					}
				}
			}
		}

		//Calculate path.
		CorneliusEngine::DjikstraPosition* startPos = nullptr;
		CorneliusEngine::DjikstraPosition* goalPos = nullptr;
		for (int i = 0; i < allPositions.size(); i++) {
			if (allPositions[i].position == selectedPosOne) {
				startPos = &allPositions[i];
			}
			else if (allPositions[i].position == selectedPosTwo) {
				goalPos = &allPositions[i];
			}
		}
		calculatedPath = CorneliusEngine::DjikstraPathfinding::FindPath(startPos, goalPos);
		for (int i = 0; i < calculatedPath.size(); i++) {
			m_gameGrid.GetEnvironmentTilemap()->GetTile(calculatedPath[i]).tint = red;
		}
	}


	//Brighten the highlighted tile and make the others dark.
	if (calculatedPath.size() <= 0) {
		std::vector<IsometricTilemap::Tile> isoTiles = m_gameGrid.GetEnvironmentTilemap()->GetTilemapList();
		for (int y = 0; y < m_gameGrid.GetEnvironmentTilemap()->GetHeight(); y++) {
			for (int x = 0; x < m_gameGrid.GetEnvironmentTilemap()->GetWidth(); x++) {
				Vector2Int currentPos(x, y);
				int tileAccessIndex = x + y * m_gameGrid.GetEnvironmentTilemap()->GetWidth();

				if (x == mouseIsoPos.x && y == mouseIsoPos.y && currentPos != selectedPosOne && currentPos != selectedPosTwo) {
					//Make this bright white.
					m_gameGrid.GetEnvironmentTilemap()->GetTilemapList()[tileAccessIndex].tint = white;
				}
				else if (currentPos != selectedPosOne && currentPos != selectedPosTwo) {
					//Make this grey.
					m_gameGrid.GetEnvironmentTilemap()->GetTilemapList()[tileAccessIndex].tint = grey;
				}
			}
		}
	}
}

void IsometricUnitMovementTestScene::ShutdownScene()
{
}
