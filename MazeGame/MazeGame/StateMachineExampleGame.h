#pragma once
#include "GameStateMachine.h"

class Game;
class GameState;

class StateMachineExampleGame : public GameStateMachine
{
public:
    enum class SceneName {
        None,
        MainMenu,
        GamePlay,
		Settings,
		HighScores,
		Lose,
		Win
    };

private:
    Game* m_pOwner;

    GameState* m_pCurrentState;
    GameState* m_pNewState;

public:
    StateMachineExampleGame(Game* pOwner);

    virtual bool Init() override;
    virtual bool UpdateCurrentState(bool processInput = true) override;
    virtual void DrawCurrentState() override;
    virtual void ChangeState(GameState* pNewState) override;
    virtual bool CleanUp() override;
    void LoadScene(SceneName name);
	void GetInputFromState(bool processInput = true) override;
};

