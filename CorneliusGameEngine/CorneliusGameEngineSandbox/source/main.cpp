#include <iostream>
#include "CorneliusEngine.h"

int main(int argc, char* argv[]) {
	//Sandbox Entry point.
	std::cout << "\n--------------------------------------\nLoading Cornelius Engine Sandbox.\n--------------------------------------" << std::endl;

	//TODO: APPLICATION CLASS TO LOAD ENGINE AND RUN PROJECT.
	CorneliusEngine::Core::Application app = CorneliusEngine::Core::Application();
	bool applicationSuccessState = app.Run();

	//Handle application exit state.
	std::cout << "\nApplication has exited ";
	if (applicationSuccessState) {
		std::cout << "successfully." << std::endl;
	}
	else {
		std::cout << "with a failure state." << std::endl;
	}

	//Sandbox Exit Point.
	std::cout << "\n--------------------------------------\nPress any key to exit the application.\n--------------------------------------" << std::endl;
	std::cin.get();
	return 0;
}