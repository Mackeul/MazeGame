#include "Game.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <fstream>

using namespace std;

constexpr int kOpenDoorColor = 10;
constexpr int kClosedDoorColor = 12;
constexpr int kRegularColor = 7;

constexpr char kTopRightBorder = 187;
constexpr char kTopLeftBorder = 201;
constexpr char kBottomRightBorder = 188;
constexpr char kBottomLeftBorder = 200;
constexpr char kHorizontalBorder = 205;
constexpr char kVerticalBorder = 186;

Game::Game() 
: m_isGameOver(false) {

}

Game::~Game() {

}

bool Game::Load() {

	return m_level.Load("Level1.txt", m_player.GetXPositionPointer(), m_player.GetYPositionPointer());
}
void Game::Run() {

	Draw();
	m_isGameOver = Update();

	if (m_isGameOver) {
		Draw();
		PlayWinSound();
	}
}

bool Game::IsGameOver() {

	return m_isGameOver;
}

bool Game::Update() {

	char input = (char)_getch();

	int newPlayerX = m_player.GetXPosition();
	int newPlayerY = m_player.GetYPosition();

	switch (input)
	{
	case 'w':
	case 'W': {
		newPlayerY--;
		break;
	}
	case 's':
	case 'S': {
		newPlayerY++;
		break;
	}
	case 'a':
	case 'A': {
		newPlayerX--;
		break;
	}
	case 'd':
	case 'D': {
		newPlayerX++;
		break;
	}
	default: {
		break;
	}
	}

	if (newPlayerX == m_level.GetWidth()) {
		newPlayerX = m_level.GetWidth() - 1;
	}
	else if (newPlayerX < 0) {
		newPlayerX = 0;
	}

	if (newPlayerY == m_level.GetHeight()) {
		newPlayerY = m_level.GetHeight() - 1;
	}
	else if (newPlayerY < 0) {
		newPlayerY = 0;
	}

	if (m_level.IsSpace(newPlayerX, newPlayerY)) {
		m_player.SetPosition(newPlayerX,newPlayerY);
	}
	else if (m_level.IsKey(newPlayerX, newPlayerY)) {
		m_level.PickupKey(newPlayerX, newPlayerY);
		m_player.PickupKey();
		m_player.SetPosition(newPlayerX, newPlayerY);
		PlayKeyPickupSound();
	}
	else if (m_level.IsDoor(newPlayerX, newPlayerY) && m_player.HasKey()) {
		m_level.OpenDoor(newPlayerX,newPlayerY);
		m_player.UseKey();
		m_player.SetPosition(newPlayerX, newPlayerY);
		PlayDoorOpenSound();
	}
	else if (m_level.IsDoor(newPlayerX, newPlayerY) && !m_player.HasKey()) {
		PlayDoorClosedSound();
	}
	else if (m_level.IsGoal(newPlayerX, newPlayerY)) {
		m_player.SetPosition(newPlayerX, newPlayerY);
		return true;
	}

	return false;

}
void Game::Draw() {

	system("cls");
	DisplayTopBorder(m_level.GetWidth());
	for (int y = 0; y < m_level.GetHeight(); y++) {
		DisplayLeftBorder();
		for (int x = 0; x < m_level.GetWidth(); x++) {
			if (m_player.GetXPosition() == x && m_player.GetYPosition() == y) {
				m_player.Draw();
			}
			else {
				HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
				if (m_level.IsDoor(x,y)) {
					if (m_player.HasKey()) {
						SetConsoleTextAttribute(console, kOpenDoorColor);
					}
					else {
						SetConsoleTextAttribute(console, kClosedDoorColor);
					}
				}
				else {
					SetConsoleTextAttribute(console, kRegularColor);
				}
				m_level.Draw(x, y);
			}
		}
		DisplayRightBorder();
	}
	DisplayBottomBorder(m_level.GetWidth());
}

void Game::DisplayTopBorder(int width) {

	cout << kTopLeftBorder;
	for (int i = 0; i < width; i++) {
		cout << kHorizontalBorder;
	}
	cout << kTopRightBorder << endl;
}

void Game::DisplayBottomBorder(int width) {

	cout << kBottomLeftBorder;

	for (int i = 0; i < width; i++) {
		cout << kHorizontalBorder;
	}
	cout << kBottomRightBorder << endl;
}

void Game::DisplayLeftBorder() {
	cout << kVerticalBorder;
}

void Game::DisplayRightBorder() {
	cout << kVerticalBorder << endl;
}

void Game::PlayKeyPickupSound() {
	Beep(1175, 75);
	Beep(1245, 75);
	Beep(1397, 75);
	Beep(1568, 75);
	Beep(1600, 75);
}


void Game::PlayDoorClosedSound() {
	Beep(500, 75);
	Beep(500, 75);

}

void Game::PlayDoorOpenSound() {
	Beep(1397, 200);

}

void Game::PlayWinSound() {
	Beep(1568, 200);
	Beep(1568, 200);
	Beep(1568, 200);
	Beep(1245, 1000);
	Beep(1397, 200);
	Beep(1397, 200);
	Beep(1397, 200);
	Beep(1175, 1000);
}