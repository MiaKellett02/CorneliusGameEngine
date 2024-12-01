#pragma once

//Project includes.
#include "Scene.h"

//Library includes.
#include <string>

//Class defintion.
class ArmySimulationScene : public Scene {
public:
	//Constructor and destructor.
	ArmySimulationScene(std::string a_sceneName) : Scene(a_sceneName, 10, 10, "resources/Tiles/dirt_center_E.png") {

	}
	~ArmySimulationScene();

	// Inherited via Scene
	void SetupScene() override;
	void UpdateScene(double a_deltaTime) override;
	void ShutdownScene() override;

private:

};