# Cornelius Game Engine

## This is a basic 2D Game engine developed to help improve my C++ Technical Skills and lower level programming knowledge.

### Description
A basic 2D game engine that will focus on creating a framework to make it as easy as possible to create 2D games. This will be used as research for me to learn how to make a good game engine framework before moving onto 3D.

### Link to View Project Design Documentation

### Technologies Used (List may expand as project is developed.):
 - Visual Studio 2022 has been used for development and compilation up to C++20 and C standard 17.
 - SDL2 is going to be used to load textures for it's wide variety of cross platform support and it's native compatibility to work within C++.

## Engine Structure
### Engine Framework Project
 - The engine framework project contains all the generic functionality that any game or simulation might require to be made.
 - This project builds into a static library that allows any projects using the engine to access the function definitions of all project header files.

### Engine Sandbox Project.
 - This is an example project that uses the engine framework to create a game.
 - This project builds into an executable that can be run on the platform it was built for.

## How to install/run/use this project.
### Installation and setup instructions.
 1. Clone the repository to your machine.
 2. Open the Visual Studio 2022 Solution Named "CorneliusGameEngine.sln".
 3. Set the "CorneliusGameEngineSandbox" project as the startup project.
 4. Ensure the "CorneluisGameEngineFramework" project is set as a dependency of the sandbox project. (This project builds the engine library that the sandbox relies on.)

### How to run the project.
 1. Build the "CorneliusGameEngine" Solution (Both projects will place the output files within the "bin" subfolder of each project and then separated further into their configuration and platform).
 2. Go to the Sandbox project's directory, open the binary folder and locate the generated executable.
 3. Run the generated Executable (You should at minimum be greeted by a console window with any messages that the engine has for you).

### How to use this project.


## License and Credits.
### License
 - This project is under the GNU GPLv3 License.

### Credits
 - 
