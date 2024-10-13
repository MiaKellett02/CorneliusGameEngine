//Library includes.
#include <iostream>

//Project includes.
#include "Application.h"
#include "ArmySimulationScene.h"

//Functions.
int main(int argc, char* argv)
{
	//Startup the application.
	int applicationOutput = Application::Instance().SetupApplication();
	if (applicationOutput != 0) {
		return applicationOutput;
	}

	//Create the desired scenes.
	ArmySimulationScene* armyScene = new ArmySimulationScene("ArmyScene");

	//Add them to the application.
	Application::Instance().AddScene(armyScene);

	//Program running.
	Application::Instance().RunApplication();

	//Application end.
	Application::Instance().Shutdown();
	return 0;
}