#pragma once

//Project includes.
#include "Scene.h"
#include "HealthComponent.h"

//Library includes.
#include <string>

//Class defintion.
class ArmySimulationScene : public Scene {
public:
	//Constructor and destructor.
	ArmySimulationScene(std::string a_sceneName) : Scene(a_sceneName) {

	}
	~ArmySimulationScene();

	// Inherited via Scene
	void SetupScene() override;
	void UpdateScene(double a_deltaTime) override;
	void ShutdownScene() override;

	//Enums.
	enum WinConditions {
		none,
		RedWin,
		BlueWin,
		Draw
	};

private:
	//Win conditions.
	WinConditions CheckWinConditions();
	WinConditions m_gameWonCondition = none;
	bool gameOver = false;
	float m_gameOverTimer = 0;

	HealthComponent* m_redBaseHealth;
	HealthComponent* m_blueBaseHealth;

	Entity* GetRedBase() { return m_redBaseHealth->GetOwnerEntity(); }
	Entity* GetBlueBase() { return m_blueBaseHealth->GetOwnerEntity(); }

};