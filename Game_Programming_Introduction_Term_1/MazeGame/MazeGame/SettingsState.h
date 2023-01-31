#pragma once
#include "GameState.h"

class StateMachineExampleGame;

class SettingsState : public GameState
{

	StateMachineExampleGame* m_pOwner;
	int m_input;

public:
	SettingsState(StateMachineExampleGame* pOwner);
	~SettingsState() = default;

	virtual bool Update(bool processInput = true) override;
	virtual void Draw() override;
	virtual void GetInput() override;

};

