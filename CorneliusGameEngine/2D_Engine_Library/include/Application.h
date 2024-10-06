#pragma once

//Forward Declarations.
class Entity;

//Project includes.
#include "Renderer.h"
#include "Vector2.h"
#include "HealthComponent.h"

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

	//Public functions.
	int Initialise();
	void Start();
	void Run();
	void Shutdown();

	//Entity handling functions.
	Entity* GetEntityByName(const std::string& a_name);
	std::vector<Entity*> GetEntitiesWithTag(const std::string& a_tag);
	void DestroyEntity(Entity* a_entityToDestroy);
	void DestroyAllEntities();

	Entity* GetRedBase() { return m_redBaseHealth->GetOwnerEntity(); }
	Entity* GetBlueBase() { return m_blueBaseHealth->GetOwnerEntity(); }

	//Utility.
	bool IsPositionOutOfBound(Vector2& a_pos);

	//Consts.
	const int SCREEN_WIDTH = 1600;
	const int SCREEN_HEIGHT = 900;
	const bool IS_FULLSCREEN = false;

	//Enums.
	enum WinConditions {
		none,
		RedWin,
		BlueWin,
		Draw
	};

private:
	//Essential game systems.
	Renderer m_renderer;

	//Game entity variables.
	std::vector<Entity*> m_gameEntities;


	//Private Functions.
	void ShuffleEntities();
	
	//Win conditions.
	WinConditions CheckWinConditions();
	WinConditions m_gameWonCondition = none;
	HealthComponent* m_redBaseHealth;
	HealthComponent* m_blueBaseHealth;
	bool gameOver = false;

	//Constructor and deconstructor.
	Application();
	~Application();

	//Consts.
	const int TARGET_FPS = 31;
};