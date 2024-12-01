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
	Application(const std::string& a_appName, int a_screenWidth, int a_screenHeight, bool a_isFullScreen)
	{
		instance = this;

		SCREEN_WIDTH = a_screenWidth;
		SCREEN_HEIGHT = a_screenHeight;
		IS_FULLSCREEN = a_isFullScreen;
		SetupApplication(a_appName);
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
	int SetupApplication(const std::string& a_appName);
	void Shutdown();

	//Consts.
	int m_targetFPS = 100000000;
	bool m_hasQuit = false;
};