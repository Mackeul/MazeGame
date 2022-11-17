#pragma once
#include "Point.h"

class Player {

	Point m_position;
	bool m_hasKey;

public:
	Player();
	~Player();

	int GetXPosition() { return m_position.x; }
	int GetYPosition() { return m_position.y; }

	int* GetXPositionPointer() { return &(m_position.x); }
	int* GetYPositionPointer() { return &(m_position.y); }

	void SetPosition(int x, int y);

	bool HasKey() { return m_hasKey; };
	void PickupKey();
	void UseKey();

	void Draw();
};