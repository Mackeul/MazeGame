#include <iostream>
#include <conio.h>
#include <fstream>
#include <assert.h>

#include "GameplayState.h"
#include "StateMachineExampleGame.h"

#include "Enemy.h"
#include "Key.h"
#include "Door.h"
#include "Goal.h"
#include "Money.h"
#include "AudioManager.h"
#include "Utility.h"

using namespace std;

constexpr int kArrowInput = 224;
constexpr int kLeftArrow = 75;
constexpr int kRightArrow = 77;
constexpr int kUpArrow = 72;
constexpr int kDownArrow = 80;
constexpr int kEscapeKey = 27;

GameplayState::GameplayState(StateMachineExampleGame* pOwner)
	:	m_pOwner(pOwner),
		m_skipFrameCount(0),
		m_beatLevel(false),
		m_currentLevel(0),
		m_pLevel(nullptr),
		m_input(0) {

	m_levelNames.push_back("Level1.txt");
	m_levelNames.push_back("Level2.txt");
	m_levelNames.push_back("Level3.txt");

}

GameplayState::~GameplayState() {
	delete m_pLevel;
	m_pLevel = nullptr;
}

bool GameplayState::Load() {

	if (m_pLevel) {
		delete m_pLevel;
		m_pLevel = nullptr;
	}

	m_pLevel = new Level();

	return m_pLevel->Load(m_levelNames.at(m_currentLevel), m_player.GetXPositionPointer(), m_player.GetYPositionPointer());
}

void GameplayState::Enter() {
	Load();
}

void GameplayState::GetInput() {

	m_input = _getch();

	if (m_input == kArrowInput) {
		m_input = _getch();
	}

}

bool GameplayState::Update(bool processInput) {

	int newPlayerX = m_player.GetXPosition();
	int newPlayerY = m_player.GetYPosition();

	if (processInput && !m_beatLevel) {

		if ((m_input == kLeftArrow) ||
			(char)m_input == 'A' || (char)m_input == 'a') {
			newPlayerX--;
		}
		else if ((m_input == kRightArrow) ||
			(char)m_input == 'D' || (char)m_input == 'd') {
			newPlayerX++;
		}
		else if ((m_input == kUpArrow) ||
			(char)m_input == 'W' || (char)m_input == 'w') {
			newPlayerY--;
		}
		else if ((m_input == kDownArrow) ||
			(char)m_input == 'S' || (char)m_input == 's') {
			newPlayerY++;
		}
		else if (m_input == kEscapeKey) {
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);
		}
		else if ((char)m_input == 'Z' || (char)m_input == 'z') {
			m_player.DropKey();
		}

		// Maybe handle this in HandleCollision method?
		if (newPlayerX == m_pLevel->GetWidth()) {
			newPlayerX = m_pLevel->GetWidth() - 1;
		}
		else if (newPlayerX < 0) {
			newPlayerX = 0;
		}

		if (newPlayerY == m_pLevel->GetHeight()) {
			newPlayerY = m_pLevel->GetHeight() - 1;
		}
		else if (newPlayerY < 0) {
			newPlayerY = 0;
		}

		// reset m_input while waiting for player to make a move.
		m_input = 0;
	}
	
	HandleCollision(newPlayerX, newPlayerY);

	if (m_beatLevel) {
		++m_skipFrameCount;
		if (m_skipFrameCount > kFramesToSkip) {
			m_beatLevel = false;
			m_skipFrameCount = 0;
			++m_currentLevel;
			if (m_currentLevel == m_levelNames.size()) {
				Utility::WriteHighScore(m_player.GetMoney());
				AudioManager::GetInstance()->PlayWinSound();
				m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Win);
			}
			else
			{
				Load();
			}
		}
	}

	return false;
}

