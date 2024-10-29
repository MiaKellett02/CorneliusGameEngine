//Project includes.
#include "Application.h"
#include "Entity.h"
#include "Logging.h"

//Library includes.
#include <iostream>
#include <SDL.h>
#include <assert.h>
#include <thread>
#include <chrono>

// Static member initialization.
Application* Application::instance = nullptr;

//Functions.
int Application::SetupApplication(int a_targetFPS)
{
	CorneliusEngine::Log("Application setup called.");

	//Initialise any APIs here.
	int rendererInitOuput = m_renderer.Initialise(SCREEN_WIDTH, SCREEN_HEIGHT, IS_FULLSCREEN);
	if (rendererInitOuput != 0) {
		return rendererInitOuput;
	}

	//Setup application backend.
	m_activeScene = nullptr; //On first load the active scene should always be nullptr.
	m_targetFPS = a_targetFPS; //If no target is given for the application, fps will default to be as high as it can.

	//Return exit code of successfull.
	return 0;
}

void Application::RunApplication()
{
	//If the active scene is null then load the first one in the list of scenes.
	if (m_activeScene == nullptr) {
		assert(m_scenes.size() > 0); //Ensure there are always existing scenes.
		LoadSceneByIndex(0);
	}

	//Application loop.
	Uint32 lastFrameTime = SDL_GetTicks();
	double targetDeltaTime = 1.0 / m_targetFPS;

	while (!m_hasQuit) {
		//Calculate time since last frame and convert to seconds.
		Uint32 currentFrameTime = SDL_GetTicks();
		Uint32 elapsedTime = currentFrameTime - lastFrameTime;
		double deltaTime = elapsedTime / 1000.0;

		//If the frametime hasn't reached the target.
		//if (deltaTime <= targetDeltaTime) {
		//	//Don't update.
		//	continue;
		//}

		//std::cout << "fps: " << ((int)(1 / deltaTime)) << std::endl;

		//Poll any events.
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				break;
			}
		}

		//Update the game.
		for (int i = 0; i < m_scenes.size(); i++) {
			m_activeScene->UpdateScene(deltaTime);
		}

		//Render all scene entities.
		std::vector<Entity*>& sceneEntities = m_activeScene->GetAllEntities();
		m_renderer.Render(sceneEntities);

		//Cache current frame time.
		lastFrameTime = currentFrameTime;

		//Sleep till target deltatime reached.
		std::this_thread::sleep_for(std::chrono::milliseconds(((int)(targetDeltaTime * 1000))));
	}
}

void Application::Shutdown()
{
	m_renderer.Shutdown();
	CorneliusEngine::Log("Shutting down SDL.");
	SDL_Quit();

	CorneliusEngine::Log("Application has finished shutting down.");
}

void Application::LoadSceneByName(const std::string& a_sceneName)
{
	//Loop through all scenes in the game.
	for (int i = 0; i < m_scenes.size(); i++) {
		//Check if the current index scene is the desired scene.
		if (m_scenes[i]->GetSceneName() == a_sceneName) {
			//If there is a scene currently active.
			if (m_activeScene != nullptr) {
				//Unload the active scene.
				m_activeScene->ShutdownScene();
			}

			//Setup the desired scene.
			m_scenes[i]->SetupScene();

			//Replace the previous active scene with this scene.
			m_activeScene = m_scenes[i];

			//Exit the function as we have succesfully loaded the scene.
			return;
		}
	}

	CorneliusEngine::Log((("Could not find scene to load of name " + a_sceneName) + "."));
}

void Application::LoadSceneByIndex(const int& a_index)
{
	assert(a_index <= m_scenes.size() - 1); //Ensure the index is in bounds.

	//If there is a scene currently active.
	if (m_activeScene != nullptr) {
		//Unload the active scene.
		m_activeScene->ShutdownScene();
	}

	//Setup the desired scene.
	m_scenes[a_index]->SetupScene();

	//Replace the previous active scene with this scene.
	m_activeScene = m_scenes[a_index];
}

bool Application::IsPositionOutOfBound(Vector2& a_pos)
{
	//std::cout << "x: " << a_pos.GetX() << " y: " << a_pos.GetY() << std::endl;
	return a_pos.x < 0
		|| a_pos.x > Application::SCREEN_WIDTH
		|| a_pos.y < 0
		|| a_pos.y > Application::SCREEN_HEIGHT;
}
