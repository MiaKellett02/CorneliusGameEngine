#pragma once

//Forward Declarations.
class Entity;

//Project includes.
#include "Renderer.h"
#include "Vector2.h"
#include "Scene.h"

//Library includes.
#include <vector>

class Application {
public:
	//Singleton class as Application needs to be globally accessible
	//	so that entities can interact with other entities.
	static Application* Instance() {
		return instance;
	}

	//Constructor and deconstructor.
	Application()
	{
		instance = this;
		SetupApplication(60);
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

	//Consts.
	static const int SCREEN_WIDTH = 1920;
	static const int SCREEN_HEIGHT = 1080;
	static const bool IS_FULLSCREEN = true;

private:
	//singleton instance.
	static Application* instance;


	//Backend Engine systems.
	Renderer m_renderer;

	//Scene handling variables.
	std::vector<Scene*> m_scenes;
	Scene* m_activeScene = nullptr;

	//Functions.
	int SetupApplication(int a_targetFPS = 100000000);
	void Shutdown();

	//Consts.
	int m_targetFPS = 100000000;
	bool m_hasQuit = false;
};