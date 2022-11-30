#pragma once
#include <chrono>

#include "GameStateMachine.h"


class Game {

	GameStateMachine* m_pStateMachine;

	std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

public:
	Game();
	void Initialize(GameStateMachine* pStateMachine);

	void RunGameLoop();
	void Deinitialize();

private:
	bool Update(bool processInput = true);
	void Draw();

};