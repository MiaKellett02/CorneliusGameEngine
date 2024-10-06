#pragma once

//Project Includes.
#include "Vector2.h"

//Library Includes
#include <string>

//Forward declarations.
class Entity;

class Component {
public:
	//Constructor and destructor.
	Component(Entity* a_ownerEntity);
	virtual ~Component();

	//Gets.
	Entity* GetOwnerEntity() { return m_ownerEntity; }

	//Main component functions.
	virtual void Update(double a_deltaTime) = 0;

	//Component ID functions.
	virtual std::string GetComponentID() const {
		return "Component";
	}

protected:
	//Variables.
	Entity* m_ownerEntity;
	Vector2 m_velocity;
};