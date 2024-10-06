//Project includes.
#include "HealthComponent.h"
#include "Application.h"

HealthComponent::~HealthComponent()
{
}

void HealthComponent::Update(double a_deltaTime)
{
}

void HealthComponent::Damage(int a_damage)
{
	//Damage the entity.
	m_currentHealth -= a_damage;

	//Update size to reflect total health.
	UpdateSize();
}

void HealthComponent::Heal(int a_healthIncrease)
{
	//Heal the entity.
	m_currentHealth += a_healthIncrease;
	if (m_currentHealth > m_maxHealth) {
		m_currentHealth = m_maxHealth;
	}

	//Update size to reflect total health.
	UpdateSize();
}

void HealthComponent::DestroyIfDead()
{
	//Check if it's dead.
	if (m_currentHealth <= 0) {
		//Death so destroy the attached entity.
		Application::Instance().DestroyEntity(m_ownerEntity);
	}
}

void HealthComponent::UpdateSize()
{
	//Find percentage health and change size to be that percentage of original.
	float percentageHealth = (float)m_currentHealth / (float)m_maxHealth;
	if (percentageHealth < 0.1) {
		percentageHealth = 0.1;
	}
	else if (percentageHealth > 1) {
		percentageHealth = 1;
	}
	float newWidth = m_originalSize.x * percentageHealth;
	float newHeight = m_originalSize.y * percentageHealth;
	Vector2 newSize((int)newWidth, (int)newHeight);

	//Set the size.
	m_ownerEntity->SetSize(newSize);
}
