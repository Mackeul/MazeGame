#pragma once
#include <set>

#include "GameState.h"

class StateMachineExampleGame;

class HighScoreState : public GameState {

	StateMachineExampleGame* m_pOwner;
	std::set<int> m_HighScores;

public:
	HighScoreState(StateMachineExampleGame* pOwner);
	~HighScoreState() = default;

	virtual bool Update(bool processInput = true) override;
	virtual void Draw() override;

};
