#pragma once

//Forward Declarations.
class SDL_Window;
class SDL_Renderer;
class SDL_Surface;
class SDL_Texture;
class Entity;

//Library includes.
#include <vector>
#include <string>
#include <map>

class Renderer {
public:
	//Constructor and destructor.
	Renderer();
	~Renderer();

	//Main renderer Functions.
	int Initialise(int a_screenWidth, int a_screenHeight, bool fullScreen);
	void Render(std::vector<Entity*>& a_entitiesToRender);
	void Shutdown();

	//Functions to handle multiple textures.
	void CreateTexture(std::string a_textureID, std::string a_filepath);


private:
	//Private Variables.
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	//Texture variables.
	std::map<std::string, SDL_Texture*> m_textureMap;
};