#include "Game.h"

Game::Game()
: m_pStateMachine(nullptr) {

}

void Game::Initialize(GameStateMachine* pStateMachine) {

	if (pStateMachine) {
		pStateMachine->Init();
		m_pStateMachine = pStateMachine;
	}
}

void Game::RunGameLoop() {

	bool isGameOver = false;

	while (!isGameOver) {
		Update(false);
		Draw();
		isGameOver = Update();
	}
	Draw();
}

void Game::Deinitialize() {

	if (m_pStateMachine) {
		m_pStateMachine->CleanUp();
	}
}

bool Game::Update(bool processInput) {

	return m_pStateMachine->UpdateCurrentState(processInput);
}

void Game::Draw() {
	
	m_pStateMachine->DrawCurrentState();
}