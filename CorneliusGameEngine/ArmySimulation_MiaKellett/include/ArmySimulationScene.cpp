//Project includes.
#include "ArmySimulationScene.h"
#include "Application.h"
#include "AttackerAIBrainComponent.h"
#include "DefenderAIBrainComponent.h"

//Function definitions.
ArmySimulationScene::~ArmySimulationScene()
{

}

void ArmySimulationScene::SetupScene()
{
	//Ensure any setup for the actual game is done here.
	const int BASE_HEALTH = 3600;

	const int DEFENDER_HEALTH = 1800;
	const int DEFENDER_COUNT = 25;
	const int DEFENDER_MOVE_SPEED = 50.0f;
	const int DEFENDER_DMG = 250;
	const float DEFENDER_ATTACK_COOLDOWN = 1.0f;

	const int ATTACKER_HEALTH = 1200;
	const int ATTACKER_COUNT = 74;
	const int ATTACKER_DMG = 400;
	const float ATTACKER_ATTACK_COOLDOWN = 0.5f;
	const float ATTACKER_MOVE_SPEED = 100.0f;

	const float SEPERATION_SPEED = 1000.0f;
	//Create the Red team units.
	//Create the base.
	Entity* redBase = new Entity(nullptr, Vector2(Application::SCREEN_WIDTH / 20, Application::SCREEN_HEIGHT / 2)
		, Vector2(Application::SCREEN_HEIGHT / 10, Application::SCREEN_HEIGHT / 10)
		, "Red Base", "RedTeam", "resources/RedBase.png");
	HealthComponent* redBaseHealth = new HealthComponent(redBase, BASE_HEALTH);
	redBase->AddComponent(redBaseHealth);
	m_redBaseHealth = redBaseHealth;
	m_gameEntities.push_back(redBase);

	//Create the red defender units.
	for (int i = 0; i < DEFENDER_COUNT; i++) {
		Entity* redDefenderUnit = new Entity(nullptr, Vector2(Application::SCREEN_WIDTH / 10, (Application::SCREEN_HEIGHT / DEFENDER_COUNT) * i)
			, Vector2(Application::SCREEN_HEIGHT / 30, Application::SCREEN_HEIGHT / 30)
			, "RedDefender(" + std::to_string(i) + ")", "RedTeam", "resources/RedDefender.png");

		HealthComponent* redDefenderHealth = new HealthComponent(redDefenderUnit, DEFENDER_HEALTH);
		redDefenderUnit->AddComponent(redDefenderHealth);
		DefenderAIBrainComponent* redDefenderBrain = new DefenderAIBrainComponent(redDefenderUnit, "RedTeam", "BlueTeam", redDefenderHealth, DEFENDER_MOVE_SPEED, SEPERATION_SPEED, DEFENDER_DMG, DEFENDER_ATTACK_COOLDOWN, GetRedBase()->GetPosition());
		redDefenderUnit->AddComponent(redDefenderBrain);
		m_gameEntities.push_back(redDefenderUnit);
	}

	//Create the red attacker units.
	for (int i = 0; i < ATTACKER_COUNT; i++) {
		bool isEven = i % 2 == 0;
		int posModifier = Application::SCREEN_HEIGHT / 32;
		if (isEven) {
			posModifier = 0;
		}
		Entity* redAttackerUnit = new Entity(nullptr, Vector2(Application::SCREEN_WIDTH / 6 + posModifier, (Application::SCREEN_HEIGHT / (ATTACKER_COUNT / 2)) * i)
			, Vector2(Application::SCREEN_HEIGHT / 32, Application::SCREEN_HEIGHT / 32)
			, "RedAttacker(" + std::to_string(i) + ")", "RedTeam", "resources/RedAttacker.png");
		HealthComponent* redAttackerHealth = new HealthComponent(redAttackerUnit, ATTACKER_HEALTH);
		redAttackerUnit->AddComponent(redAttackerHealth);
		AttackerAIBrainComponent* redAttackBrain = new AttackerAIBrainComponent(redAttackerUnit, "RedTeam", "BlueTeam", redBaseHealth, ATTACKER_MOVE_SPEED, SEPERATION_SPEED, ATTACKER_DMG, ATTACKER_ATTACK_COOLDOWN);
		redAttackerUnit->AddComponent(redAttackBrain);
		m_gameEntities.push_back(redAttackerUnit);
	}

	//Create the Blue team units.
	//Create the base.
	Entity* blueBase = new Entity(nullptr, Vector2(Application::SCREEN_WIDTH - Application::SCREEN_WIDTH / 20, Application::SCREEN_HEIGHT / 2)
		, Vector2(Application::SCREEN_HEIGHT / 10, Application::SCREEN_HEIGHT / 10)
		, "Blue Base", "BlueTeam", "resources/BlueBase.png");
	HealthComponent* blueBaseHealth = new HealthComponent(blueBase, BASE_HEALTH);
	blueBase->AddComponent(blueBaseHealth);
	m_blueBaseHealth = blueBaseHealth;
	m_gameEntities.push_back(blueBase);

	//Create the blue defender units.
	for (int i = 0; i < DEFENDER_COUNT; i++) {
		Entity* blueDefenderUnit = new Entity(nullptr, Vector2(Application::SCREEN_WIDTH - Application::SCREEN_WIDTH / 10, (Application::SCREEN_HEIGHT / 25) * i)
			, Vector2(Application::SCREEN_HEIGHT / 30, Application::SCREEN_HEIGHT / 30)
			, "BlueDefender(" + std::to_string(i) + ")", "BlueTeam", "resources/BlueDefender.png");

		HealthComponent* blueDefenderHealth = new HealthComponent(blueDefenderUnit, DEFENDER_HEALTH);
		blueDefenderUnit->AddComponent(blueDefenderHealth);
		DefenderAIBrainComponent* blueDefenderBrain = new DefenderAIBrainComponent(blueDefenderUnit, "BlueTeam", "RedTeam", blueDefenderHealth, DEFENDER_MOVE_SPEED, SEPERATION_SPEED, DEFENDER_DMG, DEFENDER_ATTACK_COOLDOWN, GetBlueBase()->GetPosition());
		blueDefenderUnit->AddComponent(blueDefenderBrain);
		m_gameEntities.push_back(blueDefenderUnit);
	}

	//Create the blue attacker units.
	for (int i = 0; i < ATTACKER_COUNT; i++) {
		bool isEven = i % 2 == 0;
		int posModifier = Application::SCREEN_HEIGHT / 32;
		if (isEven) {
			posModifier = 0;
		}
		Entity* blueAttackerUnit = new Entity(nullptr, Vector2(Application::SCREEN_WIDTH - (Application::SCREEN_WIDTH / 6 - posModifier), (Application::SCREEN_HEIGHT / (ATTACKER_COUNT / 2)) * i)
			, Vector2(Application::SCREEN_HEIGHT / 32, Application::SCREEN_HEIGHT / 32)
			, "BlueAttacker(" + std::to_string(i) + ")", "BlueTeam", "resources/BlueAttacker.png");
		HealthComponent* blueAttackerHealth = new HealthComponent(blueAttackerUnit, ATTACKER_HEALTH);
		blueAttackerUnit->AddComponent(blueAttackerHealth);
		AttackerAIBrainComponent* blueAttackBrain = new AttackerAIBrainComponent(blueAttackerUnit, "BlueTeam", "RedTeam", blueBaseHealth, ATTACKER_MOVE_SPEED, SEPERATION_SPEED, ATTACKER_DMG, ATTACKER_ATTACK_COOLDOWN);
		blueAttackerUnit->AddComponent(blueAttackBrain);
		m_gameEntities.push_back(blueAttackerUnit);
	}

	//Now all units have been created, shuffle them.
	ShuffleEntities();

	//Ensure base healths have been assigned.
	m_blueBaseHealth = blueBaseHealth;
	m_redBaseHealth = redBaseHealth;
}

