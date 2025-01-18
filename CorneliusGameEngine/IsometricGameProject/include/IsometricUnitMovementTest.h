#pragma once

//Project includes.
#include "Scene.h"
#include "GameGrid.h"

//Library includes.
#include <string>

//Forward Declarations.
class GameGrid;

//Class defintion.
class IsometricUnitMovementTest : public Scene {
public:
	//Constructor and destructor.
	IsometricUnitMovementTest(std::string a_sceneName, int a_tileMapWidth, int a_tileMapHeight, const std::string& a_defaultTile) : Scene(a_sceneName, a_tileMapWidth, a_tileMapHeight, a_defaultTile) {

	}
	~IsometricUnitMovementTest();

	// Inherited via Scene
	void SetupScene() override;
	void UpdateScene(double a_deltaTime) override;
	void ShutdownScene() override;


private:
	GameGrid m_gameGrid;
};