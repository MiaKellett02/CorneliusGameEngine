#pragma once

//Forward Declarations.
class Entity;

//Project includes.
#include "Renderer.h"
#include "Vector2.h"
#include "Scene.h"

//Library includes.
#include <vector>
#include <string>

//Class definition.
class Application {
public:
	//Singleton class as Application needs to be globally accessible
	//	so that entities can interact with other entities.
	static Application* Instance() {
		return instance;
	}

	//Constructor and deconstructor.
	Application(const std::string& a_appName, int a_defaultScreenWidth, int a_defaultScreenHeight, bool a_isFullScreen, bool a_runAtMonitorResolution)
	{
		//Ensure there is an instance set for the class.
		//We assign the instance in the constructor so initialisation is kept explicit and not lazy.
		instance = this;

		a_runAtMonitorResolution = a_runAtMonitorResolution && a_isFullScreen;  // Only will run at the monitor resolution if fullscreen.
																			    // Otherwise, run at default resolutions passed in.
																			    // We still have a separate variable for running at monitor resolution
																			    //	as it allows flexibility for running fullscreen at lower resolutions
																				//	for performance related purposes.

		// Will be overwritten by monitor width&height, 
		// inside the renderer initialisation if "a_runAtMonitorResolution" is true.
		SCREEN_WIDTH = a_defaultScreenWidth;
		SCREEN_HEIGHT = a_defaultScreenHeight;

		IS_FULLSCREEN = a_isFullScreen;
		SetupApplication(a_appName, a_runAtMonitorResolution);
	};
	~Application() { Shutdown(); };


	//Application handling functions.
	void RunApplication();
	void QuitApplication() { m_hasQuit = true; }

	//Scene Handling Functions.
	void AddScene(Scene* a_newScene) { m_scenes.push_back(a_newScene); }
	void LoadSceneByName(const std::string& a_sceneName);
	void LoadSceneByIndex(const int& a_index);
	Scene* GetActiveScene() { return m_activeScene; }

	//Utility.
	bool IsPositionOutOfBound(Vector2& a_pos);
	Renderer& GetRenderer() { return m_renderer; }

	//Public variables.
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	bool IS_FULLSCREEN;

private:
	//singleton instance.
	static Application* instance;

	//Backend Engine systems.
	Renderer m_renderer;

	//Scene handling variables.
	std::vector<Scene*> m_scenes;
	Scene* m_activeScene = nullptr;

	//Functions.
	void SetupApplication(const std::string& a_appName, bool a_runAtMonitorResolution);
	void Shutdown();

	//Consts.
	int m_targetFPS = 100000000;
	bool m_hasQuit = false;
};