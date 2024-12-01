#pragma once

//Project includes.
#include "IsometricTilemap.h"

//Library includes.
#include <string>
#include <vector>

//Forward declarations.
class Entity;

//Class definition.
class Scene {
public:
	//Constructor and destructor.
	Scene(std::string a_sceneName, int a_tileMapWidth, int a_tileMapHeight, const std::string& a_defaultTile);

	~Scene();

	//Standard Scene Functions.
	virtual void SetupScene();
	virtual void UpdateScene(double a_deltaTime);
	virtual void ShutdownScene();

	//Tilemap handling functions.
	IsometricTilemap& GetSceneTilemap() { return m_sceneTiles; }

	//Entity handling functions.
	Entity* GetEntityByName(const std::string& a_name);
	std::vector<Entity*> GetEntitiesWithTag(const std::string& a_tag);
	std::vector<Entity*>& GetAllEntities() { return m_gameEntities; }
	void DestroyEntity(Entity* a_entityToDestroy);
	void DestroyAllEntities();

	//Getters
	std::string GetSceneName() { return m_sceneName; }

protected:
	//Private/class inherited variables.
	std::string m_sceneName;
	bool m_sceneShutdown = false;

	//Scene variables.
	IsometricTilemap m_sceneTiles;

	//Game entity variables.
	std::vector<Entity*> m_gameEntities;

	//Private Functions.
	void ShuffleEntities();
};