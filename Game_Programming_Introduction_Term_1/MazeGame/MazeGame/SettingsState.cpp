#include "SettingsState.h"
#include <iostream>
#include <conio.h>

#include "StateMachineExampleGame.h"
#include "AudioManager.h"

using namespace std;

constexpr int kEscapeKey = 27;

constexpr char kSound = '1';
constexpr char kMainMenu = '2';

SettingsState::SettingsState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner) {

}

void SettingsState::GetInput() {

	m_input = _getch();

	//if (m_input == kArrowInput) {
	//	m_input = _getch();
	//}

}

bool SettingsState::Update(bool processInput) {

	bool shouldQuit = false;

	if (processInput) {
		if (m_input == kEscapeKey || (char)m_input == kMainMenu) {
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);
		}
		else if ((char)m_input == kSound) {
			AudioManager::GetInstance()->ToggleSound();
			AudioManager::GetInstance()->PlayMoneyPickupSound();
		}

		m_input = 0;
	}

	return false;
}

void SettingsState::Draw() {

	system("cls");
	cout << endl << endl << endl;
	cout << "      ---- Settings ----" << endl << endl;
	cout << "       " << kSound << ". Toggle Sound " << endl;
	cout << "          " << "Sound is ";
	if (AudioManager::GetInstance()->IsSoundOn()) {
		cout << "ON" << endl;
	}
	else {
		cout << "OFF" << endl;
	}
	cout << "       " << kMainMenu << ". Return to Main Menu " << endl;

}
