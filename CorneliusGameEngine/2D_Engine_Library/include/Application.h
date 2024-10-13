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
	static Application& Instance() {
		static Application instance;
		return instance;
	}

	//Application handling functions.
	int SetupApplication();
	void RunApplication();
	void Shutdown();

	//Scene Handling Functions.
	void AddScene(Scene* a_newScene) { m_scenes.push_back(a_newScene); }
	void LoadSceneByName(const std::string& a_sceneName);
	void LoadSceneByIndex(const int& a_index);
	Scene* GetActiveScene() { return m_activeScene; }

	//Utility.
	bool IsPositionOutOfBound(Vector2& a_pos);
	Renderer& GetRenderer() { return m_renderer; }

	//Consts.
	static const int SCREEN_WIDTH = 1600;
	static const int SCREEN_HEIGHT = 900;
	static const bool IS_FULLSCREEN = false;

private:
	//Backend Engine systems.
	Renderer m_renderer;

	//Scene handling variables.
	std::vector<Scene*> m_scenes;
	Scene* m_activeScene = nullptr;

	//Constructor and deconstructor.
	Application();
	~Application();

	//Consts.
	const int TARGET_FPS = 31;
};