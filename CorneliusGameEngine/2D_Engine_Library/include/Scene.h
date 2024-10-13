#pragma once

//Project includes.

//Library includes.
#include <string>
#include <vector>

//Forward declarations.
class Entity;

//Class definition.
class Scene {
public:
	//Constructor and destructor.
	Scene(std::string a_sceneName);

	~Scene();

	//Standard Scene Functions.
	virtual void SetupScene() = 0;
	virtual void UpdateScene(double a_deltaTime);
	virtual void ShutdownScene();

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

	//Game entity variables.
	std::vector<Entity*> m_gameEntities;

	//Private Functions.
	void ShuffleEntities();
};