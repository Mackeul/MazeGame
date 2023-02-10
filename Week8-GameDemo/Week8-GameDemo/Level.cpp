#include "Level.h"

#include <iostream>
#include <fstream>
#include <Windows.h>

using namespace std;

constexpr char WAL = (char)219;
constexpr char KEY = (char)232;
constexpr char DOR = (char)179;
constexpr char GOL = (char)36;

Level::Level() 
	: m_pLevelData(nullptr),
	  m_height(0),
	  m_width(0) 
{

}

Level::~Level() {

	if (m_pLevelData != nullptr) {
		delete[] m_pLevelData;
		m_pLevelData = nullptr;
	}
}


bool Level::Load(std::string levelName, int* playerX, int* playerY) {
	
	levelName.insert(0, "../");

	ifstream levelFile;
	levelFile.open(levelName);
	if (!levelFile) {
		cout << "Error opening file." << endl;
		return false;
	}
	else {
		constexpr int tempSize = 25;
		char temp[tempSize];

		levelFile.getline(temp, tempSize, '\n');
		m_width = atoi(temp);

		levelFile.getline(temp, tempSize, '\n');
		m_height = atoi(temp);

		m_pLevelData = new char[m_width * m_height];
		levelFile.read(m_pLevelData, (long long)m_width * (long long)m_height);

		bool anyWarnings = Convert(playerX,playerY);
		if (anyWarnings) {
			cout << "There were some warnings in the level data, see above." << endl;
			system("pause");
		}

		return true;
	}

}

void Level::Draw(int x, int y) {

	int index = GetIndexFromCoordinates(x, y);
	cout << m_pLevelData[index];
}


bool Level::IsSpace(int x, int y) {

	return m_pLevelData[GetIndexFromCoordinates(x, y)] == ' ';

}

bool Level::IsDoor(int x, int y) {
	return m_pLevelData[GetIndexFromCoordinates(x, y)] == DOR;
}

bool Level::IsKey(int x, int y) {
	return m_pLevelData[GetIndexFromCoordinates(x, y)] == KEY;
}

bool Level::IsGoal(int x, int y) {
	return m_pLevelData[GetIndexFromCoordinates(x, y)] == GOL;
}


void Level::PickupKey(int x, int y) {
	m_pLevelData[GetIndexFromCoordinates(x, y)] = ' ';
}

void Level::OpenDoor(int x, int y) {
	m_pLevelData[GetIndexFromCoordinates(x, y)] = ' ';
}

bool Level::Convert(int* playerX, int* playerY) {

	bool anyWarnings = false;

	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			int index = GetIndexFromCoordinates(x, y);

			switch (m_pLevelData[index]) {
			case '+':
			case '-':
			case '|': {
				m_pLevelData[index] = WAL;
				break;
			}
			case '*': {
				m_pLevelData[index] = KEY;
				break;
			}
			case 'D': {
				m_pLevelData[index] = DOR;
				break;
			}
			case 'X': {
				m_pLevelData[index] = GOL;
				break;
			}
			case '@': {
				m_pLevelData[index] = ' ';
				if (playerX != nullptr && playerY != nullptr) {
					*playerX = x;
					*playerY = y;
				}
				break;
			}
			case ' ': {
				break;
			}
			default: {
				cout << "Invalid character in level file: " << m_pLevelData[index] << endl;
				anyWarnings = true;
				break;
			}
			}
		}
	}

	return anyWarnings;

}

int Level::GetIndexFromCoordinates(int x, int y) {

	return y * m_width + x;

}



