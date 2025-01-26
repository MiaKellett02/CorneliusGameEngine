#pragma once

//Project includes.
#include "Scene.h"
#include "GameGrid.h"
#include "DjikstraPathfinding.h"

//Library includes.
#include <string>

//Forward Declarations.
class GameGrid;

//Class defintion.
class IsometricUnitMovementTestScene : public Scene {
public:
	//Constructor and destructor.
	IsometricUnitMovementTestScene(std::string a_sceneName, int a_tileMapWidth, int a_tileMapHeight, const std::string& a_defaultTileSprite) : Scene(a_sceneName) {
		m_gameGrid = GameGrid(a_tileMapWidth, a_tileMapHeight, a_defaultTileSprite);
	}
	~IsometricUnitMovementTestScene();

	// Inherited via Scene
	void SetupScene() override;
	void UpdateScene(double a_deltaTime) override;
	void ShutdownScene() override;


private:
	GameGrid m_gameGrid;


	const Vector2Int UNSELECTED_VALUE = Vector2Int(-1, -1);

	Vector2Int selectedPosOne = UNSELECTED_VALUE;
	Vector2Int selectedPosTwo = UNSELECTED_VALUE;

	std::vector<Vector2Int> calculatedPath;

	std::vector<CorneliusEngine::DjikstraPosition> m_navmesh;
	std::vector<Vector2Int> m_checkedPositions;
	bool m_navmeshReset = false;

	//Private functions.
	void DoPathfinding();
	void ResetNavmesh();
	void SetupNavmesh();
};