void ArmySimulationScene::UpdateScene(double a_deltaTime)
{
	//Call the base class implementation that updates all the game entities.
	Scene::UpdateScene(a_deltaTime);

	if (!gameOver) {
		//Check win conditions after updating the entities.
		m_gameWonCondition = CheckWinConditions();
		if (m_gameWonCondition != none) {
			//Game is over so destroy all entites.
			DestroyAllEntities();

			//Load the game over screen.
			if (m_gameWonCondition == BlueWin) {
				Entity* gameOverScreen = new Entity(nullptr, Vector2(Application::SCREEN_WIDTH / 2, Application::SCREEN_HEIGHT / 2), Vector2(Application::SCREEN_WIDTH, Application::SCREEN_HEIGHT), "BlueWinGameOver", "GameOver", "resources/BlueWins_GameOver.png");
				m_gameEntities.push_back(gameOverScreen);
			}
			else if (m_gameWonCondition == RedWin) {
				Entity* gameOverScreen = new Entity(nullptr, Vector2(Application::SCREEN_WIDTH / 2, Application::SCREEN_HEIGHT / 2), Vector2(Application::SCREEN_WIDTH, Application::SCREEN_HEIGHT), "RedWinGameOver", "GameOver", "resources/RedWins_GameOver.png");
				m_gameEntities.push_back(gameOverScreen);
			}
			else if (m_gameWonCondition == Draw) {
				Entity* gameOverScreen = new Entity(nullptr, Vector2(Application::SCREEN_WIDTH / 2, Application::SCREEN_HEIGHT / 2), Vector2(Application::SCREEN_WIDTH, Application::SCREEN_HEIGHT), "DrawGameOver", "GameOver", "resources/GameOverDraw.png");
				m_gameEntities.push_back(gameOverScreen);
			}

			gameOver = true;
		}
		else {
			//Cleanup any dead entities.
			for (int i = 0; i < m_gameEntities.size(); i++) {
				HealthComponent* healthCheck = (HealthComponent*)m_gameEntities[i]->GetComponentByID("HealthComponent");
				healthCheck->DestroyIfDead();
			}
		}
	}
}

void ArmySimulationScene::ShutdownScene()
{
	//Call base implementation to shutdown the scene.
	Scene::ShutdownScene();

	//The game Base entities will get cleaned up by the "DestroyAllEntites" function in the base class definition.
}

ArmySimulationScene::WinConditions ArmySimulationScene::CheckWinConditions()
{
	if (m_blueBaseHealth == nullptr) {
		return none;
	}

	if (m_redBaseHealth == nullptr) {
		return none;
	}

	if (m_blueBaseHealth->GetHealthPoints() > 0 && m_redBaseHealth->GetHealthPoints() <= 0) {
		return BlueWin;
	}
	else if (m_blueBaseHealth->GetHealthPoints() <= 0 && m_redBaseHealth->GetHealthPoints() > 0) {
		return RedWin;
	}
	else if (m_blueBaseHealth->GetHealthPoints() <= 0 && m_redBaseHealth->GetHealthPoints() <= 0) {
		return Draw;
	}
	else {
		return none;
	}
}