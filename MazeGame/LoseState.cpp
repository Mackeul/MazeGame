#include "LoseState.h"

#include <iostream>
#include <conio.h>

#include "StateMachineExampleGame.h"

using namespace std;

constexpr int kEscapeKey = 27;

constexpr char kPlay = '1';
constexpr char kHighScores = '2';
constexpr char kSettings = '3';
constexpr char kQuit = '4';

LoseState::LoseState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner) {

}

bool LoseState::Update(bool processInput) {

	if (processInput) {
		int input = _getch();
		m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);
	}

	return false;
}

void LoseState::Draw() {

	cout << "GAME OVER..." << endl;
	cout << "Better Luck next time!" << endl << endl;

	cout << "Press any key to return to Main Menu " << endl;
}