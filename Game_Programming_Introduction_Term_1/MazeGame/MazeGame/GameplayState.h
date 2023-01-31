#pragma once
#include <Windows.h>
#include <vector>
#include <string>

#include "GameState.h"
#include "Player.h"
#include "Level.h"


class StateMachineExampleGame;

class GameplayState : public GameState {
	
	StateMachineExampleGame* m_pOwner;
	
	Player m_player;
	Level* m_pLevel;

	bool m_beatLevel;

	int m_skipFrameCount;
	static constexpr int kFramesToSkip = 2;

	int m_currentLevel;
	std::vector<std::string> m_levelNames;

	int m_input;


public:
	GameplayState(StateMachineExampleGame* pOwner);
	~GameplayState();

	virtual void Enter() override;
	virtual bool Update(bool processInput = true) override;
	virtual void Draw() override;
	virtual void GetInput() override;

private:
	bool Load();
	void HandleCollision(int newPlayerX, int newPlayerY);

	void DrawHUD(const HANDLE& console);



};

