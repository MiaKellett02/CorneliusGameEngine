//Project includes.
#include "ArmySimulationScene.h"
#include "Application.h"

//Function definitions.
ArmySimulationScene::~ArmySimulationScene()
{

}

void ArmySimulationScene::SetupScene()
{
	Scene::SetupScene();
	
	//Now all units have been created, shuffle them.
	ShuffleEntities();
}

void ArmySimulationScene::UpdateScene(double a_deltaTime)
{
	//Call the base class implementation that updates all the game entities.
	Scene::UpdateScene(a_deltaTime);
}

void ArmySimulationScene::ShutdownScene()
{
	//Call base implementation to shutdown the scene.
	Scene::ShutdownScene();

	//The game Base entities will get cleaned up by the "DestroyAllEntites" function in the base class definition.
}