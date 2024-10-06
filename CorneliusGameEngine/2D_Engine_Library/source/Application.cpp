//Project includes.
#include "Application.h"
#include "Entity.h"
#include "HealthComponent.h"
#include "AttackerAIBrainComponent.h"
#include "DefenderAIBrainComponent.h"

//Library includes.
#include <iostream>
#include <SDL.h>
#include <random>
#include <algorithm>

//Functions.

Application::Application()
{
}

Application::~Application()
{

}

int Application::Initialise()
{
	int rendererInitOuput = m_renderer.Initialise(SCREEN_WIDTH, SCREEN_HEIGHT, IS_FULLSCREEN);
	if (rendererInitOuput != 0) {
		return rendererInitOuput;
	}

	return 0;
}

void Application::Start()
{
	//Ensure any setup for the actual game is done here.
	//This function is not to initialise engine.
	//This function is only for setuping game data.

	//Entity* redCircle1 = new Entity(nullptr, Vector2(200, 200), Vector2(100, 100), "Red Circle 1", "RedCircle", "resources/RedCircle.png", m_renderer);
	//Entity* blueCircle1 = new Entity(nullptr, Vector2(200, 400), Vector2(100, 100), "Blue Circle 1", "BlueCircle", "resources/BlueCircle.png", m_renderer);
	//m_gameEntities.push_back(redCircle1);
	//m_gameEntities.push_back(blueCircle1);

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
		, "Red Base", "RedTeam", "resources/RedBase.png", m_renderer);
	HealthComponent* redBaseHealth = new HealthComponent(redBase, BASE_HEALTH);
	redBase->AddComponent(redBaseHealth);
	m_redBaseHealth = redBaseHealth;
	m_gameEntities.push_back(redBase);

	//Create the red defender units.
	for (int i = 0; i < DEFENDER_COUNT; i++) {
		Entity* redDefenderUnit = new Entity(nullptr, Vector2(Application::SCREEN_WIDTH / 10, (Application::SCREEN_HEIGHT / DEFENDER_COUNT) * i)
			, Vector2(Application::SCREEN_HEIGHT / 30, Application::SCREEN_HEIGHT / 30)
			, "RedDefender(" + std::to_string(i) + ")", "RedTeam", "resources/RedDefender.png", m_renderer);

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
			, "RedAttacker(" + std::to_string(i) + ")", "RedTeam", "resources/RedAttacker.png", m_renderer);
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
		, "Blue Base", "BlueTeam", "resources/BlueBase.png", m_renderer);
	HealthComponent* blueBaseHealth = new HealthComponent(blueBase, BASE_HEALTH);
	blueBase->AddComponent(blueBaseHealth);
	m_blueBaseHealth = blueBaseHealth;
	m_gameEntities.push_back(blueBase);

	//Create the blue defender units.
	for (int i = 0; i < DEFENDER_COUNT; i++) {
		Entity* blueDefenderUnit = new Entity(nullptr, Vector2(Application::SCREEN_WIDTH - Application::SCREEN_WIDTH / 10, (Application::SCREEN_HEIGHT / 25) * i)
			, Vector2(Application::SCREEN_HEIGHT / 30, Application::SCREEN_HEIGHT / 30)
			, "BlueDefender(" + std::to_string(i) + ")", "BlueTeam", "resources/BlueDefender.png", m_renderer);

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
			, "BlueAttacker(" + std::to_string(i) + ")", "BlueTeam", "resources/BlueAttacker.png", m_renderer);
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

