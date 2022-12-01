
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
	std::thread inputThread(&Game::RunGameLoop, &myGame);
	myGame.GetInputLoop();
	inputThread.join();
	myGame.Deinitialize();

	AudioManager::DestroyInstance();

	return 0;
}




