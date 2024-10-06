#include "DefenderAIBrainComponent.h"
#include "Application.h"

//Libary includes.
#include <iostream>

DefenderAIBrainComponent::~DefenderAIBrainComponent()
{
}

void DefenderAIBrainComponent::Update(double a_deltaTime)
{
	//===============
	//HANDLE MOVEMENT
	//===============
	//Figure out how much we should be moving by.
	Vector2 totalMovement = HandleDodgingAlliesMovement();

	//Figure out movement.
	Vector2 moveDir = m_defencePoint - m_ownerEntity->GetPosition();
	if (moveDir.SqrMagnitude() < ((m_ownerEntity->GetSize().x * 2) * (m_ownerEntity->GetSize().x * 2))) {
		moveDir = Vector2(0, 0);
	}
	totalMovement = totalMovement + moveDir;

	//If the movement would put the entity out of bounds, move them in the opposite direction.
	Vector2 boundsTest = m_ownerEntity->GetPosition() + (totalMovement * (float)a_deltaTime);
	if (Application::Instance().IsPositionOutOfBound(boundsTest)) {
		//Out of bounds so weight movement to center.
		Vector2 center = Vector2(Application::Instance().SCREEN_WIDTH / 2, Application::Instance().SCREEN_HEIGHT / 2);
		Vector2 moveDir = (center - m_ownerEntity->GetPosition()) * m_seperationSpeed * 2;
		totalMovement = totalMovement + moveDir;
	}

	//Calculate velocity.
	m_velocity = m_velocity + totalMovement;

	//Apply the velocity.
	m_velocity.Normalize();
	m_velocity = m_velocity * m_moveSpeed;
	m_ownerEntity->ChangePosition(m_velocity * (float)a_deltaTime);

	//================
	//HANDLE ATTACKING
	//================
	//Get closest enemy.
	Entity* closestEnemy = GetClosestEnemy();
	if (closestEnemy == nullptr || m_ownerEntity == nullptr) {
		return; //Null check early out.
	}

	bool canAttack = (closestEnemy->GetPosition() - m_ownerEntity->GetPosition()).SqrMagnitude() < ((m_ownerEntity->GetSize().x / 2) * (m_ownerEntity->GetSize().x / 2));
	if (!canAttack) {
		return; //Can't attack so early out.
	}

	//can attack so run timer..
	m_attackCooldownTimer -= (float)a_deltaTime;
	if (m_attackCooldownTimer <= 0.0f) {
		//Timer has elapsed so reset.
		m_attackCooldownTimer = m_attackCooldownTimerMax;

		//Do dmg to the closest enemy.
		Component* component = closestEnemy->GetComponentByID("HealthComponent");
		if (component != nullptr) {
			HealthComponent* health = (HealthComponent*)component;
			health->Damage(m_dmg);
		}
	}
}

Vector2 DefenderAIBrainComponent::HandleDodgingAlliesMovement()
{
	//Get a list of all allies that currently exist.
	Vector2 alliesInRangeAveragePosition;
	int alliesInRangeCount = 0;
	std::vector<Entity*> allies = Application::Instance().GetEntitiesWithTag(m_teamTag);
	for (int i = 0; i < allies.size(); i++) {
		Entity* ally = allies[i];
		if (ally == m_ownerEntity) {
			continue; //Skip this iteration as it's the current entity.
		}

		//What is the distance to the ally.
		float distanceSqr = (ally->GetPosition() - m_ownerEntity->GetPosition()).SqrMagnitude();

		//Dodge allies that are less than the width away from the center of the entity
		if (distanceSqr < (m_ownerEntity->GetSize().x * m_ownerEntity->GetSize().x * 5)) {
			//Add this current ally to the total.
			alliesInRangeAveragePosition = alliesInRangeAveragePosition + ally->GetPosition();

			//Increment counter.
			alliesInRangeCount++;
		}
	}

	//Figure out average by dividing by the number of allies found - 1.
	if (alliesInRangeCount > 0) {
		alliesInRangeAveragePosition = alliesInRangeAveragePosition / (float)alliesInRangeCount;
	}

	//Figure out direction to move in.
	Vector2 dirToAllies = alliesInRangeAveragePosition - m_ownerEntity->GetPosition();
	dirToAllies.Normalize();

	//Final movement
	return (Vector2(0, 0) - dirToAllies) * m_seperationSpeed;
}


Entity* DefenderAIBrainComponent::GetClosestEnemy()
{
	//Get all enemies that currently exist.
	std::vector<Entity*> enemies = Application::Instance().GetEntitiesWithTag(m_enemyTag);
	if (enemies.size() <= 0) {
		return nullptr;
	}

	//There are enemies to move towards.
	Entity* closestEnemy = enemies[0];
	float closestDistanceSqr = (enemies[0]->GetPosition() - m_ownerEntity->GetPosition()).SqrMagnitude();
	for (int i = 1; i < enemies.size(); i++) {
		//Calculate distance to the owner.
		float distanceSqr = (enemies[i]->GetPosition() - m_ownerEntity->GetPosition()).SqrMagnitude();

		//If the closest distance is not initialised or the distance is less than the closest then assign
		// this enemy as the new closest.
		if (distanceSqr < closestDistanceSqr) {
			closestDistanceSqr = distanceSqr;
			closestEnemy = enemies[i];
		}
	}

	return closestEnemy;
}
