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
		//std::chrono::steady_clock::time_point current_time = std::chrono::steady_clock::now();
		//std::chrono::duration<float> elapsed_seconds = current_time - start_time;
		//if (elapsed_seconds.count() >= 1.0f) {
			Update(false);
			Draw();
			isGameOver = Update();
			//start_time = current_time;
		//}
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