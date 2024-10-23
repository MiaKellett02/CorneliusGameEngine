//Library includes.
#include <iostream>

//Project includes.
#include "Application.h"
#include "ArmySimulationScene.h"

//Functions.
int main(int argc, char* argv)
{
	//Startup the application.
	Application app;

	//Create the desired scenes and run the program..
	ArmySimulationScene armyScene("ArmyScene");
	app.AddScene(&armyScene);

	app.RunApplication();

	//Application end.
	return 0;
}