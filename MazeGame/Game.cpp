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

	while (!m_isGameOver) {

		std::chrono::steady_clock::time_point current_time = std::chrono::steady_clock::now();
		std::chrono::duration<float> elapsed_seconds = current_time - start_time;

		if (elapsed_seconds.count() >= 0.8f) {		
			Update(false);
			Draw();
			start_time = current_time;
		}
		m_isGameOver = Update(true);
	}

	Draw();
}

void Game::Deinitialize() {

	if (m_pStateMachine) {
		m_pStateMachine->CleanUp();
	}
}

void Game::GetInput(bool processInput) {
	m_pStateMachine->GetInputFromState(processInput);
}

void Game::GetInputLoop() {

	while (!m_isGameOver) {	
		m_pStateMachine->GetInputFromState(true);
	}
}

bool Game::Update(bool processInput) {

	return m_pStateMachine->UpdateCurrentState(processInput);
}

void Game::Draw() {
	m_pStateMachine->DrawCurrentState();
}