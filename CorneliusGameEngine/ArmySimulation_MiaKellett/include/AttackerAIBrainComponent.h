#pragma once
//Project includes.
#include "Component.h"
#include "HealthComponent.h"
#include "Vector2.h"

//Library includes.
#include <string>

//Forward declarations.

//Class definition.
class AttackerAIBrainComponent : public Component {
public:
	//Constructor and destructor.
	AttackerAIBrainComponent(Entity* a_ownerEntity, std::string a_teamTag, std::string a_enemyTag, HealthComponent* a_baseHealth, float a_moveSpeed, float a_seperationSpeed, int a_dmg, float a_cooldown) : Component(a_ownerEntity) {
		m_baseHealth = a_baseHealth;
		m_teamTag = a_teamTag;
		m_enemyTag = a_enemyTag;
		m_moveSpeed = a_moveSpeed;
		m_seperationSpeed = a_seperationSpeed;

		m_dmg = a_dmg;

		m_attackCooldownTimerMax = a_cooldown;
		m_attackCooldownTimer = 0.0f;
	}
	~AttackerAIBrainComponent();

	// Main component functions.
	void Update(double a_deltaTime) override;
	std::string GetComponentID() const override {
		return "AttackerAIBrainComponent";
	}

private:
	//Private Variables.
	HealthComponent* m_baseHealth;
	std::string m_teamTag;
	std::string m_enemyTag;
	float m_moveSpeed;
	float m_seperationSpeed;

	int m_dmg;

	float m_attackCooldownTimerMax;
	float m_attackCooldownTimer;

	//Private Functions.
	Vector2 HandleDodgingAlliesMovement();
	Vector2 HandleDodgingEnemies();
	Vector2 MoveTowardsClosestEnemy(Entity* a_enemy);
	
	Entity* GetClosestEnemy();
};