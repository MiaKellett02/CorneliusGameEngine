//Library includes.
#include <iostream>

//Project includes.
#include "Application.h"

//Functions.
int main(int argc, char* argv)
{
	//Startup
	int applicationOutput = Application::Instance().Initialise();
	if (applicationOutput != 0) {
		return applicationOutput;
	}

	//Program running.
	Application::Instance().Run();

	//Application end.
	Application::Instance().Shutdown();
	return 0;
}