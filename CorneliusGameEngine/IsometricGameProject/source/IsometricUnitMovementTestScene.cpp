#include "IsometricUnitMovementTestScene.h"

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
}

void IsometricUnitMovementTestScene::ShutdownScene()
{
}