void GameplayState::HandleCollision(int newPlayerX, int newPlayerY) {

	bool isGameDone = false;
	
	PlacableActor* collidedActor = m_pLevel->UpdateActors(newPlayerX, newPlayerY);

	if (collidedActor != nullptr && collidedActor->IsActive()) {
		switch (collidedActor->GetType()) {
		case ActorType::Enemy: {
			Enemy* collidedEnemy = dynamic_cast<Enemy*>(collidedActor);
			assert(collidedEnemy);
			collidedEnemy->Remove();
			m_player.SetPosition(newPlayerX, newPlayerY);
			AudioManager::GetInstance()->PlayLoseLivesSound();

			m_player.DecrementLives();
			if (m_player.GetLives() < 0) {
				AudioManager::GetInstance()->PlayLoseSound();
				m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Lose);
			}
			break;
		}
		case ActorType::Money: {
			Money* collidedMoney = dynamic_cast<Money*>(collidedActor);
			assert(collidedMoney);
			collidedMoney->Remove();
			m_player.AddMoney(collidedMoney->GetWorth());
			m_player.SetPosition(newPlayerX, newPlayerY);
			AudioManager::GetInstance()->PlayMoneyPickupSound();
			break;
		}
		case ActorType::Key: {
			Key* collidedKey = dynamic_cast<Key*>(collidedActor);
			assert(collidedKey);
			if (!m_player.HasKey()) {
				collidedKey->Remove();
				m_player.PickupKey(collidedKey);
				m_player.SetPosition(newPlayerX, newPlayerY);
				AudioManager::GetInstance()->PlayKeyPickupSound();
			}
			break;
		}
		case ActorType::Door: {
			Door* collidedDoor = dynamic_cast<Door*>(collidedActor);
			assert(collidedDoor);
			if (!collidedDoor->IsOpen()) {
				if (m_player.HasKey(collidedDoor->GetColor())) {
					collidedDoor->Open();
					m_player.UseKey();
					m_player.SetPosition(newPlayerX, newPlayerY);
					AudioManager::GetInstance()->PlayDoorOpenSound();
				}
				else {
					AudioManager::GetInstance()->PlayDoorClosedSound();
				}
			}
			else {
				m_player.SetPosition(newPlayerX, newPlayerY);
			}
			break;
		}
		case ActorType::Goal: {
			Goal* collidedGoal = dynamic_cast<Goal*>(collidedActor);
			assert(collidedGoal);
			collidedGoal->Remove();
			m_player.SetPosition(newPlayerX, newPlayerY);
			m_beatLevel = true;
			break;
		}
		default: {
			break;
		}
		}
	}
	else if (m_pLevel->IsSpace(newPlayerX, newPlayerY)) {
		// no collision
		m_player.SetPosition(newPlayerX, newPlayerY);
	}
	else if (m_pLevel->IsWall(newPlayerX, newPlayerY)) {
		// wall collision do nothing
	}

}

void GameplayState::Draw() {

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");

	m_pLevel->Draw();

	//Set cursor position for player
	COORD actorCursorPosition;
	actorCursorPosition.X = m_player.GetXPosition();
	actorCursorPosition.Y = m_player.GetYPosition();
	SetConsoleCursorPosition(console, actorCursorPosition);
	m_player.Draw();

	//Set the cursor to the end of the level
	COORD currentCursorPosition;
	currentCursorPosition.X = 0;
	currentCursorPosition.Y = m_pLevel->GetHeight();
	SetConsoleCursorPosition(console, currentCursorPosition);

	DrawHUD(console);

}

void GameplayState::DrawHUD(const HANDLE& console) {

	cout << endl << endl;

	// Left Border
	cout << Level::WAL;

	cout << " wasd - move " << Level::WAL << " z - drop key " << Level::WAL;

	cout << " $:" << m_player.GetMoney() << " " << Level::WAL;

	cout << " Lives:" << m_player.GetLives() << " " << Level::WAL;

	cout << " Key:";
	if (m_player.HasKey()) {
		m_player.GetKey()->Draw();
	}
	else {
		cout << " ";
	}

	// Right border
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(console, &csbi);

	COORD pos;
	pos.X = csbi.dwCursorPosition.X;
	pos.Y = csbi.dwCursorPosition.Y;
	SetConsoleCursorPosition(console, pos);

	cout << Level::WAL;
	cout << endl;

	int HUDwidth = pos.X+1;  // HUD may not be same width as level.

	//Bottom Border
	for (int i = 0; i < HUDwidth; i++) {
		cout << Level::WAL;
	}
	cout << endl;

	// Reset position to draw top border now that we know the width.
	pos.Y -= 1;
	pos.X = 0;
	SetConsoleCursorPosition(console, pos);
	
	//Top Border
	for (int i = 0; i < HUDwidth; i++) {
		cout << Level::WAL;
	}

}
