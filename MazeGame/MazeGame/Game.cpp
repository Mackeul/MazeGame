#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <assert.h>

#include "Game.h"
#include "Enemy.h"
#include "Key.h"
#include "Door.h"
#include "Goal.h"
#include "Money.h"
#include "AudioManager.h"

using namespace std;

constexpr int kArrowInput = 224;
constexpr int kLeftArrow = 75;
constexpr int kRightArrow = 77;
constexpr int kUpArrow = 72;
constexpr int kDownArrow = 80;
constexpr int kEscapeKey = 27;

Game::Game()
: m_isGameOver(false),
  m_UserQuit(false) {

}

Game::~Game() {

}

bool Game::Load() {

	return m_level.Load("Level1.txt", m_player.GetXPositionPointer(), m_player.GetYPositionPointer());
}
void Game::Run() {

	Draw();
	m_isGameOver = Update();

	if (m_isGameOver) {
		Draw();
	}
}

bool Game::IsGameOver() {

	return m_isGameOver;
}

bool Game::Update() {

	int input = _getch();
	int arrowInput = 0;

	int newPlayerX = m_player.GetXPosition();
	int newPlayerY = m_player.GetYPosition();

	// One of the arrow keys was pressed
	if (input == kArrowInput) {
		arrowInput = _getch();
	}
	
	if ((input == kArrowInput && arrowInput == kLeftArrow) ||
		(char)input == 'A' || (char)input == 'a') {
		newPlayerX--;
	}
	else if ((input == kArrowInput && arrowInput == kRightArrow) ||
		(char)input == 'D' || (char)input == 'd') {
		newPlayerX++;
	}
	else if ((input == kArrowInput && arrowInput == kUpArrow) ||
		(char)input == 'W' || (char)input == 'w') {
		newPlayerY--;
	}
	else if ((input == kArrowInput && arrowInput == kDownArrow) ||
		(char)input == 'S' || (char)input == 's') {
		newPlayerY++;
	}
	else if (input == kEscapeKey) {
		m_UserQuit = true;
		return true;
	}
	else if ((char)input == 'Z' || (char)input == 'z') {
		m_player.DropKey();
	}

	// Maybe handle this in HandleCollision method?
	if (newPlayerX == m_level.GetWidth()) {
		newPlayerX = m_level.GetWidth() - 1;
	}
	else if (newPlayerX < 0) {
		newPlayerX = 0;
	}

	if (newPlayerY == m_level.GetHeight()) {
		newPlayerY = m_level.GetHeight() - 1;
	}
	else if (newPlayerY < 0) {
		newPlayerY = 0;
	}

	// if position never changed
	if (newPlayerX == m_player.GetXPosition() && newPlayerY == m_player.GetYPosition()) {
		return false;
	}
	else {
		return HandleCollision(newPlayerX, newPlayerY);
	}

	return false;

}

bool Game::HandleCollision(int newPlayerX, int newPlayerY) {

	bool isGameDone = false;

	PlacableActor* collidedActor = m_level.UpdateActors(newPlayerX, newPlayerY);
	
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
					isGameDone = true;
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
				AudioManager::GetInstance()->PlayWinSound();
				isGameDone = true;
				break;
			}
			default: {
				break;
			}
		}
	}
	else if (m_level.IsSpace(newPlayerX, newPlayerY)) {
		// no collision
		m_player.SetPosition(newPlayerX, newPlayerY);
	}
	else if (m_level.IsWall(newPlayerX, newPlayerY)) {
		// wall collision do nothing
	}

	return isGameDone;
}

void Game::Draw() {

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");

	m_level.Draw();

	//Set cursor position for player
	COORD actorCursorPosition;
	actorCursorPosition.X = m_player.GetXPosition();
	actorCursorPosition.Y = m_player.GetYPosition();
	SetConsoleCursorPosition(console, actorCursorPosition);
	m_player.Draw();

	//Set the cursor to the end of the level
	COORD currentCursorPosition;
	currentCursorPosition.X = 0;
	currentCursorPosition.Y = m_level.GetHeight();
	SetConsoleCursorPosition(console, currentCursorPosition);

}