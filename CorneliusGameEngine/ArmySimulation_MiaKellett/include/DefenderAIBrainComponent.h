#pragma once

//Project includes.
#include "Component.h"
#include "HealthComponent.h"
#include "Vector2.h"

//Library includes.
#include <string>

//Forward declarations.

//Class defintion.
class DefenderAIBrainComponent : public Component {
public:
	//Constructor and destructor.
	DefenderAIBrainComponent(Entity* a_ownerEntity, std::string a_teamTag, std::string a_enemyTag, HealthComponent* a_baseHealth, float a_moveSpeed, float a_seperationSpeed, int a_dmg, float a_cooldown, Vector2 a_defencePoint) : Component(a_ownerEntity) {
		m_baseHealth = a_baseHealth;
		m_teamTag = a_teamTag;
		m_enemyTag = a_enemyTag;
		m_moveSpeed = a_moveSpeed;
		m_seperationSpeed = a_seperationSpeed;
		m_defencePoint = a_defencePoint;

		m_dmg = a_dmg;
		m_attackCooldownTimerMax = a_cooldown;
		m_attackCooldownTimer = 0.0f;
	}
	~DefenderAIBrainComponent();

	// Main component functions.
	void Update(double a_deltaTime) override;
	std::string GetComponentID() const override {
		return "DefenderAIBrainComponent";
	}

private:
	//Private Variables.
	HealthComponent* m_baseHealth;
	std::string m_teamTag;
	std::string m_enemyTag;
	float m_moveSpeed;
	float m_seperationSpeed;
	Vector2 m_defencePoint;

	int m_dmg;
	float m_attackCooldownTimerMax;
	float m_attackCooldownTimer;

	//Private Functions.
	Vector2 HandleDodgingAlliesMovement();
	Entity* GetClosestEnemy();
};