#include "MainMenuState.h"

#include <iostream>
#include <conio.h>

#include "StateMachineExampleGame.h"

using namespace std;

constexpr int kEscapeKey = 27;

constexpr char kPlay = '1';
constexpr char kHighScores = '2';
constexpr char kSettings = '3';
constexpr char kQuit = '4';

MainMenuState::MainMenuState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner) {

}

void MainMenuState::GetInput() {

	m_input = _getch();

}

bool MainMenuState::Update(bool processInput) {

	bool shouldQuit = false;

	if (processInput) {
		if (m_input == kEscapeKey || (char)m_input == kQuit) {
			shouldQuit = true;
		}
		else if ((char)m_input == kPlay) {
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::GamePlay);
		}
		else if ((char)m_input == kSettings) {
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Settings);
		}
		else if ((char)m_input == kHighScores) {
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::HighScores);
		}
		m_input = 0;
	}

	return shouldQuit;
}

void MainMenuState::Draw() {

	system("cls");
	cout << endl << endl << endl;
	cout << "      ---- Main Menu ----" << endl << endl;
	cout << "       " << kPlay << ". Play " << endl;
	cout << "       " << kHighScores << ". High Scores " << endl;
	cout << "       " << kSettings << ". Settings " << endl;
	cout << "       " << kQuit << ". Quit " << endl;
}