void Application::Run()
{
	//Start of the application.
	Start();


	//Application loop.
	Uint32 lastFrameTime = SDL_GetTicks();
	double targetDeltaTime = 1.0 / TARGET_FPS;

	while (true) {
		//Calculate time since last frame and convert to seconds.
		Uint32 currentFrameTime = SDL_GetTicks();
		Uint32 elapsedTime = currentFrameTime - lastFrameTime;
		double deltaTime = elapsedTime / 1000.0;

		//If the frametime hasn't reached the target.
		if (deltaTime <= targetDeltaTime) {
			//Don't update.
			continue;
		}

		//std::cout << "fps: " << ((int)(1 / deltaTime)) << std::endl;

		//Poll any events.
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				break;
			}
		}

		//Update the game.
		for (int i = 0; i < m_gameEntities.size(); i++) {
			Entity* currentEntity = m_gameEntities[i];
			currentEntity->Update(deltaTime);
		}

		//Render it.
		m_renderer.Render(m_gameEntities);
		if (!gameOver) {
			//Check win conditions after rendering.
			m_gameWonCondition = CheckWinConditions();
			if (m_gameWonCondition != none) {
				//Game is over so destroy all entites.
				DestroyAllEntities();

				//Load the game over screen.
				if (m_gameWonCondition == BlueWin) {
					Entity* gameOverScreen = new Entity(nullptr, Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), Vector2(SCREEN_WIDTH, SCREEN_HEIGHT), "BlueWinGameOver", "GameOver", "resources/BlueWins_GameOver.png", m_renderer);
					m_gameEntities.push_back(gameOverScreen);
				}
				else if (m_gameWonCondition == RedWin) {
					Entity* gameOverScreen = new Entity(nullptr, Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), Vector2(SCREEN_WIDTH, SCREEN_HEIGHT), "RedWinGameOver", "GameOver", "resources/RedWins_GameOver.png", m_renderer);
					m_gameEntities.push_back(gameOverScreen);
				}
				else if (m_gameWonCondition == Draw) {
					Entity* gameOverScreen = new Entity(nullptr, Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), Vector2(SCREEN_WIDTH, SCREEN_HEIGHT), "DrawGameOver", "GameOver", "resources/GameOverDraw.png", m_renderer);
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

		//Cache current frame time.
		lastFrameTime = currentFrameTime;

	}
}

void Application::Shutdown()
{
	//Destroy all entities.

	m_renderer.Shutdown();
	std::cout << "Shutting down SDL." << std::endl;
	SDL_Quit();

	std::cout << "Application has finished shutting down." << std::endl;
}

Entity* Application::GetEntityByName(const std::string& a_name)
{
	for (int i = 0; i < m_gameEntities.size(); i++) {
		if (m_gameEntities[i]->GetName() == a_name) {
			return m_gameEntities[i];
		}
	}

	//No entity matched.
	std::cout << "No entity of name " << a_name << " was found." << std::endl;
	return nullptr;
}

std::vector<Entity*> Application::GetEntitiesWithTag(const std::string& a_tag)
{
	std::vector<Entity*> entitiesWithTag;
	for (int i = 0; i < m_gameEntities.size(); i++) {
		if (m_gameEntities[i]->GetTag() == a_tag) {
			entitiesWithTag.push_back(m_gameEntities[i]);
		}
	}

	return entitiesWithTag;
}

void Application::DestroyEntity(Entity* a_entityToDestroy)
{
	//Ensure entity is valid.
	if (a_entityToDestroy == nullptr) {
		return; //Early out.
	}

	//Remove the entity from the list of current game entities.
	auto newEnd = std::remove(m_gameEntities.begin(), m_gameEntities.end(), a_entityToDestroy);
	m_gameEntities.erase(newEnd, m_gameEntities.end());

	//Destroy it.
	std::cout << "Destroying entity: " << a_entityToDestroy->GetName() << std::endl;
	delete a_entityToDestroy;
}

void Application::DestroyAllEntities()
{
	//Destroy all entities untill there is nothing left.
	while (m_gameEntities.size() > 0) {
		DestroyEntity(m_gameEntities[0]);
	}
}

bool Application::IsPositionOutOfBound(Vector2& a_pos)
{
	//std::cout << "x: " << a_pos.GetX() << " y: " << a_pos.GetY() << std::endl;
	return a_pos.x < 0
		|| a_pos.x > Application::SCREEN_WIDTH
		|| a_pos.y < 0
		|| a_pos.y > Application::SCREEN_HEIGHT;
}

void Application::ShuffleEntities()
{
	//Create a random device and seed it.
	std::random_device rng;
	std::mt19937 randFunc(rng());

	//Shuffle the entities vector.
	std::shuffle(m_gameEntities.begin(), m_gameEntities.end(), randFunc);
}

Application::WinConditions Application::CheckWinConditions()
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
