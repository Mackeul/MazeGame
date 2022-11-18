
#include <iostream>
#include "Game.h"

using namespace std;

int main()
{

	Game myGame;

	if (myGame.Load()) {
		while (!myGame.IsGameOver()) {
			myGame.Run();
		}
		
		if (myGame.DidUserQuit()) {
			cout << "Thanks for playing!" << endl;
		}
		else if (myGame.GetPlayerLives() < 0) {
			cout << "You lose..." << endl;
			//PlayLoseSound();
		}
		else {
			cout << "You win!" << endl;
			//PlayWinSound()
		}
	}
	else {
		cout << "Game did not load.  Terminating..." << endl;
	}

}




