#pragma once
#include "GameState.h"

class StateMachineExampleGame;

class MainMenuState : public GameState {

	StateMachineExampleGame* m_pOwner;
	int m_input;

public:
	MainMenuState(StateMachineExampleGame* pOwner);
	~MainMenuState() = default;

	virtual bool Update(bool processInput = true) override;
	virtual void Draw() override;
	void GetInput() override;

};

