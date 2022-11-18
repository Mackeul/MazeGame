#pragma once

#include "PlacableActor.h"


class Key;

class Player : public PlacableActor {

public:
	Player();

	//void SetPosition(int x, int y);

	bool HasKey();
	bool HasKey(int color);
	void PickupKey(Key* key);
	void UseKey();
	void DropKey();

	void AddMoney(int money) { m_money += money; }
	int GetMoney() { return m_money; }

	int GetLives() { return m_lives; }
	void DecrementLives() { m_lives--; }

	virtual void Draw() override;

private:
	Key* m_pCurrentKey;
	int m_money;
	int m_lives;
};