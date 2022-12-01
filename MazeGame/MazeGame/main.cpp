
#include <iostream>
#include <thread>
#include "vld.h"

#include "Game.h"
#include "AudioManager.h"
#include "StateMachineExampleGame.h"

using namespace std;

int main()
{
	Game myGame;

	StateMachineExampleGame gameStateMachine(&myGame);

	myGame.Initialize(&gameStateMachine);
	std::thread gameLoopThread(&Game::RunGameLoop, &myGame);
	myGame.GetInputLoop();
	gameLoopThread.join();
	myGame.Deinitialize();

	AudioManager::DestroyInstance();

	return 0;
}




