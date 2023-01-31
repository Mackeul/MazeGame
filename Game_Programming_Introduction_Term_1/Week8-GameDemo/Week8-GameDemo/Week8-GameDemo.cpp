
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
		cout << "You Win!" << endl;
	}
	else {
		cout << "Game did not load.  Terminating..." << endl;
	}

}




