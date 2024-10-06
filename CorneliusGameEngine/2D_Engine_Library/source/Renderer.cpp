//Project includes.
#include "Renderer.h"
#include "Entity.h"

//Library includes
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

//Functions.
Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

int Renderer::Initialise(int a_screenWidth, int a_screenHeight, bool fullScreen)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
		std::cout << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
		return 1;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0) {
		std::cout << "Unable to initialise SDL2_image." << std::endl;
		return 2;
	}

	//Create the window.
	if (fullScreen) {
		m_window = SDL_CreateWindow("Army Simulation - Mia Kellett", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, a_screenWidth, a_screenHeight, SDL_WINDOW_FULLSCREEN);
	}
	else {
		m_window = SDL_CreateWindow("Army Simulation - Mia Kellett", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, a_screenWidth, a_screenHeight, SDL_WINDOW_OPENGL);
	}

	//Ensure the window was correctly initialised.
	if (m_window == NULL) {
		std::cout << "Unable to initialise program window." << std::endl;
		return 3;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (m_renderer == NULL) {
		std::cout << "Unable to initialise renderer." << std::endl;
		return 4;
	}

	//If we get here then the renderer has been initialised successfully.
	std::cout << "SDL has been initialised." << std::endl;
	return 0;
}

void Renderer::Render(std::vector<Entity*>& a_entitiesToRender)
{
	//Clear the screen.
	SDL_RenderClear(m_renderer);

	//Ensure all entities are copied to the renderer.
	for (int i = 0; i < a_entitiesToRender.size(); i++) {
		Entity* entity = a_entitiesToRender[i]; //Get the entity.

		//Construct the rect for it to be rendered in.
		SDL_Rect renderRect;
		renderRect.x = (int)entity->GetScreenPos().x; //pos x
		renderRect.y = (int)entity->GetScreenPos().y; //pos y
		renderRect.w = (int)entity->GetSize().x; //width
		renderRect.h = (int)entity->GetSize().y; //height

		//Get the texture.
		SDL_Texture* entityTexture = m_textureMap[entity->GetTexID()];

		//Render the entity.
		SDL_RenderCopy(m_renderer, entityTexture, NULL, &renderRect);
	}

	//Draw to the screen.
	SDL_RenderPresent(m_renderer);
}

void Renderer::Shutdown()
{
	std::cout << "Shutting down renderer." << std::endl;
	//Destroy all textures in the map.
	for (auto& texturePair : m_textureMap) {
		SDL_Texture* texture = texturePair.second;
		SDL_DestroyTexture(texture);
	}

	//Destroy the SDL components for the renderer..
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	IMG_Quit();
}

void Renderer::CreateTexture(std::string a_textureID, std::string a_filepath)
{
	//Check if the texture already exists in the map.
	if (m_textureMap.count(a_textureID) > 0) {
		//std::cout << a_textureID << " has already been initialised." << std::endl;
		return; //Early out as we don't need to recreate the texture.
	}

	//Load the image..
	SDL_Surface* imgSurface = IMG_Load(a_filepath.c_str());
	if (imgSurface == NULL) {
		std::cout << "Unable to load image: " << IMG_GetError() << std::endl;
		return;
	}

	//Create the texture.
	SDL_Texture* imgTexture = SDL_CreateTextureFromSurface(m_renderer, imgSurface);
	if (imgTexture == NULL) {
		std::cout << "Unable to create texture.";
		return;
	}

	//Add it to the map.
	m_textureMap[a_textureID] = imgTexture;
	std::cout << "Added " << a_textureID << " to the texture map." << std::endl;

	//Free the surface memory as it is no longer needed.
	SDL_FreeSurface(imgSurface);
}
