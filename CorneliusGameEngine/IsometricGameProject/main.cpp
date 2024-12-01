//Library includes.
#include <iostream>

//Project includes.
#include "Application.h"

//Functions.
int main(int argc, char* argv)
{
	//Startup the application.
	Application app("Isometric Game Test", 1600, 900, false);

	//Move the camera by half the screen width.
	Vector2Int cameraPos = Vector2Int(400, 50);
	app.GetRenderer().SetCameraOffset(cameraPos);

	//Create the desired scenes and run the program..
	Scene armyScene("ArmyScene", 15, 15, "resources/IsometricTileTest.png");
	app.AddScene(&armyScene);

	app.RunApplication();

	//Application end.
	return 0;
}