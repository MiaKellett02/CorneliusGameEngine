#pragma once

//Project includes.
#include "Component.h"
#include "Vector2.h"
#include "Entity.h"

//Library includes.

//Forward Declarations.

//Class definition.
class HealthComponent : public Component {
public:
	//Constructor and destructor.
	HealthComponent(Entity* a_ownerEntity, int a_maxHealth) : Component(a_ownerEntity) {
		m_maxHealth = a_maxHealth;
		m_currentHealth = a_maxHealth;

		m_originalSize = a_ownerEntity->GetSize();
	}
	~HealthComponent();

	//Main component functions.
	void Update(double a_deltaTime) override;

	//Health specific functions.
	void Damage(int a_damage);
	void Heal(int a_healthIncrease);
	void DestroyIfDead();
	int GetHealthPoints() { return m_currentHealth; }

	//Component ID functions.
	std::string GetComponentID() const override {
		return "HealthComponent";
	}
private:
	int m_maxHealth;
	int m_currentHealth;

	//Size variable for showing health changes.
	Vector2 m_originalSize;


	//Functions.
	void UpdateSize();
};