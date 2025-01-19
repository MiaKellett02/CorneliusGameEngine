#pragma once

//Project includes.
#include "Scene.h"
#include "GameGrid.h"

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
};